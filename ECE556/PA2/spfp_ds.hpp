#include <vector>   // For using std::vector
#include <string>   // For using std::string
#include <iostream> // For input/output streams
#include <fstream>  // For file handling (std::ifstream, std::ofstream)
#include <cmath>    // If you need mathematical functions, e.g., for cost evaluation
#include <unordered_map>


class Module {
public:
    size_t posX = 0; // Position X
    size_t posY = 0; // Position Y
    size_t width = 0; // Width of the module
    size_t height = 0; // Height of the module
    std::string id; // Identifier for the module
    bool isMovable = true; // True if it's a block, false if it's a terminal

    // Constructor for movable blocks
    Module(const std::string& id, size_t width, size_t height) : id(id), width(width), height(height), isMovable(true) {}

    // Constructor for fixed terminals
    Module(const std::string& id, size_t posX, size_t posY, bool isMovable) : id(id), posX(posX), posY(posY), isMovable(isMovable) {}

    void print() const {
        std::cout << (isMovable ? "Block: " : "Terminal: ") << id 
                << ", Width: " << width << ", Height: " << height 
                << ", posX: " << posX << ", posY: " << posY << std::endl;
    }
};


class Net {
public:
    std::vector<Module*> connectedModules; // Pointers to connected modules

    void addModule(Module* module) {
        connectedModules.push_back(module);
    }

    void print() const {
        std::cout << "Net connects: ";
        for (const auto& module : connectedModules) {
            std::cout << module->id << " ";
        }
        std::cout << std::endl;
    }
};


class FloorplanOptimizer {
private:
    std::vector<Module> modules; // All modules including blocks and terminals
    std::vector<Net> nets; // All nets connecting the modules
    std::vector<Module*> positiveSequence; // Positive sequence for SP representation
    std::vector<Module*> negativeSequence; // Negative sequence for SP representation
    std::unordered_map<std::string, Module*> moduleMap;



public:
    FloorplanOptimizer() {
        // Constructor implementation
    }

    void addModule(const Module& module) {
        modules.push_back(module);
        // Update the map with a pointer to the newly added module
        moduleMap[module.id] = &modules.back();
    }

    Module* getModuleByName(const std::string& name) {
        auto it = moduleMap.find(name);
        if (it != moduleMap.end()) {
            return it->second; // it->second is a pointer to the Module
        }
        return nullptr; // Return nullptr if the module is not found
    }

    void addNet(const Net& net) {
        nets.push_back(net);
    }

    void optimize(); // Main method to run the optimization process

    // Utility methods for floorplan manipulation
    void initializeSequences();
    double evaluateCost() const;
    void applyMove(); // Apply a move to perturb the sequences
    
    // Methods for input/output
    void loadFromFiles(const std::string& blockFilePath, const std::string& netFilePath);
    void exportSolution(const std::string& outputPath) const;

    void printLoadedData() const {
        std::cout << "Loaded Data:" << std::endl;
        std::cout << "Modules:" << std::endl;
        for (const auto& module : modules) {
            module.print();
        }
        std::cout << "Nets:" << std::endl;
        for (const auto& net : nets) {
            net.print();
        }
    }
};
