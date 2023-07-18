// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    pair<int,int> intToPair(int square, int length){
        int r = (square-1)/length;
        int c = (square-1)%length;
        if(r%2==1) c = (length-1-c);

        r = length-1-r;

        return {r,c};
    }

    int snakesAndLadders(vector<vector<int>>& board) {
        queue<pair<int,int>> qe;
        vector<int> visited;
        int n = board.size();

        qe.push({1,0});

        while(!qe.empty()){
            pair<int,int> curr = qe.front();
            int curr_square = curr.first;
            int move = curr.second;
            qe.pop();

            for(int i = 1; i <= 6; i++){
                int next_square = curr_square + i;
                
                if(next_square > n*n) continue;
                
                pair<int,int> next_pair = intToPair(next_square, n);
                
                if(board[next_pair.first][next_pair.second]!=-1){
                    next_square = board[next_pair.first][next_pair.second];
                }
                
                if(next_square == n*n) return move+1;

                if(find(visited.begin(),visited.end(),next_square)==visited.end()){
                    qe.push({next_square, move+1});
                    visited.push_back(next_square);
                }
            }
        }
        return -1;
    }
};

int main(){
    vector<int> v1 = {-1,-1,-1,-1,-1,-1};
    vector<int> v2 = {-1,-1,-1,-1,-1,-1};
    vector<int> v3 = {-1,-1,-1,-1,-1,-1};
    vector<int> v4 = {-1,35,-1,-1,13,-1};
    vector<int> v5 = {-1,-1,-1,-1,-1,-1};
    vector<int> v6 = {-1,15,-1,-1,-1,-1};

    vector<vector<int>> input = {v1,v2,v3,v4,v5,v6};

    Solution a;
    cout << a.snakesAndLadders(input) << endl;

    return 0;
}