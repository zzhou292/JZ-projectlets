#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
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

void FloorplanOptimizer::evaluateHPWL()
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

    cur_hpwl = tmp_hpwl / 2;
}

void FloorplanOptimizer::constructRelativePositions()
{
    // Add +1 for the dummy node which acts as the universal predecessor
    int n = blocks.size() + 1;

    // Clear previous graph data and resize for all blocks plus the dummy node
    adjX.clear();
    adjY.clear();
    adjX.resize(n, std::vector<int>());
    adjY.resize(n, std::vector<int>());

    // Initialize relationships from the dummy node to all other blocks
    // This effectively sets the dummy node as preceding all blocks
    for (int i = 1; i < n; i++)
    {
        adjX[0].push_back(i);
        adjY[0].push_back(i);
    }

    // Construct graphs based on sequence pair rules for actual blocks
    for (int i = 0; i < blocks.size(); ++i)
    {
        for (int j = 0; j < blocks.size(); ++j)
        {
            if (i == j)
                continue;
            int posI_Pos = std::find(positiveSequence.begin(), positiveSequence.end(), blocks[i]) - positiveSequence.begin();
            int posJ_Pos = std::find(positiveSequence.begin(), positiveSequence.end(), blocks[j]) - positiveSequence.begin();
            int posI_Neg = std::find(negativeSequence.begin(), negativeSequence.end(), blocks[i]) - negativeSequence.begin();
            int posJ_Neg = std::find(negativeSequence.begin(), negativeSequence.end(), blocks[j]) - negativeSequence.begin();

            // Adjust indices to account for the dummy node at index 0
            // Construct horizontal graph
            if (posI_Pos > posJ_Pos && posI_Neg > posJ_Neg)
            {
                adjX[j + 1].push_back(i + 1); // "+1" adjusts for the dummy node
            }
            // Construct vertical graph
            if (posI_Pos < posJ_Pos && posI_Neg > posJ_Neg)
            {
                adjY[j + 1].push_back(i + 1); // "+1" adjusts for the dummy node
            }
        }
    }

    // No need to apply transitive reduction to the dummy node's edges,
    // but you may continue to apply it to the rest of the graph
    transitiveReduction(adjX);
    transitiveReduction(adjY);
}

void FloorplanOptimizer::transitiveReduction(std::vector<std::vector<int>> &adj)
{
    int n = adj.size();
    for (int u = 0; u < n; ++u)
    {
        for (auto v : adj[u])
        {
            std::vector<bool> reachable(n, false);
            std::queue<int> q;
            q.push(v);

            while (!q.empty())
            {
                int current = q.front();
                q.pop();
                for (int next : adj[current])
                {
                    if (!reachable[next])
                    {
                        reachable[next] = true;
                        q.push(next);
                    }
                }
            }

            adj[u].erase(std::remove_if(adj[u].begin(), adj[u].end(),
                                        [&reachable, &u](int v)
                                        { return u != v && reachable[v]; }),
                         adj[u].end());
        }
    }
}

void FloorplanOptimizer::calculateDimensionsUsingSPFA()
{
    // The number of nodes including the dummy node
    int n = blocks.size() + 1;

    // Initialize distances with a large negative value for the longest path calculation,
    // except for the dummy node, which starts at 0.
    std::vector<int> distX(n, std::numeric_limits<int>::min());
    std::vector<int> distY(n, std::numeric_limits<int>::min());
    distX[0] = 0;
    distY[0] = 0;

    std::queue<int> q;
    std::vector<bool> inQueue(n, false);

    // Start the SPFA algorithm from the dummy node
    q.push(0);
    inQueue[0] = true;

    // Process horizontal constraints (X-axis)
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (int v : adjX[u])
        {
            int width = (u == 0) ? 0 : blocks[u - 1]->width; // Using 0 width for dummy node
            if (distX[v] < distX[u] + width)
            {
                distX[v] = distX[u] + width;
                if (!inQueue[v])
                {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    // Reset inQueue for Y-axis processing
    std::fill(inQueue.begin(), inQueue.end(), false);
    q.push(0); // Start again from the dummy node
    inQueue[0] = true;

    // Process vertical constraints (Y-axis)
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (int v : adjY[u])
        {
            int height = (u == 0) ? 0 : blocks[u - 1]->height; // Using 0 height for dummy node
            if (distY[v] < distY[u] + height)
            {
                distY[v] = distY[u] + height;
                if (!inQueue[v])
                {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }

    // Update the positions of the blocks based on the calculated distances
    for (int i = 1; i < n; ++i)
    {
        // Ensure non-negative values and cast to size_t
        blocks[i - 1]->posX = static_cast<size_t>(std::max(0, distX[i]));
        blocks[i - 1]->posY = static_cast<size_t>(std::max(0, distY[i]));
    }

    // Calculate the total layout width and height
    layout_width = 0;
    layout_height = 0;
    for (int i = 1; i < n; ++i)
    {
        layout_width = std::max(layout_width, (int)(blocks[i - 1]->posX + blocks[i - 1]->width));
        layout_height = std::max(layout_height, (int)(blocks[i - 1]->posY + blocks[i - 1]->height));
    }

    totalArea = layout_width * layout_height;
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

void FloorplanOptimizer::move_3(Module *a, Module *b)
{
    // Find indices of a and b in the positive sequence
    auto posA = std::find(negativeSequence.begin(), negativeSequence.end(), a) - negativeSequence.begin();
    auto posB = std::find(negativeSequence.begin(), negativeSequence.end(), b) - negativeSequence.begin();

    // Swap a and b in the positive sequence
    std::swap(negativeSequence[posA], negativeSequence[posB]);
}

void FloorplanOptimizer::move_4(Module *a) // rotate
{
    int tmp_width = a->width;
    a->width = a->height;
    a->height = tmp_width;
}

double FloorplanOptimizer::evaluateCost()
{
    averageArea = (averageArea * (num_iterations - 1) + layout_height * layout_width) / static_cast<double>(num_iterations);
    averagehpwl = (averagehpwl * (num_iterations - 1) + cur_hpwl) / static_cast<double>(num_iterations);

    double overshoot_length = pen * (layout_width - outline_width + layout_height - outline_height);

    return (alpha * layout_height * layout_width / averageArea) +
           (1 - alpha) * (cur_hpwl + overshoot_length) / averagehpwl;
}

void FloorplanOptimizer::optimize()
{

    // Define a list of move functions using std::function. Each move function takes two module pointers as arguments.
    std::vector<std::function<void(Module *, Module *)>> moveFunctions = {
        [this](Module *a, Module *b)
        { this->move_1(a, b); },
        [this](Module *a, Module *b)
        { this->move_2(a, b); },
        [this](Module *a, Module *b)
        { this->move_3(a, b); },
        // For move_4, since it operates on a single module, we'll adapt it to fit the expected two-parameter function signature.
        [this](Module *a, Module *)
        { this->move_4(a); }};

    // Simulated Annealing
    do
    {
        pen *= 2.0;
        double T = 1000.0;
        double alpha = 0.95;
        double T_0 = 0.01;
        int iteration_per_temp = 3000;

        while (T >= T_0)
        {
            // Cooling schedule
            T = alpha * T;
            // Backup current sequences and area
            num_iterations++;
            constructRelativePositions();
            calculateDimensionsUsingSPFA();
            evaluateHPWL();
            auto backupPositiveSequence = positiveSequence;
            auto backupNegativeSequence = negativeSequence;
            auto backupCost = evaluateCost(); // Implement this function based on SPFA calculation
            auto backupAverageArea = averageArea;
            auto backupAverageHPWL = averagehpwl;

            std::cout << "cur_T:" << T << " pen:" << pen << std::endl;
            std::cout << "total area: " << layout_height * layout_width << " bc: " << backupCost << std::endl;

            // Randomly shuffle the move functions to randomize their order
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            shuffle(moveFunctions.begin(), moveFunctions.end(), std::default_random_engine(seed));
            for (int a = 0; a < iteration_per_temp; a++)
            {
                for (auto &moveFunction : moveFunctions)
                {

                    num_iterations++;
                    int i = rand() % blocks.size();
                    int j = rand() % blocks.size();
                    while (i == j)
                    {
                        i = rand() % blocks.size();
                        j = rand() % blocks.size();
                    }

                    Module *blockA = positiveSequence[i];
                    Module *blockB = positiveSequence[j];

                    // Call the move function. Note: For move_4, blockB is ignored.
                    moveFunction(blockA, blockB);

                    constructRelativePositions();   // Reconstruct positions after the move
                    calculateDimensionsUsingSPFA(); // Recalculate dimensions
                    evaluateHPWL();

                    double newCost = evaluateCost();
                    if (newCost < backupCost)
                    {
                        backupCost = newCost;
                        backupPositiveSequence = positiveSequence;
                        backupNegativeSequence = negativeSequence;
                        backupAverageArea = averageArea;
                        backupAverageHPWL = averagehpwl;
                    }
                    else
                    {
                        double delta = newCost - backupCost;
                        double acceptProb = std::exp(-delta * 10000.0 / (double)T);
                        double randProb = static_cast<double>(rand()) / RAND_MAX;

                        if (randProb < acceptProb)
                        {
                            backupCost = newCost;
                            backupPositiveSequence = positiveSequence;
                            backupNegativeSequence = negativeSequence;
                            backupAverageArea = averageArea;
                            backupAverageHPWL = averagehpwl;
                        }
                        else
                        {
                            // Restore sequences and layout if no improvement
                            positiveSequence = backupPositiveSequence;
                            negativeSequence = backupNegativeSequence;
                            constructRelativePositions();   // Restore positions
                            calculateDimensionsUsingSPFA(); // Restore dimensions
                            evaluateHPWL();
                            averageArea = backupAverageArea;
                            averagehpwl = backupAverageHPWL;
                            num_iterations--;
                        }
                    }
                }
            }
        }

    } while (layout_height - outline_height > 0 || layout_width - outline_width > 0);
}

void FloorplanOptimizer::exportSolution(const std::string &outputPath, double programRuntime)
{
    std::ofstream outFile(outputPath);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to open " << outputPath << " for writing.\n";
        return;
    }

    // Assuming chip width and height are calculated and stored
    double chipArea = layout_width * layout_height;

    // Write the required information
    outFile << evaluateCost() << "\n";
    outFile << cur_hpwl << "\n";
    outFile << chipArea << "\n";
    outFile << layout_width << " " << layout_height << "\n";
    outFile << programRuntime << "\n";

    // Write bounding box information for each macro
    for (const auto &block : blocks)
    {
        // Calculate upper-right corner (x2, y2)
        int x2 = block->posX + block->width;
        int y2 = block->posY + block->height;

        outFile << block->id << " " << block->posX << " " << block->posY << " " << x2 << " " << y2 << "\n";
    }

    outFile.close();
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

    FloorplanOptimizer optimizer(alpha);
    optimizer.loadFromFiles(blockFilePath, netFilePath);
    // After loading, output loaded data to command line
    optimizer.printLoadedData();
    optimizer.initializeSequences();

    optimizer.constructRelativePositions();
    optimizer.calculateDimensionsUsingSPFA();
    optimizer.evaluateHPWL();

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    optimizer.optimize();

    // Stop timing
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "runtime: " << duration.count() << std::endl;

    optimizer.exportSolution(outputFilePath, (double)duration.count());
    std::cout << "layout width: " << optimizer.layout_width << " layout height: " << optimizer.layout_height << std::endl;

    return 0;
}