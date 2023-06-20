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
    int helper(TreeNode* root, int cur_sum){
        if(!root) return 0;
        cur_sum = cur_sum*10 + root->val;
        if(root->left == nullptr && root->right == nullptr){
            return cur_sum;
        }else{
            return helper(root->left,cur_sum) + helper(root->right, cur_sum);
        }
    }

    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        return helper(root, 0);
    }
};