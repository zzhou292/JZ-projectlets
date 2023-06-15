// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

// this is a brute force solution with time complexity O(n^3)
// CPP LTE

class Solution {
public:

    bool checkSym(string s){
        string temp;
        for(int i = s.size()-1; i >= 0; i--){
            temp += s[i];
        }

        if(s == temp){
            return true;
        }else{
            return false;
        }
    }

    string longestPalindrome(string s) {
        int max_len = INT_MIN;
        string res_str;
        for(int i = 0; i < s.size(); i++){
            for(int j = i; j < s.size(); j++){
                string cut_str = s.substr(i,j-i+1);
                
                if (checkSym(cut_str)){
                    if(max_len < j-i+1){
                        max_len = j-i+1;
                        res_str = cut_str;
                    }
                }
            }
        }

        return res_str;
    }
};


int main(){
    string str("jrjnbctoqgzimtoklkxcknwmhiztomaofwwzjnhrijwkgmwwuazcowskjhitejnvtblqyepxispasrgvgzqlvrmvhxusiqqzzibcyhpnruhrgbzsmlsuacwptmzxuewnjzmwxbdzqyvsjzxiecsnkdibudtvthzlizralpaowsbakzconeuwwpsqynaxqmgngzpovauxsqgypinywwtmekzhhlzaeatbzryreuttgwfqmmpeywtvpssznkwhzuqewuqtfuflttjcxrhwexvtxjihunpywerkktbvlsyomkxuwrqqmbmzjbfytdddnkasmdyukawrzrnhdmaefzltddipcrhuchvdcoegamlfifzistnplqabtazunlelslicrkuuhosoyduhootlwsbtxautewkvnvlbtixkmxhngidxecehslqjpcdrtlqswmyghmwlttjecvbueswsixoxmymcepbmuwtzanmvujmalyghzkvtoxynyusbpzpolaplsgrunpfgdbbtvtkahqmmlbxzcfznvhxsiytlsxmmtqiudyjlnbkzvtbqdsknsrknsykqzucevgmmcoanilsyyklpbxqosoquolvytefhvozwtwcrmbnyijbammlzrgalrymyfpysbqpjwzirsfknnyseiujadovngogvptphuyzkrwgjqwdhtvgxnmxuheofplizpxijfytfabx");

    Solution a;
    cout << a.longestPalindrome(str) << endl;

}