// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        // edge case
        if(strs.size()==0){
            return "";
        }
        
        sort(strs.begin(), strs.end());

        int cnt = 0;
        int min_len = min(strs[0].size(), strs[strs.size()-1].size());

        for(int i = 0; i < min_len; i++){
            if (strs[0][i] == strs[strs.size()-1][i]){
                cnt++;
            }else{
                break;
            }
        }

        return strs[0].substr(0,cnt);
    }
};

int main(){
    string in1 = "jason";
    string in2 = "jasonarvarna";
    string in3 = "jarvana";
    string in4 = "jacob";

    vector<string> input= {in1, in2, in3, in4};

    Solution a;
    cout << a.longestCommonPrefix(input) << endl;
}