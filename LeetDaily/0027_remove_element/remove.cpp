// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        for(int i = 0; i < nums.size();i++){
            if(nums[i]==val){
                nums.erase(nums.begin()+i);
                i--;
            } 
        }
        return nums.size();
    }
};

int main(){
    vector<int> nums = {0,1,2,2,3,0,4,2};

    Solution a;
    cout << a.removeElement(nums, 2) << endl;

    for(int i = 0; i < nums.size(); i++){
        cout << nums[i] << " ";
    }

    return 0;
}