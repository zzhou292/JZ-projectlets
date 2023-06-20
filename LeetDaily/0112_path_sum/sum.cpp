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
    bool helper(TreeNode* root, int curSum, int& targetSum, bool isValid){
        if(root == nullptr && isValid) return curSum == targetSum;
        if(root == nullptr) return false;

        bool valid = root->left==nullptr && root->right==nullptr;
        bool left_b=helper(root->left, curSum+root->val, targetSum, valid);
        bool right_b=helper(root->right, curSum+root->val, targetSum, valid);

        return left_b || right_b;
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root==nullptr) return false;
        bool valid = root->left==nullptr && root->right==nullptr;
        return helper(root, 0, targetSum, valid);
    }
};