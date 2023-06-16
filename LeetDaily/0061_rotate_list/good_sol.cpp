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
// Author: Jason Zhou
// this is the goood solution
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr || head->next == nullptr){
            return head;
        }

        ListNode* dummy = head;
        int len = 1;
        while(dummy->next!=nullptr){
            len++;
            dummy=dummy->next;
        }

        // now we reach the end
        dummy->next = head;
        int count = len-(k%len);
        while(count>0){
            dummy = dummy->next;
            count--;
        }

        // read new root
        ListNode* new_head = dummy->next;
        // cut it
        dummy->next = nullptr;

        return new_head;


    }
};