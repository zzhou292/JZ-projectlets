// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        // edge case
        if(s.size()==0) return true;
        if(t.size()==0) return false;

        int s_ptr = 0;
        int t_ptr = 0;
        while(t_ptr <= t.size()-1){
            if(s[s_ptr]==t[t_ptr]){
                s_ptr++;
            }
            t_ptr++;

            // termination
            if(s_ptr==s.size()) return true;
        }

        return false;
    }
};

int main(){
    string s = "abc";
    string t = "ahbgdc";

    Solution a;
    cout << a.isSubsequence(s,t) << endl;

    return 0;
}