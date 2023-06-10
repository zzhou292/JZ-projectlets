// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int minOperations(string s) {
        int x = 0;
        int y = 0;

        // condition x
        for (int i = 0; i < s.size(); i++){
            if(i%2==0 && s[i]!='0'){
                x++;
            }

            if(i%2==1 && s[i]!='1'){
                x++;
            }
        }

        // condition y
        for (int i = 0; i < s.size(); i++){
            if(i%2==0 && s[i]!='1'){
                y++;
            }

            if(i%2==1 && s[i]!='0'){
                y++;
            }
        }

        return min(x,y);
    }
};

int main(){
    string input("1111");
    
    Solution a;
    cout << a.minOperations(input) << endl;

    return 0;
}