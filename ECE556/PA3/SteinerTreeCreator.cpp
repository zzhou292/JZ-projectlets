#include "SteinerTreeCreator.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <queue>
#include <chrono>
#include <vector>
#include <functional> // For std::greater

Node::Node(const std::string &name, int x, int y) : name(name), x(x), y(y) {}

std::ostream &operator<<(std::ostream &os, const Node &node)
{
    os << "Node(" << node.name << ", " << node.x << ", " << node.y << ")";
    return os;
}

void SteinerTreeCreator::initializeProblem(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Read boundary line
    sscanf(line.c_str(), "Boundary = (%d,%d), (%d,%d)",
           &lowerLeft.first, &lowerLeft.second,
           &upperRight.first, &upperRight.second);

    std::getline(file, line); // Read number of pins
    int numPins;
    sscanf(line.c_str(), "NumPins = %d", &numPins);

    std::string part, pinName;
    int x, y;
    for (int i = 0; i < numPins; ++i)
    {
        std::getline(file, line);
        std::istringstream pinStream(line);
        pinStream >> part >> pinName >> part;
        sscanf(part.c_str(), "(%d,%d)", &x, &y);
        pins.push_back(Node(pinName, x, y));
    }
    file.close();
}

double SteinerTreeCreator::calculateDistance(const Node &a, const Node &b) const
{
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void SteinerTreeCreator::findMST()
{
    inMST.resize(pins.size(), false);
    minEdgeWeight.resize(pins.size(), std::numeric_limits<double>::max());
    edgeTo.resize(pins.size(), -1);

    // Start with the first pin
    minEdgeWeight[0] = 0.0;
    pq.push(Edge(0, 0.0));
    int ct = 0;

    while (!pq.empty())
    {
        Edge current = pq.top();
        pq.pop();
        int v = current.to;

        if (inMST[v])
            continue;
        inMST[v] = true;
        ct++;

        // For each pin not in MST, check if it can be connected with a shorter edge
        for (size_t w = 0; w < pins.size(); ++w)
        {
            if (!inMST[w])
            {
                double weight = calculateDistance(pins[v], pins[w]);
                if (weight < minEdgeWeight[w])
                {
                    minEdgeWeight[w] = weight;
                    edgeTo[w] = v;
                    pq.push(Edge(w, weight));
                }
            }
        }
    }
}

void SteinerTreeCreator::unpackMST()
{
    for (size_t i = 1; i < pins.size(); ++i)
    {
        if (edgeTo[i] != -1)
        {
            const Node &fromNode = pins[edgeTo[i]];
            const Node &toNode = pins[i];

            // Create a horizontal line from `fromNode.x` to `toNode.x` at `fromNode.y`
            horizontalLines.emplace_back(fromNode.x, fromNode.y, toNode.x, fromNode.y);
            // Create a vertical line from `fromNode.y` to `toNode.y` at `toNode.x`
            verticalLines.emplace_back(toNode.x, fromNode.y, toNode.x, toNode.y);
        }
    }
}

void SteinerTreeCreator::evaluateCost()
{
    double cost = 0.0;
    for (const auto &line : horizontalLines)
    {
        cost += std::abs(line.x1 - line.x2);
    }
    for (const auto &line : verticalLines)
    {
        cost += std::abs(line.y1 - line.y2);
    }
    totalCost = cost;
}

void SteinerTreeCreator::outputResults(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening output file: " << filename << std::endl;
        return;
    }

    // Writing the number of routed pins and the total cost
    outFile << "NumRoutedPins = " << pins.size() << std::endl;
    outFile << "WireLength = " << static_cast<int>(totalCost) << std::endl; // Cast to int if needed

    // Writing all vertical lines
    for (const auto &line : verticalLines)
    {
        outFile << "V-line (" << line.x1 << "," << line.y1 << ") (" << line.x2 << "," << line.y2 << ")" << std::endl;
    }

    // Writing all horizontal lines
    for (const auto &line : horizontalLines)
    {
        outFile << "H-line (" << line.x1 << "," << line.y1 << ") (" << line.x2 << "," << line.y2 << ")" << std::endl;
    }

    outFile.close();
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input filename> <output filename>" << std::endl;
        return 1;
    }

    SteinerTreeCreator creator;
    creator.initializeProblem(argv[1]); // Use command line argument for filename

    auto start = std::chrono::high_resolution_clock::now();
    creator.findMST();
    creator.unpackMST();
    creator.evaluateCost();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "findMST runtime: " << elapsed.count() << " seconds" << std::endl;

    creator.outputResults(argv[2]);
    std::cout << "Total cost: " << creator.totalCost << std::endl;
    return 0;
}
