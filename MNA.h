//
// Created by DanCo on 5/31/2025.
//
#pragma once
#ifndef MNA_H
#define MNA_H
#include <vector>
using namespace std;

class MNA {
    /*the data matrix gets every element in circuit and if it's possible solve it with gaussian elimination

    data is based of for matrix A,B,C,D
    A: the base matrix for saving the Guidance of every resistor or for numerical solution the capacitor or inductor
    B: the base matrix for saving position of Voltage and current sources (independent or dependent)
    in order first voltage sources and then current sources
    C: the base matrix transposed form of matrix B
    D: the base matrix for dependent sources

    */
    vector<vector<double>> data;
    vector<double> b_vec;
    int size_N;
    int size_voltage;
    int size_current;
public:
    MNA(int size_n,int size_voltage,int size_current);

    void addIndependentCurrent(double value,int node1,int node2,int num);

    void addIndependentVoltage(double value,int node1,int node2,int numOfVoltage);

    void addVCVS(double gain,int node1,int node2,int c_idx1,int c_idx2,int num);

    void addCCVS(double gain,int node1,int node2,int numOfc_ctrl,int numOfvoltage);

    void addVCCS(double gain,int node1,int node2,int c_idx1,int c_idx2);

    void addCCCS(double gain,int node1,int node2,int i_ctrl);

    void addResistor(double G,int node1,int node2);

    vector <double> gaussianElimination();
};



#endif //MNA_H