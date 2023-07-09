// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    int hammingWeight(uint32_t n) {
        uint32_t mask = 1;
        int cnt = 0;
        for(int i = 0; i < 32; i++){
            uint32_t cur_mask = mask << i;
            if(cur_mask == (cur_mask & n)){
                cnt++;
            }
        }
        return cnt;
    }
};

int main(){
    uint32_t input = 13;

    Solution a;
    cout << a.hammingWeight(input) << endl;

    return 0;
}