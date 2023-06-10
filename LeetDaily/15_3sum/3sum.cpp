#include "../general_include.h"

using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::set<vector<int>> return_set;

        sort(nums.begin(),nums.end());
        for (int i = 0; i < nums.size(); i++){
            int j = i + 1;
            int k = nums.size()-1;

            while(j < k){
                int sum = nums[i] + nums[j] + nums[k];
                if (sum == 0){
                    return_set.insert({nums[i], nums[j], nums[k]});
                    j++;
                    k--;
                } else if (sum < 0){
                    j++;
                } else {
                    k--;
                }
            }

        }

        std::vector<vector<int>> return_vec;
        return_vec.assign(return_set.begin(), return_set.end());
        return return_vec;
    }
};

int main() {
    vector<int> input = {-1,0,1,2,-1,-4};
    Solution a;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> output = a.threeSum(input);

    // ==================================
    // ===== print out data =============
    for(int i = 0; i < output.size(); i++)
    {   
        std::cout << "[";
        for(int j = 0; j < output[i].size();j++){
            std::cout << output[i][j]<<" ";
        }
        std::cout << "]; ";
    }
    std::cout << std::endl;
    // ====================================

    // End the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    std::chrono::duration<double> duration = end - start;

    // Print the runtime in seconds
    std::cout << "Runtime: " << duration.count() << " seconds" << std::endl;

    return 0;
}