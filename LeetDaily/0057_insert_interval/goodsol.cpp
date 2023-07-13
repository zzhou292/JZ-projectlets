// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        
        for(int i = 0; i < intervals.size();i++){
            if(intervals[i][1] < newInterval[0]){
                res.push_back(intervals[i]);
            }else if(intervals[i][0] > newInterval[1]){
                res.push_back(newInterval);
                newInterval = intervals[i];
            }else if(intervals[i][1] >= newInterval[0] || intervals[i][0] <= newInterval[1]){
                newInterval[0] = min(intervals[i][0], newInterval[0]);
                newInterval[1] = max(intervals[i][1], newInterval[1]);
            }
        }

        res.push_back(newInterval);

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