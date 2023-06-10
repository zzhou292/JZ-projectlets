// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> m_stk;


        for(char c : s){
            if(c=='{' || c=='(' || c=='['){
                m_stk.push(c);
            }else{
                if(m_stk.empty()){
                    return false;
                }else if(c=='}'){
                    if(m_stk.top()=='{'){
                        m_stk.pop();
                    }else{
                        return false;
                    }
                }else if(c==')'){
                    if(m_stk.top()=='('){
                        m_stk.pop();
                    }else{
                        return false;
                    }
                }else if(c==']'){
                    if(m_stk.top()=='['){
                        m_stk.pop();
                    }else{
                        return false;
                    }
                }
            }
        }

        if(m_stk.empty()){
            return true;
        }else{
            return false;
        }
    }
};

int main(){
    string input("()[]{}");

    Solution a;
    cout << a.isValid(input) << endl;

    return 0;
}