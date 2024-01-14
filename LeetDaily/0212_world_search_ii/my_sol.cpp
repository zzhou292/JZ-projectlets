class Node {
public:
  Node *nodes[26] = {};
  bool is_terminal = false;

  void insert(string word) {
    auto root = this;
    for (int i = 0; i < word.size(); i++) {
      if (root->nodes[word[i] - 'a'] == NULL) {
        root->nodes[word[i] - 'a'] = new Node();
      }
      root = root->nodes[word[i] - 'a'];
    }
    root->is_terminal = true;
  }

  bool search(string word) {
    auto root = this;
    for (int i = 0; i < word.size(); i++) {
      if (root->nodes[word[i] - 'a'] == NULL)
        return false;
      root = root->nodes[word[i] - 'a'];
    }
    if (root->is_terminal == true) {
      return true;
    } else {
      return false;
    }
  }

  bool isPrefix(string prefix) {
    auto root = this;
    for (int i = 0; i < prefix.size(); i++) {
      if (root->nodes[prefix[i] - 'a'] == NULL)
        return false;
      root = root->nodes[prefix[i] - 'a'];
    }
    return true;
  }
};

class Solution {
public:
  void dfs(int i, int j, vector<vector<char>> &board, Node *root,
           vector<vector<int>> &visited, string &cur, vector<string> &res,
           const int &n) {
    // Boundary and visited check
    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
        visited[i][j])
      return;

    // Check if current character can lead to a valid word
    char ch = board[i][j];
    if (!root->isPrefix(cur + ch))
      return;

    // Append current character and mark as visited
    cur.push_back(ch);
    visited[i][j] = 1;

    // Check for word and add to result
    if (root->search(cur) && find(res.begin(), res.end(), cur) == res.end()) {
      res.push_back(cur);
      if (res.size() == n)
        return; // Early stopping if result size meets requirement
    }

    // Explore all 4 directions
    dfs(i + 1, j, board, root, visited, cur, res, n);
    dfs(i - 1, j, board, root, visited, cur, res, n);
    dfs(i, j + 1, board, root, visited, cur, res, n);
    dfs(i, j - 1, board, root, visited, cur, res, n);

    // Backtrack
    cur.pop_back();
    visited[i][j] = 0;
  }

  void startHelper(int i, int j, vector<vector<char>> &board, Node *root,
                   vector<string> &res, const int &n) {
    vector<vector<int>> visited(board.size(), vector<int>(board[0].size(), 0));
    string cur = "";
    dfs(i, j, board, root, visited, cur, res, n);
  }

  vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
    // performance optimization step
    map<char, int> my_map;
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board[i].size(); j++) {
        my_map[board[i][j]]++;
      }
    }

    for (int i = 0; i < words.size(); i++) {
      bool invalid = false;
      for (const char &c : words[i]) {
        if (my_map[c] == 0)
          invalid = true;
      }
      if (invalid) {
        words.erase(words.begin() + i);
        i--;
      }
    }

    // debug - display valid
    for (const string &w : words) {
      cout << w << ", ";
    }

    vector<string> res;
    Node *root = new Node();
    for (const string &word : words) {
      root->insert(word);
    }

    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board[0].size(); j++) {
        startHelper(i, j, board, root, res, words.size());
      }
    }

    return res;
  }
};