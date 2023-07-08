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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        
        // edge case
        if(root==NULL) return res;

        // BFS
        queue<pair<int, TreeNode*>> que;
        int cur_lv = 0;
        que.push({0, root});

        vector<int> cur_vec;

        while(!que.empty()){
            pair<int, TreeNode*> itm = que.front();
            que.pop();
            TreeNode* cur = itm.second;
            
            if(cur_lv == itm.first){
                cur_vec.push_back(cur->val);
            }else{
                res.push_back(cur_vec);
                vector<int> temp;
                cur_vec = temp;
                cur_vec.push_back(cur->val);
                cur_lv = itm.first;
            }

            if(cur->left!=NULL) que.push({cur_lv+1, cur->left});
            if(cur->right!=NULL) que.push({cur_lv+1, cur->right});
        }

        if(cur_vec.size()!=0) res.push_back(cur_vec);

        return res;
    }
};