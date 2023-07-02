// Author: Jason Zhou
// It's a easy but tricky math problem
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int trailingZeroes(int n) {
        int count = 0 ;
        for (int i = 5; n / i >= 1; i *= 5){
            count += n / i;
        }
        return count;
        
    }
};

int main(){
    Solution a;
    cout << a.trailingZeroes(5) << endl;

    return 0;
}