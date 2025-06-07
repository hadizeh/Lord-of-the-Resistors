//
// Created by DanCo on 6/7/2025.
//

#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
using namespace std;

class Element {
protected:
    double voltage;
    double current;
    string name;
    int node1;
    int node2;
public:
    Element(string name,double c,double v);
    double getVoltage();
    double getCurrent();
    string getName();
    virtual void stamp(double v) =0;
};



#endif //ELEMENT_H
