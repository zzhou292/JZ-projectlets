// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        // if both the numbers left and right is same, return anyone
        if(left==0 || right ==0) return 0;

        // if there binary numbers for left and right are of different digits
        if((int)log2(left)!=(int)log2(right)) return 0; 
        //initialize output with left range
        int res = left;

        while(left<right){
            res &= ++left;
        }
        return res;
    }
};

int main(){
    int left = 3;
    int right = 13;

    Solution a;
    cout << a.rangeBitwiseAnd(left,right) << endl;

    return 0;
}