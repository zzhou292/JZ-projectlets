// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // edge case
        if(nums.size()==0 || k<=0) return 0;


        priority_queue<int> qe;
        for(int& itm:nums) qe.push(itm);

        int count = 0;
        int cur = nums[0];
        do{
            count++;
            cur = qe.top();
            qe.pop();
        }while(count!=k);

        return cur;
    }
};

int main(){
    vector<int> input = {3,2,3,1,2,4,5,5,6};

    Solution a;
    cout << a.findKthLargest(input,4) << endl;

    return 0;
}