// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        vector<vector<char>> visited;
        for(int i = 0; i < m; i++){
            vector<char> temp;
            for(int j = 0; j < n; j++){
                temp.push_back(0);
            }
            visited.push_back(temp);
        }

        int row = 0; int col = 0;
        int dir = 0; // 0 ->; 1 down; 2 <-; 3 up;
        vector<int> res;
        while(row>=0 && row<m && col>=0 && col<n && visited[row][col]==0){
            res.push_back(matrix[row][col]);
            visited[row][col]=1;
            // switch direction
            if((dir==0 && (col+1>=n||visited[row][col+1]==1)) ||
               (dir==1 && (row+1>=m||visited[row+1][col]==1)) || 
               (dir==2 && (col-1<0||visited[row][col-1]==1)) || 
               (dir==3 && (row-1<0||visited[row-1][col]==1))){
                   dir=(dir+1)%4;
               } 

            if(dir==0){
                col++;
            }else if(dir==1){
                row++;
            }else if(dir==2){
                col--;
            }else if(dir==3){
                row--;
            }
        }

        return res;
    }
};

int main(){
    vector<vector<int>> input;
    vector<int> row_1 = {1,2,3,4};
    vector<int> row_2 = {5,6,7,8};
    vector<int> row_3 = {9,10,11,12};

    input.push_back(row_1);
    input.push_back(row_2);
    input.push_back(row_3);

    Solution a;
    vector<int> res = a.spiralOrder(input);

    for(int& a:res){
        cout << a << ", ";
    }

    return 0;
}