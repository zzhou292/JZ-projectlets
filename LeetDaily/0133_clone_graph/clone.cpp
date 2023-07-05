/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        // edge case
        if(node==nullptr) return nullptr;

        unordered_map<int, Node*> new_map;
        vector<int> visited;
        stack<Node*> old_st;
        Node* root;
        old_st.push(node);

        while(!old_st.empty()){
            Node* original = old_st.top();
            old_st.pop();

            int old_val = original->val;
            vector<Node*> old_vec = original->neighbors;

            // create new nodes
            Node* new_node;
            vector<Node*> new_neighbour_vec;
            if(new_map.count(old_val)==0){
                new_node = new Node(old_val);
                new_map[new_node->val]=new_node;
            }else{
                new_node = new_map[old_val];
            }
            
            // push old neighbours to stack
            for(int i = 0; i < old_vec.size(); i++){
                if(find(visited.begin(), visited.end(), old_vec[i]->val)==visited.end()){
                    old_st.push(old_vec[i]);
                }
                
                if(new_map.count(old_vec[i]->val)==0){
                    Node* new_neighbour_node = new Node(old_vec[i]->val);
                    new_map[old_vec[i]->val] = new_neighbour_node;
                    new_neighbour_vec.push_back(new_neighbour_node);
                }else{
                    new_neighbour_vec.push_back(new_map[old_vec[i]->val]);
                }
                
            }
            new_node->neighbors = new_neighbour_vec;

            visited.push_back(new_node->val);

            if(visited.size()==1) root = new_node;
        }

        return root;
    }
};