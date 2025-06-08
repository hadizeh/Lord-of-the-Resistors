#include <iostream>
#include <string>
#include <regex>
#include "MNA.h"
#include "exceptions.h"
#include "Controller.h"
#include "regex.h"
#include "map"
#include <vector>
#include <algorithm>
#include "View.h"

using namespace std;

///////////////////////////////

//list



int main() {
    string line;
    bool cond = true;
    Controller controller;
    View view;
    while (cond) {
        getline(cin, line);
        try {
            cond = view.inputHandler(line,controller);
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    return 0;
}