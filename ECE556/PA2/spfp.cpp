#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include "spfp_ds.hpp" // Assume your class definitions are in this header

// Helper function to check if a line should be processed
bool isDataLine(const std::string& line) {
    return !line.empty() && isalpha(line[0]);
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void FloorplanOptimizer::loadFromFiles(const std::string& blockFilePath, const std::string& netFilePath) {
    std::ifstream blockFile(blockFilePath);
    std::ifstream netFile(netFilePath);
    std::string line;
    std::regex wsRegex("\\s+"); // Whitespace regex for splitting

    if (!blockFile) {
        std::cerr << "Error opening block file: " << blockFilePath << std::endl;
        return;
    }

    // Skip non-relevant lines and read the outline width and height, if applicable
    while (std::getline(blockFile, line) && line.find("Outline:") == std::string::npos);
    // Assuming outline information is processed here

    // Process block and terminal information
    while (std::getline(blockFile, line)) {
        line = std::regex_replace(line, wsRegex, " "); // Normalize spaces
        if (line.empty() || line[0] == '#' || line[0] == '\n') continue; // Skip empty or comment lines

        std::istringstream iss(line);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

        if (tokens.size() == 3) { // It's a block
            Module block(tokens[0], std::stoul(tokens[1]), std::stoul(tokens[2]));
            addModule(block);
        } else if (tokens.size() == 4 && tokens[1] == "terminal") { // It's a fixed point, handled within Module
            Module terminal(tokens[0], std::stoul(tokens[2]), std::stoul(tokens[3]), false);
            addModule(terminal);
        }
    }

    if (!netFile) {
        std::cerr << "Error opening net file: " << netFilePath << std::endl;
        return;
    }
if (!netFile) {
    std::cerr << "Error opening net file: " << netFilePath << std::endl;
    return;
}

std::string netName;
size_t netDegree = 0;
// Read lines from the net file
while (std::getline(netFile, line)) {
    // Use regex to remove extra spaces and trim the line
    line = std::regex_replace(line, wsRegex, " "); 
    // Skip if line is a comment or empty
    if (line.empty() || line[0] == '#' || line[0] == '\n') continue;

    std::istringstream iss(line);
    std::string firstWord;
    iss >> firstWord;

    // If the line specifies the degree of a net
    if (firstWord == "NetDegree:") {
        iss >> netDegree; // Extract net degree
        iss >> netName; // Assuming the next token is the net name, based on usual formats
        Net net; // Assuming you have a default constructor for Net

        for (size_t i = 0; i < netDegree; ++i) {
            if (!std::getline(netFile, line)) break; // Exit loop if there are no more lines
            line = std::regex_replace(line, wsRegex, " "); // Normalize spaces
            line = trim(line); // Trim to remove leading and trailing spaces
            if (line.empty()) { --i; continue; } // Adjust for empty lines
            Module* module = getModuleByName(line); // Find module by name
            if (module) {
                net.addModule(module); // Add the module to the current net
            } else {
                std::cerr << "Module named '" << line << "' not found in net." << std::endl;
            }
        }
        addNet(net); // Add the fully populated net to your collection
    }
}
}


int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " [α value] [input.block name] [input.net name] [output file name]" << std::endl;
        return 1;
    }

    double alpha = std::stod(argv[1]);
    std::string blockFilePath = argv[2];
    std::string netFilePath = argv[3];
    std::string outputFilePath = argv[4];

    FloorplanOptimizer optimizer;
    optimizer.loadFromFiles(blockFilePath, netFilePath);
    // After loading, output loaded data to command line
    optimizer.printLoadedData();

    return 0;
}
