// Author: Jason Zhou
// This is a solution, not necessarily running O(n), but acceptted by leetcode
#include "../general_include.h"
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // edge case
        if (nums.size()==0) return 0;
        sort(nums.begin(), nums.end()); // this is an O(nlogn) operation
        unordered_map<int, int> st;
        int max_sequence = INT_MIN;
        for(int i = 0; i < nums.size(); i++){
            if(st[nums[i]]!=0) continue;
            st[nums[i]] = st[nums[i]-1] + 1;
            max_sequence = max(max_sequence, st[nums[i]]);
        }

        return max_sequence;
    }
};

int main(){
    Solution sol;
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << sol.longestConsecutive(nums) << endl;
    return 0;
}