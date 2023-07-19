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
    ListNode* sortList(ListNode* head) {
        if(head==NULL || head->next==NULL){return head;}

        // two pointer splitting method
        ListNode* temp = head;
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast!=NULL && fast->next!=NULL){
            temp = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        temp->next = NULL;

        ListNode* left = sortList(head);
        ListNode* right = sortList(slow);

        ListNode* fake_head = new ListNode(0);
        ListNode* real_head = fake_head; 
        while(left !=NULL && right != NULL){
            if(left->val <= right->val){
                fake_head->next = left;
                left = left->next;
            }else{
                fake_head->next = right;
                right = right->next;
            }
            fake_head = fake_head->next;
        }

        if(left!=NULL){
            fake_head->next = left;
            left = left->next;
        }

        if(right!=NULL){
            fake_head->next = right;
            right = right->next;
        }

        return real_head->next;
    }
};