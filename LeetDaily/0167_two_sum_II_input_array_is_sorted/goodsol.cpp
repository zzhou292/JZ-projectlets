
// good solution, two pointer optimized
// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> res = {-1, -1};

        int l = 0;
        int r = numbers.size()-1;

        while(l < r){
            if(numbers[l]+numbers[r]==target) break;
             
            if(numbers[l]+numbers[r]>target){
                r--;
            }else{
                l++;
            }
        }

        res[0] = l+1;
        res[1] = r+1;

        return res;
    }
};

int main(){
    vector<int> input = {2,7,11,15};
    int target = 18;

    Solution a;
    vector<int> res = a.twoSum(input, target);

    cout << res[0] << endl;
    cout << res[1] << endl;
}