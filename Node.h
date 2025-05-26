// Project: Circuit Simulation Framework
#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H

#include "Element.h"
#include <functional>
#include <string>
#include <complex>
#include <vector>
#include <map>
#include <memory>
#include <complex>
#include <string>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>
using namespace std;

class Node {

private:
    // Core properties
    std::string id; // name
    bool isGlobal = false; // ground
    bool isHidden = false; // hidden

    // Electrical state
    double dcVoltage = 0.0; // DC
    std::complex<double> acVoltage = {0.0, 0.0}; // AC
    std::vector<double> transientVoltage; // dependent like for temperatur
    double pulseVoltage = 0.0; // Pulsing
    double initialVoltage = 0.0; // initial

    // Topological data
    // graph
    std::vector<Element*> connectedElements; // connected elements
    std::vector<Node*> adjacentNodes; // connected nodes

    // Simulation metadata
    int matrixIndex = -1; // for matrix
    int hierarchyLevel = 0; // for hierarchy
    bool isFloating = false; // floating node is connected to ground or in a loop or a connection
    std::vector<std::string> warnings; // warnings

    // Visualization
    struct Position { int x; int y; }; // for GUI
    bool isProbed = false; // for GUI
    int size; // for GUI
    Position guiPosition; // for GUI

    // Thermal properties
    double temperature = 300.0;  // Kelvin

    // Performance optimization
    std::complex<double> cachedImpedance = {0.0, 0.0}; // for AC analysis
    bool isActiveInMatrix = true; // for matrix
public:
    // Constructors
    Node(const std::string& nodeId, int x = 0, int y = 0)
            : id(nodeId), guiPosition{x, y} {} // constructor with position

    // Core identifier methods
    std::string getId() const { return id; }
    void setGlobal(bool global) { isGlobal = global; }
    bool getIsGlobal() const { return isGlobal; }

    // Voltage management
    void setDcVoltage(double voltage) { dcVoltage = voltage; }
    double getDcVoltage() const { return dcVoltage; }

    void setAcVoltage(const std::complex<double>& voltage) { acVoltage = voltage; }
    std::complex<double> getAcVoltage() const { return acVoltage; }

    void addTransientVoltage(double voltage) { transientVoltage.push_back(voltage); }
    const std::vector<double>& getTransientVoltage() const { return transientVoltage; }

    // Topology management
    void addElement(Element* comp) { connectedElements.push_back(comp); }
    const std::vector<Element*>& getElements() const { return connectedElements; }

    void setHierarchyLevel(int level) { hierarchyLevel = level; }
    int getHierarchyLevel() const { return hierarchyLevel; }
    void setHidden(bool hidden) { isHidden = hidden; }
    bool getIsHidden() const { return isHidden; }
    void setPulseVoltage(double voltage) { pulseVoltage = voltage; }
    double getPulseVoltage() const { return pulseVoltage; }
    void setSize(int s) { size = s; }
    int getSize() const { return size; }
    void setActiveInMatrix(bool active) { isActiveInMatrix = active; }
    bool getIsActiveInMatrix() const { return isActiveInMatrix; }


    void addAdjacentNode(Node* node) { adjacentNodes.push_back(node); }
    const std::vector<Node*>& getAdjacentNodes() const { return adjacentNodes; }

    // Matrix operations
    void setMatrixIndex(int idx) { matrixIndex = idx; }
    int getMatrixIndex() const { return matrixIndex; }

    // Error handling
    void setFloating(bool floating) { isFloating = floating; }
    bool getIsFloating() const { return isFloating; }

    void addWarning(const std::string& warning) { warnings.push_back(warning); }
    const std::vector<std::string>& getWarnings() const { return warnings; }

    // Visualization
    void setProbed(bool probed) { isProbed = probed; }
    bool getIsProbed() const { return isProbed; }


    void setGuiPosition(int x, int y) { guiPosition = {x, y}; }
    Position getGuiPosition() const { return guiPosition; }

    // Thermal properties
    void setTemperature(double temp) { temperature = temp; }
    double getTemperature() const { return temperature; }

    // Initial conditions
    void setInitialVoltage(double voltage) { initialVoltage = voltage; }
    double getInitialVoltage() const { return initialVoltage; }

    // Reset for new simulation
    void reset() {
        dcVoltage = initialVoltage;
        acVoltage = {0.0, 0.0};
        transientVoltage.clear();
        pulseVoltage = 0.0;
        isFloating = false;
        warnings.clear();
    }

    double voltage() const { return dcVoltage; }

};



#endif //PROJECT_NODE_H
