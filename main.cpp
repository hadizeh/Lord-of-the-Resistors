#include <iostream>
#include <string>
#include <regex>
using namespace std;
//---------basics----------
enum {Resistor,Capacitor,Inductor,Diode,GND,all};
string element_names[all]={"R","C","L","D","GND"};
string proper_Diode_modals[all]={"D","Z"};
//---------regexes---------
//add R<name> <node1> <node2> <value>
regex add_resistant(R"(add (\S+) (\S+) (\S+) (\S+))");
//add C<name> <node1> <node2> <value>
regex add_capacitor(R"(add (\S+) (\S+) (\S+) (\S+))");
//add L<name> <node1> <node2> <value>
regex add_Inductor(R"(add (\S+) (\S+) (\S+) (\S+))");
//add D<name> <node1> <node2> <model>
regex add_diode(R"(add (\S+) (\S+) (\S+) (\S+))");
//add GND <node>
regex add_GND(R"(add GND (\S+))");
//delete L<name>
//delete C<name>
//delete R<name>
//delete D<name>
regex delete_element(R"(delete (\S+))");
//delete GND <node>
regex delete_GND(R"(delete GND (\S+))");

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
