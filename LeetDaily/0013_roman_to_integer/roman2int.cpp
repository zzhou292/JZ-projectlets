// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        int res = 0;

        vector<string> ro_vec = {"M","D","C","L","X","V","I"};
        vector<int> val_vec = {1000,500,100,50,10,5,1};

        vector<string> off_ro_vec = {"CM","CD","XC","XL","IX","IV"};
        vector<int> off_val_vec = {900,400,90,40,9,4};
    
        int counter = 0;
        for(int i = 0; i < ro_vec.size();i++){
            while(s.substr(counter, 1)==ro_vec[i]){
                res += val_vec[i];
                counter+=1;
            }

            while(i!=ro_vec.size()-1 && s.substr(counter, 2)==off_ro_vec[i]){
                res += off_val_vec[i];
                counter+=2;
            }
        }

        return res;

    }
};

int main(){
    Solution a;
    cout << a.romanToInt("MCMXCIV") << endl;

    return 0;
}