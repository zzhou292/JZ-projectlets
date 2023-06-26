// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>>res;
        sort(intervals.begin(), intervals.end());
        for(int i = 0; i < intervals.size();i++){
            if(res.size()==0 || res.back()[1]<intervals[i][0]){
                res.push_back(intervals[i]);
            }else{
                res[res.size()-1][1] = max(res[res.size()-1][1], intervals[i][1]);
            }
        }
        return res;
    }
}; 

int main(){
    vector<vector<int>> input = {{1,3},{2,6},{8,10},{15,18}};
    Solution a;
    auto output = a.merge(input);
    for(auto i:output){
        cout << i[0] << " " << i[1] << endl;
    }

    return 0;
}