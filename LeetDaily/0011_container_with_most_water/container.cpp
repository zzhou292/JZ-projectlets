// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        // edge check
        if(height.size() < 2){
            return 0;
        }


        int max_area = INT_MIN;
        int l = 0;
        int r = height.size()-1;

    
        while(l < r && l >= 0 && r < height.size()){
            
            int area = (r-l)*min(height[l], height[r]);
            if(max_area < area){
                max_area = area;
            }


            if(height[l] < height[r]){
                l++;
            }else if(height[r] < height[l]){
                r--;
            }else{
                l++;
                r--;
            }
        }
        
        return max_area;
    }
};

int main(){
    vector<int> height = {1,8,6,2,5,4,8,3,7};

    Solution a;
    cout << a.maxArea(height) << endl;
}