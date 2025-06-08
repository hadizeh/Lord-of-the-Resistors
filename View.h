//
// Created by aria 336 77 940 on 28/05/2025.
//
#include <iostream>
#include <string>
#include <regex>
#include "MNA.h"
#include "exceptions.h"
#include "Controller.h"
#include "map"
#include <vector>
#include <algorithm>
#include "regex.h"

#ifndef PROJECT_FAZE_1_VIEW_H
#define PROJECT_FAZE_1_VIEW_H
//these are my regexes
////add R<name> <node1> <node2> <value>
//regex add_R (R"(^add R(\S+) (\S+) (\S+) (\S+))");
////delete R<name>
//regex delete_R (R"(^delete R(\S+))");
////add C<name> <node1> <node2> <value>
//regex add_C (R"(^add C(\S+) (\S+) (\S+) (\S+))");
////add L<name> <node1> <node2> <value>
//regex add_L (R"(^add L(\S+) (\S+) (\S+) (\S+))");
////add D<name> <node1> <node2> <model>
//regex add_D (R"(^add D(\S+) (\S+) (\S+) (\S+))");
//
////add GND <node>
//regex add_GND(R"(^add GND (\S+))");
////delete L<name>
////delete C<name>
////delete R<name>
////delete D<name>
//regex delete_element(R"(^delete (\S+))");
////delete GND <node>
//regex delete_GND(R"(^delete GND (\S+))");
////show circuits
//regex show_nodes(R"(^.nodes)");
//regex show_special_elements(R"(^.list (\S+))");
//regex show_element(R"(^list\s*$)");
////rename node
////.rename node <old_name> <new_name>
//regex rename_node(R"(^.rename node (\S+) (\S+))");
////.print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] V(n001)
////.print DC <SourceName> <StartValue> <EndValue> <Increment> V(out)
//// .print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] V(n001)
//regex print_TRAN(R"(^\.print TRAN (\S+) (\S+)(?: (\S+))?(?: (\S+))? V\((\S+)\))");
//regex print_DC(R"(^\.print DC (\S+) (\S+) (\S+) (\S+) V\((\S+)\))");
//// .print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] I(R1)
//// .print DC <SourceName> <StartValue> <EndValue> <Increment> I(C1
//// .print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] I(R1)
//regex print_TRAN_I(R"(^\.print TRAN (\S+) (\S+)(?: (\S+))?(?: (\S+))? I\((\S+)\))");
//regex print_DC_I(R"(^\.print DC (\S+) (\S+) (\S+) (\S+) I\((\S+)\))");
////.print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] V(in) V(out) I(R1) I(D1)
//regex print_TRAN_all(R"(^\.print TRAN (\S+) (\S+)(?: (\S+))?(?: (\S+))? V\((\S+)\) V\((\S+)\) I\((\S+)\) I\((\S+)\))");
////add VoltageSource<Name> <Node1> <Node2> <Value>
//regex add_VoltageSource(R"(^add VoltageSource(\S+) (\S+) (\S+) (\S+))");
//// add CurrentSource<Name> <Node1> <Node2> <Value>
//regex add_CurrentSource(R"(^add CurrentSource(\S+) (\S+) (\S+) (\S+))");
//// add V<name> <node+> <node-> SIN(<Voffset> <Vamplitude> <Frequency>)
//regex add_V(R"(^add V(\S+) (\S+) (\S+) SIN\((\S+) (\S+) (\S+)\))");
//// add E<Name> <Node1> <Node2> <CtrlNode1> <CtrlNode2> <Gain>
//regex add_E(R"(^add E(\S+) (\S+) (\S+) (\S+) (\S+) (\S+))");
//// add G<name> <node+> <node-> <control+> <control-> <Gain>
//regex add_G(R"(^add G(\S+) (\S+) (\S+) (\S+) (\S+) (\S+))");
//// add H<name> <node+> <node-> <vname> <gain>
//regex add_H(R"(^add H(\S+) (\S+) (\S+) (\S+) (\S+))");
//// add F<name> <node+> <node-> <vname> <gain>
//regex add_F(R"(^add F(\S+) (\S+) (\S+) (\S+) (\S+))");
//// .TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>]
//regex TRAN(R"(^\.TRAN (\S+) (\S+)(?: (\S+))?(?: (\S+))?)");
////.DC <SourceName> <StartValue> <EndValue> <Increment>
//regex DC(R"(^\.DC (\S+) (\S+) (\S+) (\S+))");
//////////////////////////////////
map<string , double> unitPrefixes{
        {"k", 1e3},     // kilo
        {"M", 1e6},     // Mega
        {"G", 1e9},     // Giga
        {"T", 1e12},    // Tera
        {"Meg", 1e6},
        {"m", 1e-3},    // milli
        {"u", 1e-6},    // micro (sometimes written as µ)
        {"n", 1e-9},    // nano
        {"p", 1e-12}    // pico
};
//////////////////////////////////////
class View {
public:
    bool isPureDecimalNumber(const std::string& str) {
        if (str.empty()) return false;

        bool hasDot = false;

        for (char c : str) {
            if (c == '.') {
                if (hasDot) return false;  // More than one dot
                hasDot = true;
            } else if (!isdigit(c)) {
                return false;  // Not a digit
            }
        }

        // Must not be just a dot
        return !(str == ".");
    }
    void checking_element_value(string a , ElementType b , string typee){
        // This function checks if the value of an element is valid
        // For example, it can check if the value is a number or if it is within a certain range
        // You can implement your own logic here
        //it should check if it is not a double at all
        char lastchar = a[a.length() - 1];
            //check if last word is a number or char
            if (lastchar == 'k' || lastchar == 'M' || lastchar == 'G' || lastchar == 'T' ||
                lastchar == 'm' || lastchar == 'u' || lastchar == 'n' || lastchar == 'p') {
                //if it is a number with a unit prefix
                //check that if other chars make a double
                string valueWithoutUnit = a.substr(0, a.length() - 1);
                if(!isPureDecimalNumber(valueWithoutUnit)) {
                    throw invalid_argument(typee + " cannot be zero or negative");
                }
            }
            //else if it is not a number
            else if (!isdigit(lastchar) ) {
                throw invalid_argument(typee + " cannot be zero or negative");
            }

            if (!isPureDecimalNumber(a)) {
                throw invalid_argument(typee + " cannot be zero or negative");
            }
            double value = stod(a);
            if( value <= 0) {
                throw invalid_argument(typee + " cannot be zero or negative");
            }

    }

    void check_element_exsictance(string name, Controller &c , ElementType  E, string typenamee) {
        bool exists = false;
        if (E == RESISTOR) {
            for (int i = 0; i < c.resistors.size(); ++i) {
                if (c.resistors[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        } else if (E == CAPACITOR) {
            for (int i = 0; i < c.capacitors.size(); ++i) {
                if (c.capacitors[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        } else if (E == INDUCTOR) {
            for (int i = 0; i < c.inductors.size(); ++i) {
                if (c.inductors[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        } else if (E == VOLTAGE_SOURCE) {
            for (int i = 0; i < c.voltageSources.size(); ++i) {
                if (c.voltageSources[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        } else if (E == CURRENT_SOURCE) {
            for (int i = 0; i < c.currentSources.size(); ++i) {
                if (c.currentSources[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        } else if (E == DIODE) {
            for (int i = 0; i < c.diodes.size(); ++i) {
                if (c.diodes[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        }
        if (!exists) {
            //Cannot delete resistor; component not found
            throw element_not_exist("Cannot delete " + typenamee + "; component not found");
        }
    }

    void check_repeated_name(string name, Controller &c, ElementType E, string typenamee) {
        bool exists = false;
        if (E == RESISTOR) {
            for (int i = 0; i < c.resistors.size(); ++i) {
                if (c.resistors[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        } else if (E == CAPACITOR) {
            for (int i = 0; i < c.capacitors.size(); ++i) {
                if (c.capacitors[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        } else if (E == INDUCTOR) {
            for (int i = 0; i < c.inductors.size(); ++i) {
                if (c.inductors[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        } else if (E == VOLTAGE_SOURCE) {
            for (int i = 0; i < c.voltageSources.size(); ++i) {
                if (c.voltageSources[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        } else if (E == CURRENT_SOURCE) {
            for (int i = 0; i < c.currentSources.size(); ++i) {
                if (c.currentSources[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        } else if (E == DIODE) {
            for (int i = 0; i < c.diodes.size(); ++i) {
                if (c.diodes[i]->get_name() == name) {
                    exists = true;
                    break;
                }
            }
        }
        if (exists) {
            //Resistor <name> already exists in the circuit
            throw Resistor_repeated_exception("Resistor " + name + " already exists in the circuit");
        }
    }
    bool inputHandler(string line,Controller &c) {
        bool ok=true;
        smatch matches;
        if (regex_match(line, matches, add_R)) {
            //call the functions
            checking_element_value(matches[4].str(), RESISTOR, "Resistor");
            check_repeated_name(matches[1].str(), c, RESISTOR, "Resistor");
            string name = matches[1].str();
            string node1 = matches[2].str();
            string node2 = matches[3].str();
            double value = stod(matches[4].str());
        } else if (regex_match(line, matches, delete_R)) {
            check_element_exsictance(matches[2].str(), c, RESISTOR, "Resistor");
            string name = matches[1].str();
        } else if (regex_match(line, matches, add_C)) {
            checking_element_value(matches[4].str(), CAPACITOR, "Capacitor");
            check_repeated_name(matches[1].str(), c, CAPACITOR, "Capacitor");
            string name = matches[1].str();
            string node1 = matches[2].str();
            string node2 = matches[3].str();
            double value = stod(matches[4].str());
        } else if (regex_match(line, matches, add_L)) {
            checking_element_value(matches[4].str(), INDUCTOR, "Inductor");
            check_repeated_name(matches[1].str(), c, INDUCTOR, "Inductor");

            string name = matches[1].str();
            string node1 = matches[2].str();
            string node2 = matches[3].str();
            double value = stod(matches[4].str());
        } else if (regex_match(line, matches, add_D)) {
            string name = matches[1].str();
            string node1 = matches[2].str();
            string node2 = matches[3].str();
            string model = matches[4].str();
        } else if (regex_match(line, matches, add_GND)) {
            string nameOfNode = matches[1].str();
        } else if (regex_match(line, matches, delete_L)) {
            check_element_exsictance(matches[2].str(), c, INDUCTOR, "Inductor");
        } else if (regex_match(line, matches, delete_C)) {
            check_element_exsictance(matches[2].str(), c, CAPACITOR, "Capacitor");
        } else if (regex_match(line, matches, delete_D)) {
            check_element_exsictance(matches[2].str(), c, DIODE, "Diode");
        }  else if(regex_match(line, matches, adddddd)){
            //Element <name> not found in library
            throw element_not_found_exception("Element " + matches[1].str() + " not found in library");
        } else if (regex_match(line, matches, add_GND)) {
        } else if (regex_match(line, matches, delete_element)) {
        } else if (regex_match(line, matches, delete_GND)) {
        } else if (regex_match(line, show_nodes)) {
        } else if (regex_match(line, matches, show_special_elements)) {
        } else if (regex_match(line, show_element)) {
        } else if (regex_match(line, matches, rename_node)) {
        } else if (regex_match(line, matches, print_TRAN)) {
        } else if (regex_match(line, matches, print_DC)) {
        } else if (regex_match(line, matches, print_TRAN_I)) {
        } else if (regex_match(line, matches, print_DC_I)) {
        } else if (regex_match(line, matches, print_TRAN_all)) {
        } else if (regex_match(line,matches ,add_VoltageSource)){
        } else if (regex_match(line, matches, add_CurrentSource)) {
        } else if (regex_match(line, matches, add_V)) {
        } else if (regex_match(line, matches, add_E)) {
        } else if (regex_match(line, matches, add_G)) {
        } else if (regex_match(line, matches, add_H)) {
        } else if (regex_match(line, matches, add_F)) {
        } else if (regex_match(line, matches, TRAN)) {
        } else if (regex_match(line, matches, DC)) {
        } else if (line == "exit") {
            ok = false;
        } else {
            throw syntax_error("Syntax error");
        }

    }
};


#endif //PROJECT_FAZE_1_VIEW_H
