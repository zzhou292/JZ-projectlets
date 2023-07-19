// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size()==0) return true;

        int l = 0;
        int r = 0;
        int far = 0;
        while(r < nums.size()-1){
            for(int i = l; i <= r; i++){
                far = max(far, nums[i]+i);
            }
            if(r==far) break;
            l = r+1;
            r = far;
        }

        if(far >= nums.size()-1) return true;
        return false;
    }
};

int main(){
    vector<int> input = {2,3,1,1,4};

    Solution a;
    cout << a.canJump(input) << endl;

    return 0;
}