// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

// this is a very good solution with O(n^2)

class Solution {
public:
    string longestPalindrome(string s) {
        int max_len = INT_MIN;
        string res;

        // odd case
        int l = 0;
        int r = 0;
        for(int i = 0; i < s.size(); i++){
            l = i;
            r = i;
            while(l >= 0 && r < s.size() && s[l] == s[r]){
                if(max_len < r-l+1){
                    max_len = r-l+1;
                    res = s.substr(l, r-l+1);
                }
                l--;
                r++;
            }
        }

        // even case
        for(int i = 0; i < s.size(); i++){
            l = i;
            r = i+1;
            while(l >= 0 && r < s.size() && s[l] == s[r]){
                if(max_len < r-l+1){
                    max_len = r-l+1;
                    res = s.substr(l, r-l+1);
                }
                l--;
                r++;
            }
        }

        return res;
        
    }
};

int main(){
    string str("jrjnbctoqgzimtoklkxcknwmhiztomaofwwzjnhrijwkgmwwuazcowskjhitejnvtblqyepxispasrgvgzqlvrmvhxusiqqzzibcyhpnruhrgbzsmlsuacwptmzxuewnjzmwxbdzqyvsjzxiecsnkdibudtvthzlizralpaowsbakzconeuwwpsqynaxqmgngzpovauxsqgypinywwtmekzhhlzaeatbzryreuttgwfqmmpeywtvpssznkwhzuqewuqtfuflttjcxrhwexvtxjihunpywerkktbvlsyomkxuwrqqmbmzjbfytdddnkasmdyukawrzrnhdmaefzltddipcrhuchvdcoegamlfifzistnplqabtazunlelslicrkuuhosoyduhootlwsbtxautewkvnvlbtixkmxhngidxecehslqjpcdrtlqswmyghmwlttjecvbueswsixoxmymcepbmuwtzanmvujmalyghzkvtoxynyusbpzpolaplsgrunpfgdbbtvtkahqmmlbxzcfznvhxsiytlsxmmtqiudyjlnbkzvtbqdsknsrknsykqzucevgmmcoanilsyyklpbxqosoquolvytefhvozwtwcrmbnyijbammlzrgalrymyfpysbqpjwzirsfknnyseiujadovngogvptphuyzkrwgjqwdhtvgxnmxuheofplizpxijfytfabx");

    Solution a;
    cout << a.longestPalindrome(str) << endl;

}
