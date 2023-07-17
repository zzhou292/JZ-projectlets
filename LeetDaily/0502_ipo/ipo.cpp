// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        // edge case
        if(profits.size()!=capital.size()||
            k <= 0 ||
            w < 0){
                return w;
            }

        priority_queue<int> qe;
        vector<pair<int,int>> st;
        for(int i = 0; i < profits.size(); i++){
            st.push_back({capital[i], profits[i]});
        }

        sort(st.begin(), st.end());

        int cur_cap = w;
        int p = 0;

        for(int i = 0; i < k; i++){
            while(p<st.size() && st[p].first <= cur_cap){
                qe.push(st[p].second);
                p++;
            }
            
            if(qe.empty()) return cur_cap;
            cur_cap += qe.top();
            qe.pop();
        }

        return cur_cap;
    }
};

int main(){
    vector<int> profits = {1,2,3};
    vector<int> capitals = {0,1,1};

    Solution a;
    cout << a.findMaximizedCapital(2,0,profits,capitals) << endl;

    return 0;
}