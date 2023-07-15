// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res={-1,-1};

        // edge case
        if(nums.size()==0) return res;
        if(nums.size()==1){
            if(nums[0]==target){
                res[0]=0; res[1]=0;
                return res;
            } 
        }

        int l = 0;
        int r = nums.size()-1;
        int mid = (l+r)/2;
        bool found = false;

        while(l<=r){
            if(nums[mid]==target){
                found = true;
                break;
            }else if(nums[mid]>target){
                r = mid-1;
            }else{
                l = mid+1;
            }

            mid = (l+r)/2;
        }

        if(found==false) return res;

        
        int res_l = mid;
        int res_r = mid;

        while(res_l-1>=0 && nums[res_l-1]==target){
            res_l--;
        }

        while(res_r+1<=nums.size()-1 && nums[res_r+1]==target){
            res_r++;
        }
        
        res[0] = res_l; res[1] = res_r;
        return res;
    }
};

int main(){
    vector<int> input = {5,7,7,8,8,10};
    int target = 8;

    Solution a;
    cout << a.searchRange(input, target)[0] << ", " << a.searchRange(input, target)[1]  << endl;

    return 0;
}