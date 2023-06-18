// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int h_idx = min(citations[citations.size()-1],(int)citations.size());
        if(h_idx == 0) return 0;
        while(h_idx>0){
            if(citations[citations.size()-h_idx]<h_idx) h_idx--;
            if(h_idx<=citations[citations.size()-h_idx]) return h_idx; 
        }
        
        return 0;
    }
};

int main(){
    vector<int> input = {0,1,3,5,6};

    Solution a;
    cout << a.hIndex(input) << endl;

    return 0;
}