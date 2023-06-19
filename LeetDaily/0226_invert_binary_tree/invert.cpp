/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
  TreeNode *invertTree(TreeNode *root) {
    if (root == nullptr)
      return root;

    TreeNode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    // traverse next
    if (root->left != nullptr)
      invertTree(root->left);
    if (root->right != nullptr)
      invertTree(root->right);

    return root;
  }
};