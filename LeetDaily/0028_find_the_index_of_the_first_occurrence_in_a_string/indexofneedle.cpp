// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int len = needle.size();
        // edge case
        if(len > haystack.size()){
            return -1;
        }


        for (int i = 0; i < haystack.size()-(len-1);i++){
            string sub = haystack.substr(i, len);
            if(sub == needle){
                return i;
            }
        }

        return -1;
    }
};

int main(){
    string haystack = "jason wowowowwowow love yirui";
    string needle = "yirui";

    Solution a;
    cout << a.strStr(haystack, needle) << endl;

    return 0;
}