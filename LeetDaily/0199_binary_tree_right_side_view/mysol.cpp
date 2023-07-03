// this is a good and acceptable solution, but not the best.

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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        vector<TreeNode*> st;

        if(root==nullptr) return res;

        st.push_back(root);

        while(st.size()!=0){
            vector<int> temp_level;
            vector<TreeNode*> temp_ptr;
            for(auto& i:st){
                temp_level.push_back(i->val);
                if(i->left!=nullptr) temp_ptr.push_back(i->left);
                if(i->right!=nullptr) temp_ptr.push_back(i->right);
            }
            res.push_back(temp_level[temp_level.size()-1]);
            st = temp_ptr;
        }

        return res;
    }
};