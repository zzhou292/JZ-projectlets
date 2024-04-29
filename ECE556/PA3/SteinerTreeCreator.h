#ifndef STEINER_TREE_CREATOR_H
#define STEINER_TREE_CREATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <limits>

class Node
{
public:
    std::string name;
    int x, y;
    Node(const std::string &name, int x, int y);
    friend std::ostream &operator<<(std::ostream &os, const Node &node);
};

struct Edge
{
    int to;
    double weight;
    Edge(int to, double weight) : to(to), weight(weight) {}

    // Define comparison operator for the priority queue
    bool operator>(const Edge &other) const
    {
        return weight > other.weight;
    }
};

struct Line
{
    int x1, y1, x2, y2;
    Line(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

class SteinerTreeCreator
{
private:
    std::pair<int, int> lowerLeft;
    std::pair<int, int> upperRight;
    std::vector<Node> pins;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    std::vector<bool> inMST;
    std::vector<double> minEdgeWeight;
    std::vector<int> edgeTo;

    std::vector<Line> horizontalLines;
    std::vector<Line> verticalLines;

public:
    float totalCost;

    void initializeProblem(const std::string &filename);
    double calculateDistance(const Node &a, const Node &b) const;
    void findMST();
    void unpackMST();
    void evaluateCost();
    void outputResults(const std::string &filename);
};

#endif // STEINER_TREE_CREATOR_H
