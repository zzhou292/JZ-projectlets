// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    void dfs(vector<vector<char>>& board, vector<vector<int>>& visited, int index, string& word, bool& res, int x_cur, int y_cur){
        if(index == word.size()){
            res=true;
            return;
        }

        // start case
        if(index==0){
            for(int i = 0; i<board.size(); i++){
                for(int j = 0; j<board[i].size(); j++){
                    if(board[i][j]==word[index]){
                        visited[i][j] = 1;
                        dfs(board, visited, index+1, word, res, i, j);
                        visited[i][j] = 0;
                    }
                }
            }
        }
        // continuous case
        else{
            // search around
            // 1) within boundary
            // 2) not visited
            // 3) hit character
            vector<int> x_mut = {0,0,-1,1};
            vector<int> y_mut = {1,-1,0,0};

            for(int i = 0; i < 4; i++){
                int c_x = x_cur + x_mut[i];
                int c_y = y_cur + y_mut[i];
                if(c_x>=0 && 
                    c_x<board.size() && 
                    c_y>=0 && 
                    c_y<board[0].size() && 
                    visited[c_x][c_y]==0 &&
                    board[c_x][c_y]==word[index])
                    {
                        visited[c_x][c_y] = 1;
                        dfs(board, visited, index+1, word, res, c_x, c_y);
                        visited[c_x][c_y] = 0;
                    }
            }
        }
    }

    bool exist(vector<vector<char>>& board, string word) {
        bool res = false;

        // edge case
        if(board.size() == 0 || board[0].size() == 0) return res;

        // pruning at the root
        if(word.size() > board.size()*board[0].size()) return false;
        unordered_map<char,int> check_map_board;
        unordered_map<char,int> check_map_word;
        for(int i = 0; i < word.size();i++) check_map_word[word[i]]++;
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[i].size(); j++){
                check_map_board[board[i][j]]++;
            }
        }

        for(auto& c_pair:check_map_word){
            char key = c_pair.first;
            if(check_map_board[key] < check_map_word[key]) return false;
        }

        vector<vector<int>> visited(board.size(), vector<int>(board[0].size(),0));

        dfs(board, visited, 0, word, res, -1, -1);

        return res;
    }
};

int main(){
    vector<char> vec1 = {'A','B','C','E'};
    vector<char> vec2 = {'S','F','C','S'};
    vector<char> vec3 = {'A','D','E','E'};
    
    vector<vector<char>> board;
    board.push_back(vec1);
    board.push_back(vec2);
    board.push_back(vec3);

    string word = "ABCCED";

    Solution a;
    cout << a.exist(board,word) << endl;
}