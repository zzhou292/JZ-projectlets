// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        // edge case
        if(magazine.size()==0) return false;

        // main algorithm
        // read and store magazine
        unordered_map<char,int> st;
        for(int i = 0; i < magazine.size(); i++){
            st[(char)magazine[i]]++;
        }   

        for(int i = 0; i < ransomNote.size(); i++){
            st[(char)ransomNote[i]]--;
            if(st[(char)ransomNote[i]]<0) return false;
        }
        
        return true;
    }
};

int main(){
    string note("aa");
    string magazine("aab");

    Solution a;
    cout << a.canConstruct(note, magazine) << endl;

    return 0;
}