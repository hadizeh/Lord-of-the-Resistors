//
// Created by DanCo on 6/4/2025.
//
#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Element.h"
#include "Circuit.h"
#include<vector>
class Controller {
public:
    vector<Node*> nodes;
    vector<Elements*> elements;
    vector<Diode*> diodes;
    vector<Resistor*> resistors;
    vector<Capacitor*> capacitors;
    vector<Inductor*> inductors;
    vector<VoltageSource*> voltageSources;
    vector<CurrentSource*> currentSources;
    vector<Circuit> circuits;
    int currentCircuitIndex=-1;
//    Controller();
//    ~Controller();
//    void createNewCircuit();
//    void showListOfCircuits();
//    void GotoCircuit(int circuitNumber);
//    void add(string nameandtype,string node1,string node2,string valueOrModel);
//    void addGround(string nameOfNode);
//    void SolveTransiant();
//    void solveDCsweap();
//    void SolveDC();
//    void getvoltage();
};



#endif //CONTROLLER_H