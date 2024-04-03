#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm> // std::shuffle
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock
#include <limits>
#include <queue>
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

    // Attempt to find the "Outline:" line and then parse it for the chip's outline dimensions
    bool outlineFound = false;
    size_t outlineWidth = 0, outlineHeight = 0;
    while (std::getline(blockFile, line))
    {
        if (line.find("Outline:") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string outlineLabel;
            iss >> outlineLabel >> outlineWidth >> outlineHeight;
            outline_width = outlineWidth;
            outline_height = outlineHeight;
            outlineFound = true;
            break; // Exit the loop once the outline dimensions are found
        }
    }

    if (!outlineFound)
    {
        std::cerr << "Outline dimensions not found in block file." << std::endl;
        return; // Outline is crucial for further processing, so return if not found
    }

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
                addModule(block, false);
            }
        }
        else if (tokens.size() == 4 && tokens[1] == "terminal")
        { // It's a fixed point, handled within Module
            Module *terminal = new Module(tokens[0], std::stoul(tokens[2]), std::stoul(tokens[3]), false);
            if (getModuleByName(tokens[0]) == nullptr)
            {
                addModule(terminal, true);
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

    for (auto &module : blocks)
    {

        positiveSequence.push_back(module);
        negativeSequence.push_back(module);
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

int FloorplanOptimizer::evaluateHPWL() const
{
    int tmp_hpwl = 0;
    int max_x = 0, min_x = std::numeric_limits<int>::max(), max_y = 0, min_y = std::numeric_limits<int>::max();
    int llx = 0, lly = 0;

    for (auto &net : nets)
    {

        max_x = 0;
        min_x = std::numeric_limits<int>::max();
        max_y = 0;
        min_y = std::numeric_limits<int>::max();
        llx = 0;
        lly = 0;

        for (auto &m : net->connectedModules)
        {
            // n is a terminal
            if (m->isMovable == false)
            {
                llx = 2 * m->posX;
                lly = 2 * m->posY;
            }
            // n is a block
            else
            {
                int x = m->posX;
                int y = m->posY;
                int w = m->width;
                int h = m->height;

                llx = 2 * x + ((x + w) - x);
                lly = 2 * y + ((y + h) - y);
            }

            if (llx >= max_x)
            {
                max_x = llx;
            }
            if (llx <= min_x)
            {
                min_x = llx;
            }
            if (lly >= max_y)
            {
                max_y = lly;
            }
            if (lly <= min_y)
            {
                min_y = lly;
            }
        }

        tmp_hpwl = tmp_hpwl + (max_x - min_x) + (max_y - min_y);
    }

    return tmp_hpwl;
}

void FloorplanOptimizer::constructRelativePositions()
{
    int n = positiveSequence.size();
    adjX.resize(n);
    adjY.resize(n);

    // Initialize graphs based on sequence pair rules
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
                continue;
            int posI_Pos = std::find(positiveSequence.begin(), positiveSequence.end(), blocks[i]) - positiveSequence.begin();
            int posJ_Pos = std::find(positiveSequence.begin(), positiveSequence.end(), blocks[j]) - positiveSequence.begin();
            int posI_Neg = std::find(negativeSequence.begin(), negativeSequence.end(), blocks[i]) - negativeSequence.begin();
            int posJ_Neg = std::find(negativeSequence.begin(), negativeSequence.end(), blocks[j]) - negativeSequence.begin();

            // Construct horizontal graph
            if (posI_Pos > posJ_Pos && posI_Neg > posJ_Neg)
            {
                adjX[j].push_back(i); // j is left of i
            }

            // Construct vertical graph
            if (posI_Pos < posJ_Pos && posI_Neg > posJ_Neg)
            {
                adjY[j].push_back(i); // j is below i
            }
        }
    }
}

void FloorplanOptimizer::calculateDimensionsUsingSPFA()
{
    int n = blocks.size(); // Use the size of movable blocks only

    // Containers for distances (longest paths)
    std::vector<int> distX(n, 0);
    std::vector<int> distY(n, 0);

    // Assuming the starting block is at position (0, 0)
    // It's necessary to have a "dummy" start node if the graph doesn't have a natural start.
    // For simplicity, let's assume the first block is the start; adjust as needed.
    distX[0] = 0;
    distY[0] = 0;

    std::queue<int> q;
    std::vector<bool> inQueue(n, false);

    // Initially add all blocks to the queue for processing
    for (int i = 0; i < n; ++i)
    {
        q.push(i);
        inQueue[i] = true;
    }

    // Process horizontal constraints (X-axis)
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (int v : adjX[u])
        {
            if (distX[v] < distX[u] + blocks[u]->width)
            {
                distX[v] = distX[u] + blocks[u]->width;
                if (!inQueue[v])
                {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    // Clear queue and reinitialize for vertical constraints (Y-axis)
    std::fill(inQueue.begin(), inQueue.end(), false);
    for (int i = 0; i < n; ++i)
    {
        q.push(i);
        inQueue[i] = true;
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (int v : adjY[u])
        {
            if (distY[v] < distY[u] + blocks[u]->height)
            {
                distY[v] = distY[u] + blocks[u]->height;
                if (!inQueue[v])
                {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    // Update blocks' positions based on calculated distances
    for (int i = 0; i < n; ++i)
    {
        if (distX[i] < 0)
            distX[i] = 0; // Clamp to 0 to prevent underflow if negative
        if (distY[i] < 0)
            distY[i] = 0;

        blocks[i]->posX = static_cast<size_t>(distX[i]);
        blocks[i]->posY = static_cast<size_t>(distY[i]);

        std::cout << "blocks " << blocks[i]->id << " posX " << blocks[i]->posX << " posY " << blocks[i]->posY << std::endl;
    }

    // Calculate the total layout width and height, including terminals
    size_t layoutWidth = 0, layoutHeight = 0;
    for (const auto &block : blocks)
    {
        layoutWidth = std::max(layoutWidth, block->posX + block->width);
        layoutHeight = std::max(layoutHeight, block->posY + block->height);
    }
    for (const auto &terminal : terminals)
    {
        layoutWidth = std::max(layoutWidth, terminal->posX + terminal->width);
        layoutHeight = std::max(layoutHeight, terminal->posY + terminal->height);
    }

    layout_width = layoutWidth;
    layout_height = layoutHeight;
}

// Move 1: Swap two elements (a and b by their pointers) in the positive sequence
void FloorplanOptimizer::move_1(Module *a, Module *b)
{
    // Find indices of a and b in the positive sequence
    auto posA = std::find(positiveSequence.begin(), positiveSequence.end(), a) - positiveSequence.begin();
    auto posB = std::find(positiveSequence.begin(), positiveSequence.end(), b) - positiveSequence.begin();

    // Swap a and b in the positive sequence
    std::swap(positiveSequence[posA], positiveSequence[posB]);
}
// Move 2: Swap two elements (a and b by their elements, not indices) in both sequences
void FloorplanOptimizer::move_2(Module *a, Module *b)
{
    // Find indices of a and b in the positive sequence
    auto posA = std::find(positiveSequence.begin(), positiveSequence.end(), a) - positiveSequence.begin();
    auto posB = std::find(positiveSequence.begin(), positiveSequence.end(), b) - positiveSequence.begin();

    // Swap a and b in the positive sequence
    std::swap(positiveSequence[posA], positiveSequence[posB]);

    // Find indices of a and b in the negative sequence
    auto negA = std::find(negativeSequence.begin(), negativeSequence.end(), a) - negativeSequence.begin();
    auto negB = std::find(negativeSequence.begin(), negativeSequence.end(), b) - negativeSequence.begin();

    // Swap a and b in the negative sequence
    std::swap(negativeSequence[negA], negativeSequence[negB]);
}
void FloorplanOptimizer::optimize()
{
    bool improvement = true;
    while (improvement)
    {
        std::cout << "current area: " << layout_height * layout_width << std::endl;
        improvement = false; // Assume no improvement will be found

        // Backup current sequences and area
        auto backupPositiveSequence = positiveSequence;
        auto backupNegativeSequence = negativeSequence;
        auto backupArea = layout_height * layout_width; // Implement this function based on SPFA calculation

        // Try Move 1
        for (size_t i = 0; i < positiveSequence.size() - 1 && !improvement; ++i)
        {
            for (size_t j = i + 1; j < positiveSequence.size() && !improvement; ++j)
            {
                Module *blockA = positiveSequence[i]; // Example selection
                Module *blockB = positiveSequence[j]; // Another example selection
                move_1(blockA, blockB);               // Use move_1 here
                constructRelativePositions();         // Reconstruct positions after the move
                calculateDimensionsUsingSPFA();       // Recalculate dimensions

                auto newArea = layout_height * layout_width;
                if (newArea < backupArea)
                {
                    improvement = true; // Accept the move
                }
                else
                {
                    // Restore sequences and layout if no improvement
                    positiveSequence = backupPositiveSequence;
                    negativeSequence = backupNegativeSequence;
                    constructRelativePositions();   // Restore positions
                    calculateDimensionsUsingSPFA(); // Restore dimensions
                }
            }
        }

        // If Move 1 didn't improve, try Move 2
        if (!improvement)
        {
            for (size_t i = 0; i < positiveSequence.size() - 1; ++i)
            {
                for (size_t j = i + 1; j < positiveSequence.size(); ++j)
                {
                    Module *blockA = positiveSequence[i]; // Example selection
                    Module *blockB = positiveSequence[j]; // Another example selection
                    move_2(blockA, blockB);               // Use move_2 here
                    constructRelativePositions();
                    calculateDimensionsUsingSPFA();

                    auto newArea = layout_height * layout_width;
                    if (newArea < backupArea)
                    {
                        improvement = true; // Accept the move
                        break;              // Exit the loop if improvement is found
                    }
                    else
                    {
                        // Restore sequences and layout if no improvement
                        positiveSequence = backupPositiveSequence;
                        negativeSequence = backupNegativeSequence;
                        constructRelativePositions();   // Restore positions
                        calculateDimensionsUsingSPFA(); // Restore dimensions
                    }
                }
                if (improvement)
                    break; // Exit the outer loop if improvement is found
            }
        }

        if (!improvement)
            break; // Exit the optimization loop if no improvement
    }
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
    optimizer.constructRelativePositions();
    optimizer.calculateDimensionsUsingSPFA();

    optimizer.optimize();

    int hpwl = optimizer.evaluateHPWL();
    std::cout << "hpwl: " << hpwl << std::endl;
    std::cout << "layout width: " << optimizer.layout_width << " layout height: " << optimizer.layout_height << std::endl;

    return 0;
}
