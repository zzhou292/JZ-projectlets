// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        vector<int> left_max_data(height.size());
        vector<int> right_max_data(height.size());
        
        left_max_data[0] = height[0];
        right_max_data[height.size()-1] = height[height.size()-1];

        for (int i = 1; i < height.size(); i++){
            left_max_data[i] = max(left_max_data[i-1], height[i]);
        }

        for (int i = height.size()-2; i >= 0; i--){
            right_max_data[i] = max(right_max_data[i+1], height[i]);
        }

        for (int i = 0; i < height.size(); i++){
            ans += (min(left_max_data[i], right_max_data[i]) - height[i]);
        }

        return ans; 
    }
};

int main(){
    vector<int> input = {0,1,0,2,1,0,1,3,2,1,2,1};

    Solution a;
    cout << a.trap(input) << endl;

    return 0;
}