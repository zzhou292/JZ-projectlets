// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        intervals.push_back(newInterval);
        sort(intervals.begin(),intervals.end());
        
        for(int i = 0; i < intervals.size();i++){
            if(res.size()==0 || res[res.size()-1][1] < intervals[i][0]){
                res.push_back(intervals[i]);
            }else{
                res[res.size()-1][1] = max(res[res.size()-1][1], intervals[i][1]);
            }
        }

        return res;
    }
};

int main(){
    vector<int> new_interval = {2,5};

    vector<int> vec1 = {1,3};
    vector<int> vec2 = {6,9};
    vector<vector<int>> input = {vec1, vec2};

    Solution a;
    vector<vector<int>> res = a.insert(input, new_interval);

    for(int i = 0; i < res.size();i++){
        cout <<"[" << res[i][0] << ", "<<res[i][1] << "]" << endl;
    }

    return 0;
}