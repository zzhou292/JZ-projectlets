// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    int lengthOfLastWord(string s) {
        int cnt = s.size()-1;
        int res = 0;
        while(cnt >= 0){
            char c = s[cnt];
            if(c!=' '){
                res++;
            }

            if(res!=0 && c==' '){
                break;
            }

            cnt--;
        }

        return res;
    }
};

int main(){
    string input = "jason is amazing";
    
    Solution a;
    cout << a.lengthOfLastWord(input) << endl;

    return 0;
}