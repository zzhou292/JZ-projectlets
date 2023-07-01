// Author: Jason Zhou
// a o(n) solution, using unordered_map
#include "../general_include.h"
using namespace std;
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, bool> st;
        
        for(int i = 0; i < nums.size(); i++){
            st[nums[i]] = true;
        }

        for(int i = 0; i < nums.size(); i++){
            if(st.count(nums[i]-1)==1) st[nums[i]] = false;
        }

        int res;
        for(int i = 0; i < nums.size(); i++){
            if(st[nums[i]]==true){
                int j = 0; int count = 0;
                while(st.count(nums[i]+j)==1){
                    j++;
                    count++;
                }
                res = max(res, count);
            }
        }
        return res;
    }
};

int main(){
    Solution sol;
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << sol.longestConsecutive(nums) << endl;
    return 0;
}