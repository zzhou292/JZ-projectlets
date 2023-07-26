// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        string roman;

        vector<char> ro_vec = {'M','D','C','L','X','V','I'};
        vector<int> val_vec = {1000,500,100,50,10,5,1};

        vector<string> off_ro_vec = {"CM","CD","XC","XL","IX","IV"};
        vector<int> off_val_vec = {900,400,90,40,9,4};
    
        for(int i = 0; i < ro_vec.size(); i++){
            while(num/val_vec[i]){
                roman += ro_vec[i];
                num = num - val_vec[i];
            }

            if(i!=ro_vec.size()-1 && num/off_val_vec[i]!=0){
                roman += off_ro_vec[i];
                num = num - off_val_vec[i];
            }
        }

        return roman;

    }
};

int main(){
    Solution a;
    cout << a.intToRoman(1994) << endl;

    return 0;
}