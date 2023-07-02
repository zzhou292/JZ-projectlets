// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        vector<int> st = {0,1,2,3};
        if(n<=3) return st[n];

        for(int i = 4; i <= n;i++){
            st.push_back(st[i-1]+st[i-2]);
        }

        return st[n];
    }
};


int main(){
    Solution a;
    cout << a.climbStairs(45) << endl;
    return 0;
}