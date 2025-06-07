//
// Created by DanCo on 6/7/2025.
//

#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <memory>
using namespace std;
#include <vector>
#include "Element.h"
#include "Node.h"
class Circuit {
    vector<unique_ptr<Element>> elements;
    vector<Node> nodes;

public:
    Circuit();
    ~Circuit();
    void addElement(string type ,string name);
};

#endif //CIRCUIT_H
