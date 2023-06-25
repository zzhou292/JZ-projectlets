// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if(nums.size()==0) return 0;
        int l = 0;
        int r = nums.size()-1;
        int mid = l+(r-l)/2;

        while(l<=r){
            mid = l+(r-l)/2;
            if(nums[mid] == target) return mid;
            if(nums[mid] > target){
                r = mid-1;
            }else if(nums[mid] < target){
                l = mid+1;
            }
        }

        if(nums[mid]>target){
            return mid;
        }else{
            return mid+1; 
        }
    }
};

int main(){
    vector<int> input = {1,3,5,6};
    int target = 5;

    Solution a;
    cout << a.searchInsert(input, target) << endl;

    return 0;
}