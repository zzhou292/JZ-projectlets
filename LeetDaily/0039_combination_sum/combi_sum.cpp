// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:

    void dfs(vector<vector<int>>& res, vector<int>& cur, vector<int>& candidates, int index, int& target){
        int sum = 0;
        for(int i = 0; i < cur.size(); i++){
            sum+=cur[i];
        }

        // termination conditions
        if(sum==target){
            res.push_back(cur);
            return;
        }else if(index>candidates.size()-1){
            return;
        }

        for(int i = index; i < candidates.size();i++){
            if(sum+candidates[i]<=target){
                cur.push_back(candidates[i]);
                dfs(res,cur,candidates,i,target);
                cur.pop_back();
            }
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> cur;

        // edge case
        if(candidates.size()==0) return res;

        dfs(res,cur,candidates,0,target);

        return res;
    }
};

int main(){
    vector<int> candidates = {2,3,6,7};
    int target = 7;


    Solution a;
    vector<vector<int>> res = a.combinationSum(candidates, target);

    for(int i = 0; i < res.size(); i++){
        for(int j = 0; j < res[i].size();j++){
            cout << res[i][j] << ",";
        }
        cout << endl;
    }

    return 0;
}