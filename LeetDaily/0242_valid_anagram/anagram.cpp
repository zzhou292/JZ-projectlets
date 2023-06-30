// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        // edge check
        if(s.size()!=t.size()) return false;

        unordered_map<char, int> st;
        for(int i = 0; i < s.size(); i++){
            st[s[i]]++;
        }

        for(int i = 0; i < t.size(); i++){
            st[t[i]]--;

            if(st[t[i]]<0) return false;
        }

        return true;
    }
};

int main(){
    Solution a;
    cout << a.isAnagram("anagram", "nagaram") << endl;
    return 0;
}