// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        // edge case
        if(x==0) return 0;
        if(x==1) return 1;

        int l = 1; int r = x/2;
        long mid = (l+r)/2;
        while(l<=r){
            if((mid*mid)==x) return mid;

            if(mid*mid>x){
                r=mid-1;
            }else{
                l=mid+1;
            }

            mid = (l+r)/2;
        }
        return mid;
    }
};

int main(){
    Solution a;
    cout << a.mySqrt(16) << endl;

    return 0;
}