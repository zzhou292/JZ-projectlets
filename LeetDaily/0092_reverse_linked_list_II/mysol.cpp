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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // edge cases
        if(left==right){
            return head;
        }

        if(head==nullptr){
            return head;
        }

        // algorithm
        int count = 1;
        ListNode* prev = nullptr;
        ListNode* cur = head;
        ListNode* next = head->next;
        while(count < left){
            prev = cur;
            cur = cur->next;
            next = cur->next;
            count++;
        }

        ListNode* l_b = prev;
        ListNode* r_b = cur;

        // start reversing
        while(count <= right){
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
            count++;
        }

        if(l_b==nullptr){
            head = prev;
            r_b->next = cur;
        }else{
            l_b->next = prev;
            r_b->next = cur;
        }
    

        return head;
    }
};