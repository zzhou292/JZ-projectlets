// Author: Jason Zhou
// this is a stack implementation 
// intuition might say that a queue should be used, but that is incorrect due to the existence of "/../" symbol
#include "../general_include.h"

using namespace std;

class Solution {
public:

    // "/", "//", "..", "."
    string simplifyPath(string path) {
        // edge case 
        if(path.size()==0) return "";

        stack<string> st;
        for(int i = 0; i < path.size();i++){
            if(path[i]=='/') continue;
            
            string temp;
            while(i < path.size() && path[i]!='/'){
                temp=temp+path[i];
                i++;
            }

            if(temp==".") continue;
            if(temp==".."){
                if(!st.empty()) st.pop();
                continue;
            }

            st.push(temp);
        }

        string res;
        while(!st.empty()){
            res = "/" + st.top() + res;
            st.pop();
        }
        if (res=="") res=res+"/";
        return res;
    }
};

int main(){
    string input = "/home//foo/";
    
    Solution a;
    cout << a.simplifyPath(input) << endl;
    return 0;
}