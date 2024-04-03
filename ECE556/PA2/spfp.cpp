#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>   // std::shuffle
#include <random>      // std::default_random_engine
#include <chrono>      // std::chrono::system_clock
#include "spfp_ds.hpp" // Assume your class definitions are in this header

// Helper function to check if a line should be processed
bool isDataLine(const std::string &line)
{
    return !line.empty() && isalpha(line[0]);
}

std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void FloorplanOptimizer::loadFromFiles(const std::string &blockFilePath, const std::string &netFilePath)
{
    std::ifstream blockFile(blockFilePath);
    std::ifstream netFile(netFilePath);
    std::string line;
    std::regex wsRegex("\\s+"); // Whitespace regex for splitting

    if (!blockFile)
    {
        std::cerr << "Error opening block file: " << blockFilePath << std::endl;
        return;
    }

    // Skip non-relevant lines and read the outline width and height, if applicable
    while (std::getline(blockFile, line) && line.find("Outline:") == std::string::npos)
        ;
    // Assuming outline information is processed here

    // Process block and terminal information
    while (std::getline(blockFile, line))
    {
        line = std::regex_replace(line, wsRegex, " "); // Normalize spaces

        if (line.empty() || line[0] == '#' || line[0] == '\n')
            continue; // Skip empty or comment lines

        std::istringstream iss(line);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

        if (tokens.size() == 3)
        { // It's a block
            Module *block = new Module(tokens[0], std::stoul(tokens[1]), std::stoul(tokens[2]));
            if (getModuleByName(tokens[0]) == nullptr)
            {
                addModule(block);
            }
        }
        else if (tokens.size() == 4 && tokens[1] == "terminal")
        { // It's a fixed point, handled within Module
            Module *terminal = new Module(tokens[0], std::stoul(tokens[2]), std::stoul(tokens[3]), false);
            if (getModuleByName(tokens[0]) == nullptr)
            {
                addModule(terminal);
            }
        }
    }
    if (!netFile)
    {
        std::cerr << "Error opening net file: " << netFilePath << std::endl;
        return;
    }

    // number of nets
    std::getline(netFile, line);
    auto it = std::sregex_token_iterator(line.begin(), line.end(), wsRegex, -1);
    int num_nets = std::stoi(*(++it));

    // configurations of nets
    while (std::getline(netFile, line))
    {
        if (line.size() == 0)
        {
            continue;
        }

        size_t netdegree = 0;
        it = std::sregex_token_iterator(line.begin(), line.end(), wsRegex, -1);
        netdegree = std::stoi(*(++it));

        Net *n = new Net();
        for (size_t i = 0; i < netdegree; ++i)
        {
            Module *var;
            std::getline(netFile, line);
            it = std::sregex_token_iterator(line.begin(), line.end(), wsRegex, -1);
            var = getModuleByName(*it);

            n->addModule(var);
        }
        addNet(n);
    }
}

void FloorplanOptimizer::initializeSequences()
{
    // Filter movable blocks only
    positiveSequence.clear();
    negativeSequence.clear();

    for (auto &module : modules)
    {
        if (module->isMovable)
        {
            positiveSequence.push_back(module);
            negativeSequence.push_back(module);
        }
    }

    // Obtain a time-based seed:
    unsigned seed_1 = std::chrono::system_clock::now().time_since_epoch().count();
    unsigned seed_2 = std::chrono::system_clock::now().time_since_epoch().count() + 1209;

    // Shuffle the sequences to generate a random initial sequence pair
    std::shuffle(positiveSequence.begin(), positiveSequence.end(), std::default_random_engine(seed_1));
    std::shuffle(negativeSequence.begin(), negativeSequence.end(), std::default_random_engine(seed_2));

    // Output the initial sequences
    std::cout << "Positive sequence: ";
    for (const auto &module : positiveSequence)
    {
        std::cout << module->id << " ";
    }
    std::cout << std::endl;

    std::cout << "Negative sequence: ";
    for (const auto &module : negativeSequence)
    {
        std::cout << module->id << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
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
    optimizer.initializeSequences();

    return 0;
}
