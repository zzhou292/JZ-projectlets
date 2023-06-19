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
    TreeNode* construct(int poststart,int postend, vector<int> &postorder, int instart, int inend, vector<int> &inorder, map<int,int> &mp){
        if(poststart>postend || instart>inend) return NULL;
        TreeNode* root=new TreeNode(postorder[postend]);
        int root_idx=mp[root->val];
        int nelements_r=inend-root_idx;
        root->left=construct(poststart,postend-nelements_r-1,postorder,instart,root_idx-1,inorder,mp);
        root->right=construct(postend-nelements_r,postend-1,postorder,root_idx+1,inend,inorder,mp);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        map<int,int> mp;
        for(int i=0;i<inorder.size();i++) mp[inorder[i]]=i;
        TreeNode* root= construct(0,postorder.size()-1,postorder,0,inorder.size()-1,inorder,mp);
        return root;
    }
};