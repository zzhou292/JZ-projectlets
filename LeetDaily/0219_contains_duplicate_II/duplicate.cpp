// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int,int> st;
        for(int i = 0; i < nums.size(); i++){
            if(st.find(nums[i])==st.end()){
                st[nums[i]] = i;
            }else{
                if((i-st[nums[i]])<=k){
                    return true;
                }else{
                    st[nums[i]] = i;
                }
            }
        }
        return false;
    }
};

int main(){
    Solution a;
    vector<int> input = {1,2,3,1,2,3};
    cout << a.containsNearbyDuplicate(input, 2) << endl;

    return 0;
}