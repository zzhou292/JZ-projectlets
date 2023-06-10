// Author: Jason Zhou
#include "../general_include.h"
using namespace std;
class Solution {
public:
    int jump(vector<int>& nums) {
        int res = 0;
        int l = 0;
        int r = 0;
        int far = 0;

        while(r < nums.size()-1){
            for (int i = l; i <= r; i++){
                far = max(far, nums[i]+i);
            }

            l = r + 1;
            r = far;
            res++;
        }

        return res;
    }
};

int main(){
    vector<int> input = {2,3,1,1,4};

    Solution a;
    cout << a.jump(input) << endl;
}