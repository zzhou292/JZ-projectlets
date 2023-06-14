// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:

    void clearNei(vector<vector<char>>& G, int i, int j){
        // termination conditions
        if (i < 0 || j < 0 || i >= G.size() || j >=G[i].size()){
            return;
        }

        if (G[i][j] == '0'){
            return;
        }
        
        G[i][j] = '0';

        clearNei(G, i+1, j);
        clearNei(G, i-1, j);
        clearNei(G, i, j+1);
        clearNei(G, i, j-1);
    }

    int numIslands(vector<vector<char>>& grid) {
        vector<vector<char>>& tgrid = grid;
        int res = 0;
        for (int i = 0; i < tgrid.size(); i++){
            for (int j = 0; j < tgrid[i].size(); j++){
                if(tgrid[i][j] == '1'){
                    clearNei(tgrid, i, j);
                    res++;
                }
            }
        }

        return res;
    }
    
};

int main(){
    vector<vector<char>> input;
    vector<char> row1 = {'1','1','0','0','0'};
    vector<char> row2 = {'1','1','0','0','0'};
    vector<char> row3 = {'0','0','1','0','0'};
    vector<char> row4 = {'0','0','0','1','1'};
    input.push_back(row1);
    input.push_back(row2);
    input.push_back(row3);
    input.push_back(row4);

    Solution a;
    cout << a.numIslands(input) << endl;

    return 0;
}