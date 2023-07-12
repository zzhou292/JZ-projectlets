/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        // edge case
        if(head == nullptr) return head;

        vector<ListNode*> st_1;
        vector<ListNode*> st_2;
        ListNode* cur = head;

        // scan and partition
        while(cur!=nullptr){
            if(cur->val < x){
                st_1.push_back(cur);
            }else{
                st_2.push_back(cur);
            }
            cur=cur->next;
        }

        // lump together
        for(ListNode* itm:st_2){
            st_1.push_back(itm);
        }

        // reconnect
        for(int i = 0; i < st_1.size()-1; i++){
            st_1[i]->next = st_1[i+1];
        }

        st_1[st_1.size()-1]->next = NULL;

        return st_1[0];
    }
};