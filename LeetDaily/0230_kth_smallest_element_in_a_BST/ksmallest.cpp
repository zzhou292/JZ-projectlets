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
    int kthSmallest(TreeNode* root, int k) {
        // edge case
        if(k<=0) return 0;
        if(root==NULL) return 0;

        // use DFS
        stack<TreeNode*> st;
        vector<int> st_vec;

        st.push(root);

        while(!st.empty()){
            TreeNode* cur = st.top();
            st.pop();

            st_vec.push_back(cur->val);

            if(cur->right!=NULL) st.push(cur->right);
            if(cur->left!=NULL) st.push(cur->left);
        }

        sort(st_vec.begin(), st_vec.end());

        return st_vec[k-1];

    }
};