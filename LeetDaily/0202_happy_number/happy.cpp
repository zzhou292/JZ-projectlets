

// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int next_helper(int n){
        int res = 0;
        while(n/10!=0){
            res = res + (n%10) * (n%10);
            n = n/10;
        }
        res = res+(n%10)*(n%10);
        return res;
    }

    bool isHappy(int n) {

        vector<int> num_comb;
        unordered_set<int> st;
        st.insert(n);
        while(n!=1){
            n = next_helper(n);
            if(st.find(n)!=st.end()) return false;
            st.insert(n);
        }

        return true;
    }
};

int main(){
    Solution a;
    cout << a.isHappy(19) << endl;


    return 0;
}