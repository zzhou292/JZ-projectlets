/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        //edge case
        if(head == nullptr){
            return head;
        }
        
        map<Node*, Node*> node_map; // pair<old, new>
        Node* root = new Node(-1);
        Node* cur = root;
        Node* head_dup = head;
        
        while(head!=nullptr){
            cur->next = new Node(head->val);
            cur = cur->next;
            node_map.insert(make_pair(head, cur));
            head = head->next;
        }

        root = root->next;
        cur = root;

        while(head_dup!=nullptr){
            if(head_dup->random == nullptr){
                node_map[head_dup]->random = nullptr;
            }else{
                node_map[head_dup]->random = node_map[head_dup->random];
            }
            head_dup = head_dup->next;
            cur = cur->next;
        }

        return root;        
    }
};