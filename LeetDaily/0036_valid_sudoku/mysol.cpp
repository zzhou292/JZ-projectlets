// Author: Jason Zhou
// this is my own solution, not the best, but acceptable
#include "../general_include.h"

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<char> cset;

        // check row
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[i].size();j++){
                if(board[i][j]!='.'){
                    if(cset.find(board[i][j])!=cset.end()){
                        return false;
                    }else{
                        cset.insert(board[i][j]);
                    }
                }
            }
            cset.clear();
        }

        // check column
        for(int j = 0; j < board[0].size(); j++){
            for(int i = 0; i < board.size();i++){
                if(board[i][j]!='.'){
                    if(cset.find(board[i][j])!=cset.end()){
                        return false;
                    }else{
                        cset.insert(board[i][j]);
                    }
                }
            }
            cset.clear();
        }

        // check subset
        for(int a = 0; a < 3; a++){
            for (int b = 0; b < 3; b++){
                int start_i = 3*a;
                int start_j = 3*b;
                for (int i = 0; i < 3; i++){
                    for(int j = 0; j < 3;j++){
                        if(board[start_i+i][start_j+j]!='.'){
                            if(cset.find(board[start_i+i][start_j+j])!=cset.end()){
                                return false;
                            }else{
                            cset.insert(board[start_i+i][start_j+j]);
                            }
                        }
                    }
                }
                cset.clear();
            }
        }

        return true;
    }
};