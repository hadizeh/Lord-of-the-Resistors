//
// Created by aria 336 77 940 on 08/06/2025.
//
#include "exceptions.h"
#include <stdexcept>
#include <string>
#include "regex.h"
element_not_found_exception::element_not_found_exception(string name) : not_found_exception("Element " + name + " not found in library") {}
const char* element_not_found_exception::what() const noexcept {
    return not_found_exception::what();
}
not_found_exception::not_found_exception(string message) : message(std::move(message)) {}
const char* not_found_exception::what() const noexcept {
    return message.c_str();
}
element_not_exist::element_not_exist(string name) : not_found_exception("Element " + name + " does not exist in the circuit") {}
const char* element_not_exist::what() const noexcept {
    return not_found_exception::what();
}
syntax_error::syntax_error(string message) : message(std::move(message)) {}
const char* syntax_error::what() const noexcept {
    return message.c_str();
}
