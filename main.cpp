#include <iostream>
#include <string>
#include <regex>
#include "MNA.h"
#include "exceptions.h"
#include "Controller.h"
using namespace std;
//---------basics----------
enum {Resistor,Capacitor,Inductor,Diode,GND,all};
string element_names[all]={"R","C","L","D","GND"};
string proper_Diode_modals[all]={"D","Z"};
//---------regexes---------
//add R<name> <node1> <node2> <value>
//add C<name> <node1> <node2> <value>
//add L<name> <node1> <node2> <value>
//add D<name> <node1> <node2> <model>
regex add(R"(^add (\S+) (\S+) (\S+) (\S+))");

//add GND <node>
regex add_GND(R"(^add GND (\S+))");
//delete L<name>
//delete C<name>
//delete R<name>
//delete D<name>
regex delete_element(R"(^delete (\S+))");
//delete GND <node>
regex delete_GND(R"(^delete GND (\S+))");
//show circuits
regex show_nodes(R"(^.nodes)");
regex show_special_elements(R"(^.list (\S+))");
regex show_element(R"(^list\s*$)");
//rename node
//.rename node <old_name> <new_name>
regex rename_node(R"(^.rename node (\S+) (\S+))");
//.print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] V(n001)
//.print DC <SourceName> <StartValue> <EndValue> <Increment> V(out)
regex solve (R"(^.print (\S+))");
bool inputHandler(string line,Controller &c) {
    bool ok=true;
    smatch matches;
    if(regex_match(line,matches,add)) {
        c.add(matches[1].str(),matches[2].str(),matches[3].str(),matches[4].str());
    }
    else if(regex_match(line,matches,add_GND)) {

    }
}
int main() {
    string line;
    bool cond = true;
    Controller controller;
    while (cond) {
        getline(cin, line);
        try {
            cond = inputHandler(line,controller);
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
