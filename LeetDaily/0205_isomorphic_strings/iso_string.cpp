// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> st_s_t;
        unordered_map<char, char> st_t_s;
        for(int i = 0; i < s.size(); i++){
            if(st_s_t.find(s[i])==st_s_t.end() && st_t_s.find(t[i])==st_t_s.end()){
                st_s_t[s[i]] = t[i];
                st_t_s[t[i]] = s[i];
            }else{
                if(st_s_t[s[i]]!=t[i]) return false;
                if(st_t_s[t[i]]!=s[i]) return false;
            }
        }
        return true;
    }
};

int main(){
    Solution a;
    cout << a.isIsomorphic("egg", "add") << endl;
    return 0;
}