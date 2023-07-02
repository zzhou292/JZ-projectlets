
// Author: Jason Zhou
// XOR has exchange rule
#include "../general_include.h"

using namespace std;
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res=0;
        for(auto& a: nums) res=res^a;
        return res;
    }
};

int main(){
    vector<int> input = {2,2,3,3,4,4,5,5,6};

    Solution a;
    cout << a.singleNumber(input) << endl;
    
    return 0;
}