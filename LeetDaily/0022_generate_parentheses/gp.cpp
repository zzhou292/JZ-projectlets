// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    void dfs(vector<string>& res, string& cur_sol, int& n, int open, int end){
        // backtracking terminal conditions
        if(cur_sol.size()==2*n){
            res.push_back(cur_sol);
            return;
        }

        if(open < n){
            if(open>end){
                // a-> we add an open
                cur_sol = cur_sol + '(';
                dfs(res, cur_sol,n,open+1, end);
                cur_sol.erase(cur_sol.size()-1);

                // b-> we add an end
                cur_sol = cur_sol+')';
                dfs(res, cur_sol, n, open, end+1);
                cur_sol.erase(cur_sol.size()-1);
            }else{
                // the only choice is to add an open
                cur_sol = cur_sol+'(';
                dfs(res,cur_sol,n,open+1,end);
                cur_sol.erase(cur_sol.size()-1);
            }
        }else{
            // the only choice is to add an end
            cur_sol = cur_sol+')';
            dfs(res, cur_sol, n, open, end+1);
            cur_sol.erase(cur_sol.size()-1);
        }
        
    }

    vector<string> generateParenthesis(int n) {
        vector<string> res;

        // edge case
        if(n==0) return res;
        string cur_sol;
        int open = 0;
        int end = 0;

        dfs(res,cur_sol, n, open, end);

        return res;
    }
};

int main(){
    Solution a;
    vector<string> res = a.generateParenthesis(5);

    for(int i = 0; i < res.size(); i++){
        cout << res[i] << endl;
    }

    return 0;
}