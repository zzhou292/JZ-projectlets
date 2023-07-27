// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    string reverseWords(string s) {
        // edge case
        if(s.size() == 0 || s.size() == 1) return s;

        int counter = 0;
        string temp;
        vector<string> str_vec; 
        while(counter <= s.size()-1){
            if(s[counter] == ' '){
                if(temp.size()!=0){
                    str_vec.push_back(temp);
                    temp = "";
                }

            }else{
                temp = temp + s[counter];
            }
            counter++;
        }

        if(temp.size()!=0) str_vec.push_back(temp);

        string res;
        for(int i = 0; i < str_vec.size(); i++){
            res = res+str_vec[str_vec.size()-1-i];
            if(i!=str_vec.size()-1) res = res+" ";

        }

        return res;
    }
};

int main(){
    Solution a;
    cout << a.reverseWords("a good   example") << endl;

    return 0;
}