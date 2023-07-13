// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:

    void solve(string &digits, vector<string> &choice, vector<string> &result, string &ans, int index){

        if(ans.length() == digits.size()){
            result.push_back(ans);
            return;
        }

        string temp = choice[digits[index]-'2'];

        for(int i = 0; i < temp.size(); i++){
            ans.push_back(temp[i]);
            solve(digits, choice, result, ans, index+1);
            ans.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {

        if(digits.size() == 0)
            return {};

        vector<string> choice = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        vector<string> result;
        string ans = "";

        solve(digits, choice, result, ans, 0);

        return result;
    }
};

int main(){
    string digits = "4958";
    Solution a;
    vector<string> res = a.letterCombinations(digits);

    for(int i = 0; i < res.size(); i++){
        cout << res[i] << ",";
    }

    return 0;
}