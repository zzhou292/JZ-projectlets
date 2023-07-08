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
    int getMinimumDifference(TreeNode* root) {
        // edge case
        if(root==NULL) return 0;

        // use DFS
        int prev_val;
        int mini_dist = INT_MAX;

        stack<TreeNode*> st;
        st.push(root);

        vector<int> st_vec;

        while(!st.empty()){
            TreeNode* cur = st.top();
            st.pop();

            if(cur->right!=NULL) st.push(cur->right);
            if(cur->left!=NULL) st.push(cur->left);
            

            st_vec.push_back(cur->val);
        }

        sort(st_vec.begin(), st_vec.end());

        for(int i = 1; i < st_vec.size(); i++){
            mini_dist = min(mini_dist, st_vec[i]-st_vec[i-1]);
        }

        return mini_dist;
    }
};