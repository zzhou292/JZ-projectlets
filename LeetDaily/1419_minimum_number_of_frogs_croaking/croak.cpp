// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        // edge case if not dividable by 5
        if (croakOfFrogs.size()%5!=0){
            return -1;
        }

        int arr_str[croakOfFrogs.size()];
        int cnt[5];
        int global_res = 0;
        for (int i = 0; i < 5; i++){
            cnt[i]=0;
        }

        for (int i = 0; i < croakOfFrogs.size(); i++){
            // convert string to a int arr
            // 0->c 1->r 2->o 3->a 4->k
            if (croakOfFrogs[i]-'a'== 2)
                arr_str[i] = 0;
            else if (croakOfFrogs[i]-'a'== 17)
                arr_str[i] = 1;
            else if (croakOfFrogs[i]-'a' == 14)
                arr_str[i] = 2;
            else if (croakOfFrogs[i]-'a' == 0)
                arr_str[i] = 3;
            else if (croakOfFrogs[i]-'a' == 10)
                arr_str[i] = 4;
            
            // find previous and check
            // handle case 'c'
            if(arr_str[i] == 0){
                cnt[0]++;
            }else{
                int prev_idx = arr_str[i]-1;
                if(cnt[prev_idx] == 0){
                    return -1;
                }else{
                    cnt[prev_idx]--;
                    cnt[arr_str[i]]++;
                }
            }

            // count current max number of frog
            int cur_res = cnt[0]+cnt[1]+cnt[2]+cnt[3];
            if (cur_res > global_res){
                global_res = cur_res;
            }
        }

                    
        // check if all frogs finish properly
        if(cnt[0]+cnt[1]+cnt[2]+cnt[3]!=0){
            return -1;
        }else{
            return global_res;
        }
    }
};

int main(){
    string input("crcoakroak");
    Solution a;
    cout << a.minNumberOfFrogs(input) << endl;
}