// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // edge case 
        if(nums.size()==0) return 0;

        int count = 0;
        int prev = nums[0];
        for(int i = 1; i < nums.size(); i++){
            if(nums[i]==prev){
                count++;
                if(count>=2){
                    nums.erase(nums.begin()+i);
                    i--;
                }
            }else{
                count = 0;
            }
            prev = nums[i];
        }

        return nums.size();
    }
};

int main(){
    Solution a;
    vector<int> input = {1,1,1,2,2,3};
    cout << a.removeDuplicates(input) << endl;

    return 0;
}