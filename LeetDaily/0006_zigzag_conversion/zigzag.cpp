// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        // edge case
        if(s.size()==0 || numRows == 0) return s;
        if(numRows == 1) return s;

        unordered_map<int, vector<char>> map;

        string res;
        bool seg = true;
        int counter = 0;
        int row_idx = 0;
        while(counter < s.size()){
            map[row_idx].push_back(s[counter]);
            counter++;

            if(row_idx == numRows-1){
                seg = false;
            }

            if(row_idx == 0){
                seg = true;
            }

            if(seg){
                row_idx++;
            }else{
                row_idx--;
            }
        }

        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < map[i].size(); j++){
                res = res + map[i][j];
            }
        }

        return res;
    }
};

int main(){
    string s = "PAYPALISHIRING";
    int numRows = 3;

    Solution a;
    cout << a.convert(s, numRows) << endl;

    return 0;
}