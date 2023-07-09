/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void BalancedBSTUtil(vector<int>& nums, TreeNode* subroot, int side){
        int mid = nums.size()/2;
        TreeNode* next_root;

        if(side==0){
            subroot->left = new TreeNode(nums[mid]);
            next_root = subroot->left;
        }else{
            subroot->right = new TreeNode(nums[mid]);
            next_root = subroot->right;
        }

        if(mid-1>=0){
            vector<int> left_nums;
            left_nums.assign(nums.begin(),nums.begin()+mid);
            BalancedBSTUtil(left_nums, next_root, 0);
        }

        if(mid+1<=nums.size()-1){
            vector<int> right_nums;
            right_nums.assign(nums.begin()+mid+1, nums.end());
            BalancedBSTUtil(right_nums, next_root, 1);
        }
        
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int mid = nums.size()/2;
        TreeNode* root = new TreeNode(nums[mid]);

        if(mid-1>=0){
            vector<int> left_nums;
            left_nums.assign(nums.begin(),nums.begin()+mid);
            BalancedBSTUtil(left_nums, root, 0);
        }

        if(mid+1<=nums.size()-1){
            vector<int> right_nums;
            right_nums.assign(nums.begin()+mid+1, nums.end());
            BalancedBSTUtil(right_nums, root, 1);
        }

        return root;
    }
};