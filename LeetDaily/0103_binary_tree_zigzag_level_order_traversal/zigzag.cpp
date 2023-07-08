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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;

        //edge case
        if(root==NULL) return res;

        stack<TreeNode*> st;
        st.push(root);
        bool zig = true;

        while(!st.empty()){
            vector<TreeNode*> temp_st;
            vector<int> temp;

            while(!st.empty()){
                temp_st.push_back(st.top());
                st.pop();
            }
            
            for(int i = 0; i < temp_st.size(); i++){
                TreeNode* cur = temp_st[i];
                
                temp.push_back(cur->val);

                if(zig){
                    if(cur->left!=NULL) st.push(cur->left);
                    if(cur->right!=NULL) st.push(cur->right); 
                }else{
                    if(cur->right!=NULL) st.push(cur->right);
                    if(cur->left!=NULL) st.push(cur->left); 
                }
            }
            
            zig = !zig;
            res.push_back(temp);
        }

        return res;
    }
};