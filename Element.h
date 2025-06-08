
#pragma once
#include "iostream"
#include "Node.h"

using namespace std;

#ifndef PROJECT_FAZE_1_ELEMENTS_H
#define PROJECT_FAZE_1_ELEMENTS_H

#endif //PROJECT_FAZE_1_ELEMENTS_H

enum ElementType {
    RESISTOR,
    CAPACITOR,
    INDUCTOR,
    VOLTAGE_SOURCE,
    CURRENT_SOURCE,
    DIODE,
    OPAMP,
    SWITCH,
    GROUND,
    WIRE
};

class Elements{
private:
    string name;
    Node* node1;
    Node* node2;
    ElementType type;
    double value;


public:
    Elements(string new_name , Node* A , Node* B , ElementType C , double D) :
            name(new_name) , node1(A) , node2(B) , type(C) , value(D){};

    string get_name(){
        return name;
    }
    void set_name(string new_name){
        name = new_name;
    }
    Node* get_node1(){
        return node1;
    }
    Node* get_node2(){
        return node2;
    }
    ElementType get_type(){
        return type;
    }
    double get_value(){
        return value;
    }
    void set_value(double new_value){
        value = new_value;
    }

};

class Resistor : public Elements{


public:
    Resistor(string new_name , Node* A , Node* B , double R) :
            Elements(new_name, A, B, RESISTOR, R) {};


};

class Capacitor : public Elements{
public:
    Capacitor(string new_name , Node* A , Node* B , double C) :
            Elements(new_name, A, B, CAPACITOR, C) {};
};

class Inductor : public Elements{
public:
    Inductor(string new_name , Node* A , Node* B , double L) :
            Elements(new_name, A, B, INDUCTOR, L) {};
};

class VoltageSource : public Elements{
public:
    VoltageSource(string new_name , Node* A , Node* B , double V) :
            Elements(new_name, A, B, VOLTAGE_SOURCE, V) {};
};

class CurrentSource : public Elements{
public:
    CurrentSource(string new_name , Node* A , Node* B , double I) :
            Elements(new_name, A, B, CURRENT_SOURCE, I) {};
};
class Diode : public Elements{
public:
    Diode(string new_name , Node* A , Node* B) :
            Elements(new_name, A, B, DIODE, 0.0) {}; // Diodes typically don't have a value like resistors or capacitors
};