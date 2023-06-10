// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    bool isValid(vector<int> pos, int rows, int cols){
        if (pos[0] >= 0 && pos[0] < rows){
            if (pos[1] >= 0 && pos[1] < cols){
                return true;
            }
        }

        return false;
    }

    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        int orientation = 0; // 0 for east, 1 for south, 2 for west, 3 for north
        int step = 0; // iteration step number
        int footstep = 1; // foot step number, add 2 each 2 steps

        vector<vector<int>> res;
        vector<int> my_pos = {rStart, cStart};
        res.push_back(my_pos);

        while(res.size() < rows*cols)
        {

            if(step%2==0 && step!=0){
                footstep = footstep + 1;
            }

            switch(orientation){
                case 0:
                {
                    for(int i = 0; i < footstep; i++)
                    {
                        my_pos[1] = my_pos[1]+1;
                        if(isValid(my_pos,rows,cols)){
                            res.push_back(my_pos);
                        }
                    }
                    break; 
                }
                case 1:
                {
                    for(int i = 0; i < footstep; i++)
                    {
                        my_pos[0] = my_pos[0]+1;
                        if(isValid(my_pos,rows,cols)){
                            res.push_back(my_pos);
                        }
                    }
                    break;
                }
                case 2:
                {
                    for(int i = 0; i < footstep; i++)
                    {
                        my_pos[1] = my_pos[1]-1;
                        if(isValid(my_pos,rows,cols)){
                            res.push_back(my_pos);
                        }
                    }
                    break;
                }
                case 3:
                {
                    for(int i = 0; i < footstep; i++)
                    {
                        my_pos[0] = my_pos[0]-1;
                        if(isValid(my_pos,rows,cols)){
                            res.push_back(my_pos);
                        }
                    }
                    break;
                }

            }


            step++;
            orientation = (orientation+1)%4;
        }

        return res;
    }
};

int main(){
    Solution a;
    vector<vector<int>> output = a.spiralMatrixIII(1,4,0,0);

    // ==================================
    // ===== print out data =============
    for(int i = 0; i < output.size(); i++)
    {   
        std::cout << "[";
        for(int j = 0; j < output[i].size();j++){
            std::cout << output[i][j]<<" ";
        }
        std::cout << "]; ";
    }
    std::cout << std::endl;
    // ====================================

    return 0;
}