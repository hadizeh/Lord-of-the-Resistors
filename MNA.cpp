//
// Created by DanCo on 5/31/2025.
//
#include <iostream>
#include <cmath>
#include "MNA.h"

MNA::MNA(int size_n, int size_v,int size_c) {
    data.resize(size_n+size_v+size_c);
    for (auto& row : data) {
        row.resize(size_n+size_v, 0.0);
    }
    b_vec.resize(size_n+size_v,0.0);
    size_voltage = size_v;
    size_current = size_c;
    size_N = size_n;
}

void MNA::addResistor(double G, int node1, int node2) {
    if (node1 != 0 && node2 != 0) {
        data[node1-1][node1-1] += G;
        data[node2-1][node2-1] += G;
        data[node1-1][node2-1] -= G;
        data[node2-1][node1-1] -= G;
    } else if (node1 == 0 && node2 != 0) {
        data[node2-1][node2-1] += G;
    } else if (node2 == 0 && node1 != 0) {
        data[node1-1][node1-1] += G;
    }
}

vector<double> MNA::gaussianElimination() {
    vector<vector<double>> A_mat(data.size(), vector<double>(size_N+size_voltage+size_current));
    for(int i=0;i<data.size();i++) {
        for(int j=0;j<data[i].size();j++) {
            A_mat[i][j]=data[i][j];
        }
    }
    int n = A_mat.size();
    if (n == 0) return {}; // Handle empty system gracefully
    if (A_mat[0].size() != n || b_vec.size() != n) {
        std::cerr << "Error: Invalid matrix or vector dimensions for Gaussian elimination." << std::endl;
        return {};
    }

    for (int i = 0; i < n; ++i) {
        A_mat[i].push_back(b_vec[i]);
    }

    for (int i = 0; i < n; ++i) {
        int max_row = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::fabs(A_mat[k][i]) > std::fabs(A_mat[max_row][i])) {
                max_row = k;
            }
        }
        std::swap(A_mat[i], A_mat[max_row]);

        if (std::fabs(A_mat[i][i]) < 1e-12) {
            std::cerr << "Error: Matrix is singular or nearly singular during Gaussian elimination." << std::endl;
            for(int k=0; k<n; ++k) A_mat[k].pop_back();
            return {};
        }

        double pivot_val = A_mat[i][i];
        for (int j = i; j < n + 1; ++j) {
            A_mat[i][j] /= pivot_val;
        }

        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = A_mat[k][i];
                for (int j = i; j < n + 1; ++j) {
                    A_mat[k][j] -= factor * A_mat[i][j];
                }
            }
        }
    }

    std::vector<double> x(n);
    for (int i = 0; i < n; ++i) {
        x[i] = A_mat[i][n];
    }
    return x;
}

void MNA::addIndependentVoltage(double value, int node1, int node2,int numOfVoltage) {
    //the number of first voltage source is size_N (because its 0 base)
    if(numOfVoltage>size_voltage){return;}//it's incorrect
    int i_idx   = (node1 > 0 ? node1 - 1 : -1);
    int j_idx   = (node2 > 0 ? node2 - 1 : -1);
    int src_idx = size_N + numOfVoltage-1;
    // 1) KCL at node i: +1·i_s
    if (i_idx >= 0) data[i_idx][src_idx] += +1.0;

    // 2) KCL at node j: –1·i_s  (omit if j==0)
    if (j_idx >= 0) data[j_idx][src_idx] += -1.0;

    // 3) KVL for the source: v_i – v_j = Vs
    if (i_idx >= 0) data[src_idx][i_idx] += +1.0;
    if (j_idx >= 0) data[src_idx][j_idx] += -1.0;
    // 4) RHS entry for KVL equation:
    b_vec[src_idx] = value;
}

void MNA::addIndependentCurrent(double value, int node1, int node2,int numOfCurrent) {
    //the number of first current source is size_N + size_voltage
    if(numOfCurrent>size_current){return;}
    int idx1   = (node1 > 0 ? node1 - 1 : -1);
    int idx2   = (node2 > 0 ? node2 - 1 : -1);
    if (idx1 != -1) b_vec[idx1] += value;
    if (idx2 != -1) b_vec[idx2] -= value;
}

void MNA::addVCVS(double gain, int node1, int node2, int c_idx1, int c_idx2, int num) {
    /*
    Equation: v_p - v_q = A_v * (v_cp - v_cn)
A_v is the dimensionless voltage gain.
Impact on MNA size: A VCVS introduces its own unknown branch current (let's call it i_vcvs).
So, it increases M by 1. A new row and column are added to the M-dimension parts of the system.
     */
    if(num>size_voltage){return;}
    int i_idx   = (node1 > 0 ? node1 - 1 : -1);
    int j_idx   = (node2 > 0 ? node2 - 1 : -1);
    int idx_cp = (c_idx1 > 0 ? c_idx1 - 1 : -1);
    int idx_cn = (c_idx2 > 0 ? c_idx2 - 1 : -1);
    int src_idx = size_N + num - 1;
    if (i_idx >= 0) data[i_idx][src_idx] += 1.0;
    if (j_idx >= 0) data[j_idx][src_idx] -= 1.0;
    if (i_idx >= 0) data[src_idx][i_idx] += 1.0;
    if (j_idx >= 0) data[src_idx][j_idx] -= 1.0;
    if(idx_cp != -1) data[src_idx][idx_cp] -= gain;
    if(idx_cn != -1) data[src_idx][idx_cn] += gain;
    data[src_idx][src_idx] = 0;
    b_vec[src_idx] = 0;
}
void MNA::addVCCS(double gain, int node1, int node2, int c_idx1, int c_idx2) {
    /*Equation: I_out = G_m * (v_cp - v_cn)
G_m is the transconductance (Amps/Volt).
I_out is the current produced by the source, flowing from node q to node p.
Impact on MNA size: A VCCS does not introduce a new unknown branch current. Its current is directly defined by node voltages. So, it does not increase M.
Stamping: The VCCS directly modifies the KCL equations for nodes p and q.*/
    int i_idx   = (node1 > 0 ? node1 - 1 : -1);
    int j_idx   = (node2 > 0 ? node2 - 1 : -1);
    int idx_cp = (c_idx1 > 0 ? c_idx1 - 1 : -1);
    int idx_cn = (c_idx2 > 0 ? c_idx2 - 1 : -1);
    if(i_idx >= 0&&idx_cp>=0) data[i_idx][idx_cp] += gain;
    if(i_idx >= 0&& idx_cn>=0) data[i_idx][idx_cn] -= gain;
    if(j_idx >=0 && idx_cp>=0) data[j_idx][idx_cp] -= gain;
    if(j_idx >= 0 && idx_cn>=0) data[j_idx][idx_cn] += gain;
}
void MNA::addCCVS(double gain, int node1, int node2,int numOfc_ctrl,int numOfvoltage) {
    /*Equation: v_p - v_q = R_m * i_ctrl
R_m is the transresistance (Volts/Amp).
i_ctrl is the controlling current (M-indexed k_ctrl).
Impact on MNA size: A CCVS introduces its own unknown branch current (i_ccvs). So, it increases M by 1. Let m_ccvs be the new M-index.*/
    int i_idx   = (node1 > 0 ? node1 - 1 : -1);
    int j_idx   = (node2 > 0 ? node2 - 1 : -1);
    int k_ctrl = size_N+numOfc_ctrl-1;
    int src_idx = size_N + numOfvoltage-1;
    if(i_idx >= 0) data[i_idx][src_idx] += 1.0;
    if (j_idx >= 0) data[j_idx][src_idx] -= 1.0;
    if(i_idx >= 0) data[src_idx][i_idx] += 1.0;
    if(j_idx >= 0) data[src_idx][j_idx] -= 1.0;
    data[src_idx][k_ctrl] -= gain;
    b_vec[src_idx] = 0;
}
void MNA::addCCCS(double gain, int node1, int node2,int i_ctrl) {
    /*Equation: I_out = A_i * i_ctrl
A_i is the dimensionless current gain.
i_ctrl is the controlling current (M-indexed k_ctrl).
I_out flows from node q to node p.
Impact on MNA size: A CCCS does not introduce a new unknown branch current. It does not increase M.
Stamping: The CCCS modifies KCL equations at nodes p and q, and these modifications depend on an existing unknown branch current i_ctrl.
B_matrix[idx_p][k_ctrl] += A_i
B_matrix[idx_q][k_ctrl] -= A_i*/
    int i_idx   = (node1 > 0 ? node1 - 1 : -1);
    int j_idx   = (node2 > 0 ? node2 - 1 : -1);
    int k_ctrl = size_N+i_ctrl-1;
    if(i_idx>=0) {
        data[i_idx][k_ctrl] += gain;
    }
    if(j_idx>=0) {
        data[j_idx][k_ctrl] -= gain;
    }
}



