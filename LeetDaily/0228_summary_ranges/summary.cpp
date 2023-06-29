// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        if(nums.size()==0) return res;

        int prev = nums[0];
        int pair_first = nums[0];
        for(int i = 1; i < nums.size(); i++){
            if (nums[i]!=prev+1){
                // encolse
                string temp;
                if(pair_first==prev){
                    temp = std::to_string(pair_first);
                }else{
                    temp = std::to_string(pair_first) + "->" + std::to_string(prev);
                }
                res.push_back(temp);
                pair_first = nums[i];
            }
            prev = nums[i];
        }

        string temp;    
        if(pair_first==prev){
            temp = std::to_string(pair_first);
        }else{
            temp = std::to_string(pair_first) + "->" + std::to_string(prev);
        }
        res.push_back(temp);

        return res;


    }
};

int main(){
    vector<int> input = {0,1,2,4,5,7};

    Solution a;
    vector<string> res = a.summaryRanges(input);

    for(auto& str: res){
        cout << str << ", ";
    }

    return 0;
}