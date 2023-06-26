// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    bool wordPattern(string pattern, string s) {
        // split string and save in a vector
        istringstream iss(s);
        string item;
        vector<string> string_vec;
        while(getline(iss, item, ' ')){
            string_vec.push_back(item);
        } 

        if(pattern.size()!=string_vec.size()) return false;

        unordered_map<char, string> pattern_st;
        unordered_map<string, char> word_st;
        for(int i = 0; i < string_vec.size(); i++){
            if(pattern_st.find(pattern[i])!=pattern_st.end()){
                if(pattern_st[pattern[i]]!=string_vec[i]) return false;
            }else if(word_st.find(string_vec[i])!=word_st.end()){
                if(word_st[string_vec[i]]!=pattern[i]) return false;
            }else{
                pattern_st[pattern[i]] = string_vec[i];
                word_st[string_vec[i]] = pattern[i];
            }
        }
        
        return true;
    }
};

int main(){
    string pattern = "abba";
    string s = "dog cat cat dog";

    Solution a;
    cout << a.wordPattern(pattern, s) << endl;

    return 0;
}