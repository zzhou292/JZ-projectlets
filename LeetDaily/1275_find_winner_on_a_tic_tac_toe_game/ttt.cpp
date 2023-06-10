
// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:

    bool check(int* data){
        // check row
       for (int i = 0; i < 3; i++){
           if(data[i*3+0]==1 && data[i*3+1]==1 && data[i*3+2]==1){
               return true;
           }
       }

       // check column
       for (int i = 0; i < 3; i++){
           if(data[0+i]==1 && data[3+i]==1 && data[6+i]==1){
               return true;
           }
       }

        // check diag 1
        if(data[0]==1 && data[4]==1 && data[8]==1){
           return true;
        }

        // check diag 2
        if(data[2]==1 && data[4]==1 && data[6]==1){
           return true;
        }



       return false;
    }



    string tictactoe(vector<vector<int>>& moves) {
        int X_data[9];
        int O_data[9];

        for (int i = 0; i < moves.size(); i++){
            if (i%2==0){
                X_data[moves[i][0]*3 + moves[i][1]] = 1;
            }else{
                O_data[moves[i][0]*3 + moves[i][1]] = 1;
            }
        }

        bool X_win = check(X_data);
        bool O_win = check(O_data);

        if(X_win){return string("A");}
        if(O_win){return string("B");}
        
        if(moves.size()==9){return string("Draw");}
        return string("Pending");
        
    }
};

int main(){
    vector<vector<int>> input = {{0,0},{1,1},{2,0},{1,0},{1,2},{2,1},{0,1},{0,2},{2,2}};

    Solution a;
    cout << a.tictactoe(input)<<endl;

    return 0;
}