class Solution {
public:
  vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges,
                                       vector<vector<int>> &blueEdges) {
    // Graph representation
    vector<vector<pair<int, int>>> graph(n);

    // Red edges are marked with 0, blue edges with 1
    for (const auto &e : redEdges)
      graph[e[0]].emplace_back(e[1], 0);
    for (const auto &e : blueEdges)
      graph[e[0]].emplace_back(e[1], 1);

    // Distance arrays for red and blue paths, initialized to INT_MAX
    vector<int> redDist(n, INT_MAX), blueDist(n, INT_MAX);
    redDist[0] = blueDist[0] = 0; // Distance to start node is 0

    // Queue for BFS, each element is a pair of node and last edge color
    queue<pair<int, int>> q;
    q.push({0, 0}); // Start from node 0 with a red edge
    q.push({0, 1}); // Start from node 0 with a blue edge

    while (!q.empty()) {
      int node = q.front().first;
      int color = q.front().second;
      q.pop();

      for (const auto &next : graph[node]) {
        int nextNode = next.first;
        int nextColor = next.second;

        // Ensure alternating colors
        if (nextColor != color) {
          int &dist = (nextColor == 0) ? redDist[nextNode] : blueDist[nextNode];
          int &prevDist = (color == 0) ? redDist[node] : blueDist[node];

          if (prevDist + 1 < dist) {
            dist = prevDist + 1;
            q.push({nextNode, nextColor});
          }
        }
      }
    }

    // Result vector
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
      int minDist = min(redDist[i], blueDist[i]);
      res[i] = (minDist == INT_MAX) ? -1 : minDist;
    }

    return res;
  }
};
