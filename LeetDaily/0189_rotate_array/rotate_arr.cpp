// Author: Jason Zhou
// my own acceptable solution
#include "../general_include.h"

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k%nums.size();
        vector<int> rotate_temp;
        for(int i = 0; i < k; i++){
            rotate_temp.push_back(nums[nums.size()-(k-i)]);
        }

        for(int i = 0; i < k; i++){
             nums.erase(nums.begin()+nums.size()-1);
        }

        rotate_temp.insert(rotate_temp.end(), nums.begin(), nums.end());

        nums = rotate_temp;
    }
};

int main(){
    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 3;

    Solution a;
    a.rotate(nums, k);
    
    for(int i = 0; i < nums.size(); i++){
        cout << nums[i] << " ";
    }

    return 0;
}