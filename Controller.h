//
// Created by DanCo on 6/4/2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Element.h"
#include "Circuit.h"
#include<vector>
class Controller {
    vector<Circuit> circuits;
    int currentCircuitIndex=-1;
    public:
    Controller();
    ~Controller();
    void createNewCircuit();
    void showListOfCircuits();
    void GotoCircuit(int circuitNumber);
    void add(string nameandtype,string node1,string node2,string valueOrModel);
    void addGround(string nameOfNode);
    void SolveTransiant();
    void solveDCsweap();
    void SolveDC();
    void getvoltage();
};



#endif //CONTROLLER_H
