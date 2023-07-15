// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    bool checkdiag(vector<int>& cur_sol){
        for(int i = 0; i < cur_sol.size(); i++){
            for(int j = 0; j < cur_sol.size();j++){
                if(i!=j){
                    if(abs(cur_sol[i]-cur_sol[j])==abs(i-j)) return true;
                }
            }
        }

        return false;
    }

    void dfs(vector<int>& cur_sol, int& res, int& n){
        // backtracking termination condition
        if(cur_sol.size()==n){
            if(!checkdiag(cur_sol)){
                res++;return;
            }else{return;}
        }else if(checkdiag(cur_sol)){return;}

       // backtracking dfs procedure
       for(int i = 0; i < n; i++){
           if(count(cur_sol.begin(), cur_sol.end(), i)==0){
                cur_sol.push_back(i);
                dfs(cur_sol, res, n);
                cur_sol.pop_back();
           }
       }
    }

    int totalNQueens(int n) {
        // edge case
        if(n==0) return 0;

        vector<int> cur_sol;
        int res = 0;

        dfs(cur_sol, res, n);

        return res;
    }
};

int main(){
    Solution a;
    cout << a.totalNQueens(5) << endl;

    return 0;
}