// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        if(digits.size()==0) return digits;

        int carry = 0;
        for(int i = digits.size()-1; i >= 0; i--){
            int num = digits[i] + carry;
            if(i==digits.size()-1) num = digits[i]+1;
            
            digits[i] = num%10;
            carry = num/10;
        }

        if(carry!=0){
            digits.insert(digits.begin(), carry);
        }

        return digits;
    } 
};


int main(){
    Solution a;
    vector<int> input = {4,3,2,1};
    vector<int> res = a.plusOne(input);

    for(int i = 0; i < res.size(); i++) cout << res[i] << ", ";
    
    return 0;
}