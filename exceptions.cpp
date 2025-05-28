//
// Created by DanCo on 5/28/2025.
//

#include "exceptions.h"
const char *Resistant_exception::what() {
    return "Resistant exception";
}
const char *Resistor_negative_resistance_exception::what() const noexcept {
    return "Error: Resistance cannot be zero or negative";
}
not_found_exception::not_found_exception(string message) {
    this->message = message;
}
const char *not_found_exception::what() const noexcept {
    string s="Error: Element "+message+" not found in library";
    return s.c_str();
}
Resistor_repeated_exception::Resistor_repeated_exception(string message) {
    this->message = message;
}
const char *Resistor_repeated_exception::what() const noexcept {
    string s="Error: Resistor "+message+"already exists in the circuit";
}

const char *Resistor_not_found_for_deleting_exception::what() const noexcept {
    return"Error: Cannot delete resistor; component not found";
}
const char *Capacitor_exception::what() {
    return "Capacitor error";
}
const char *Capacitor_negative_capacity_exception::what() const noexcept {
    return"Error: Capacitance cannot be zero or negative";
}

const char *Capacitor_not_found_for_deleting_exception::what() const noexcept {
    return "Error: Cannot delete capacitor; component not found";
}
Capacitor_repeated_exception::Capacitor_repeated_exception(string message) {
    this->message = message;
}
const char *Capacitor_repeated_exception::what() const noexcept {
    string s="Error: Capacitor "+message+" already exists in the circuit";
    return s.c_str();
}
const char *Inductor_exception::what() const noexcept {
    return "Error: Inductor error";
}
const char *Inductor_negative_exception::what() const noexcept {
    return "Error: Inductance cannot be zero or negative";
}
const char *Inductor_not_found_for_deleting_exception::what() const noexcept {
    return "Error: Cannot delete inductor; component not found";
}
Inductor_repeated_exception::Inductor_repeated_exception(string message) {
    this->message = message;
}
const char *Inductor_repeated_exception::what() const noexcept {
    string s="Error: inductor "+message+" already exists in the circuit";
    return s.c_str();
}
const char *Diode_exception::what() {
    return "Error: Diode error";
}
const char *Diode_not_found_for_deleting_exception::what() const noexcept {
    return "Error: Cannot delete diode; component not found";
}
Diode_wrong_modality::Diode_wrong_modality(string message) {
    this->message = message;
}
const char *Diode_wrong_modality::what() const noexcept {
    string s="Error: Model "+message+"not found in library";
    return s.c_str();
}
Diode_repeated_exception::Diode_repeated_exception(string message) {
    this->message = message;
}
const char *Diode_repeated_exception::what() const noexcept {
    string s="Error: diode "+message+" already exists in the circuit";
}
const char *syntax_error::what() const noexcept {
    return "Error: Syntax error";
}