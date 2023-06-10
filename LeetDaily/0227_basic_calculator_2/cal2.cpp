// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int calculate(string s) {
  
        const int length = s.length();
  
        // declaring character array (+1 for null terminator)
        char* char_array = new char[length + 1];
  
        // copying the contents of the
        // string to char array
        strcpy(char_array, s.c_str());
        
        stack<int> num_stack;

        int counter = 0;    // count the current loc of read
        int num = 0;
        char operation = '+';

        while(counter < length){
            if (isspace(s[counter])&&counter!=length-1){
                counter++;
                continue;
            }
            if(isdigit(s[counter])){
                num = num*10 + (s[counter] - '0');
                
            }
            
            if(!isdigit(s[counter])|| counter == length-1){
                if(operation == '+'){
                    num_stack.push(num);
                }else if (operation == '-'){
                    num_stack.push(-num);
                }else if (operation == '*'){
                    int temp_res = num_stack.top()*num;
                    num_stack.pop();
                    num_stack.push(temp_res);
                }else if (operation == '/'){
                    int temp_res = num_stack.top()/num;
                    num_stack.pop();
                    num_stack.push(temp_res);
                }

                num = 0;
                operation = s[counter];
            }
            counter++;
        }

        int final_res = 0;
        while(!num_stack.empty()){
            final_res += num_stack.top();
            num_stack.pop();
        }

        return final_res;
    }
};

int main(){
    string input("3+2*2+15-2*2+4/2-1+21/3*7");

    Solution a;
    cout << a.calculate(input) << endl;
}