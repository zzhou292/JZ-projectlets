// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    string addBinary(string a, string b) {
        string res="";
        int m = a.size()-1;
        int n = b.size()-1;
        int carry = 0;

        while(m>=0 && n>=0){
            int temp_a = (a[m]=='1'?1:0);
            int temp_b = (b[n]=='1'?1:0);
            res = to_string((temp_a+temp_b+carry)%2)+res;
            carry = (temp_a+temp_b+carry)/2;
            m--;
            n--;
        }

        while(m>=0){
            int temp_a = (a[m]=='1'?1:0);
            res = to_string((temp_a+carry)%2)+res;
            carry = (temp_a+carry)/2;
            m--;
        }


        while(n>=0){
            int temp_b = (b[n]=='1'?1:0);
            res = to_string((temp_b+carry)%2)+res;            
            carry = (temp_b+carry)/2;
            n--;
        }

        if(carry!=0) res = "1"+res;

        return res;
    }
};

int main(){
    string input_1 = "111";
    string input_2 = "1";

    Solution a;
    cout << a.addBinary(input_1, input_2) << endl;

    return 0;
}