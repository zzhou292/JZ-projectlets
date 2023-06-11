// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    vector<int> scan_data;
    Solution(vector<int>& w) {
        int sum = 0;
        for(int i = 0; i < w.size(); i++){
            sum += w[i];
            scan_data.push_back(sum);
        }
    }
    
    int pickIndex() {
        if (scan_data.size()==1){
            return 0;
        }

        // Generate a random number
        int randomNum = rand()%scan_data[scan_data.size()-1];
    
        // Search for the random number
        auto it = upper_bound(scan_data.begin(), scan_data.end(), randomNum);
        return it - scan_data.begin();
        
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */

 int main(){
    vector<int> input = {1,3};
    
    Solution a(input);

    for (int i = 0; i < 200; i++){
        cout << a.pickIndex() << " ";
    }
    cout << endl;
    
 }