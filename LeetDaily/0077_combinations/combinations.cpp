// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    void dfs(vector<vector<int>>& res, vector<int>& cur_sol, int& n, int& k, int start){
        // backtracking terminal conditions
        if(cur_sol.size()==k) res.push_back(cur_sol);

        for(int i = start; i <= n; i++){
            cur_sol.push_back(i);
            dfs(res,cur_sol,n,k, i+1);
            cur_sol.pop_back();
        } 
    }


    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;

        // edge case
        if(n==0 || k==0 || k>n) return res;

        vector<int> cur_sol;

        dfs(res,cur_sol,n,k,1);

        return res;
    }
};

int main(){
    Solution a;
    vector<vector<int>> res = a.combine(4,2);

    for(int i = 0; i < res.size(); i++){
        for(int j = 0; j < res[i].size();j++){
            cout << res[i][j] << ",";
        }
        cout << "--"<<endl;
    }

    return 0;
}