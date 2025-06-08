//
// Created by aria 336 77 940 on 08/06/2025.
//
#pragma once
#ifndef PROJECT_FAZE_1_REGEX_H
#define PROJECT_FAZE_1_REGEX_H

#endif //PROJECT_FAZE_1_REGEX_H
#include <iostream>
#include <string>
#include <regex>
#include "MNA.h"
#include "exceptions.h"
#include "Controller.h"
#include <vector>
#include "regex"
using namespace std;
//---------basics----------

//---------regexes---------
//add R<name> <node1> <node2> <value>
regex add_R (R"(^add R(\S+) (\S+) (\S+) (\S+))");
//delete R<name>
regex delete_R (R"(^delete R(\S+))");
//add C<name> <node1> <node2> <value>
regex add_C (R"(^add C(\S+) (\S+) (\S+) (\S+))");
//add L<name> <node1> <node2> <value>
regex add_L (R"(^add L(\S+) (\S+) (\S+) (\S+))");
//add D<name> <node1> <node2> <model>
regex add_D (R"(^add D(\S+) (\S+) (\S+) (\S+))");
//add wrong thing
regex adddddd (R"(^add (\S)(\S+) (\S+) (\S+) (\S+))");

//add GND <node>
regex add_GND(R"(^add GND (\S+))");
//delete L<name>
regex delete_L(R"(^delete L(\S+))");
//delete C<name>
regex delete_C(R"(^delete C(\S+))");
//delete D<name>
regex delete_D(R"(^delete D(\S+))");
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
// .print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] V(n001)
regex print_TRAN(R"(^\.print TRAN (\S+) (\S+)(?: (\S+))?(?: (\S+))? V\((\S+)\))");
regex print_DC(R"(^\.print DC (\S+) (\S+) (\S+) (\S+) V\((\S+)\))");
// .print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] I(R1)
// .print DC <SourceName> <StartValue> <EndValue> <Increment> I(C1
// .print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] I(R1)
regex print_TRAN_I(R"(^\.print TRAN (\S+) (\S+)(?: (\S+))?(?: (\S+))? I\((\S+)\))");
regex print_DC_I(R"(^\.print DC (\S+) (\S+) (\S+) (\S+) I\((\S+)\))");
//.print TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>] V(in) V(out) I(R1) I(D1)
regex print_TRAN_all(R"(^\.print TRAN (\S+) (\S+)(?: (\S+))?(?: (\S+))? V\((\S+)\) V\((\S+)\) I\((\S+)\) I\((\S+)\))");
//add VoltageSource<Name> <Node1> <Node2> <Value>
regex add_VoltageSource(R"(^add VoltageSource(\S+) (\S+) (\S+) (\S+))");
// add CurrentSource<Name> <Node1> <Node2> <Value>
regex add_CurrentSource(R"(^add CurrentSource(\S+) (\S+) (\S+) (\S+))");
// add V<name> <node+> <node-> SIN(<Voffset> <Vamplitude> <Frequency>)
regex add_V(R"(^add V(\S+) (\S+) (\S+) SIN\((\S+) (\S+) (\S+)\))");
// add E<Name> <Node1> <Node2> <CtrlNode1> <CtrlNode2> <Gain>
regex add_E(R"(^add E(\S+) (\S+) (\S+) (\S+) (\S+) (\S+))");
// add G<name> <node+> <node-> <control+> <control-> <Gain>
regex add_G(R"(^add G(\S+) (\S+) (\S+) (\S+) (\S+) (\S+))");
// add H<name> <node+> <node-> <vname> <gain>
regex add_H(R"(^add H(\S+) (\S+) (\S+) (\S+) (\S+))");
// add F<name> <node+> <node-> <vname> <gain>
regex add_F(R"(^add F(\S+) (\S+) (\S+) (\S+) (\S+))");
// .TRAN <Tstep> <Tstop> [<Tstart>] [<Tmaxstep>]
regex TRAN(R"(^\.TRAN (\S+) (\S+)(?: (\S+))?(?: (\S+))?)");
//.DC <SourceName> <StartValue> <EndValue> <Increment>
regex DC(R"(^\.DC (\S+) (\S+) (\S+) (\S+))");