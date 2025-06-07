//
// Created by DanCo on 6/7/2025.
//

#include "Element.h"
Element::Element(string name, double c, double v) {
        this->name = name;
        this->voltage = c;
        this->current = v;
}
double Element::getVoltage() {
        return voltage;
}
double Element::getCurrent() {
        return current;
}
string Element::getName() {
        return name;
}

