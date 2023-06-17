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
    ListNode* deleteDuplicates(ListNode* head) {
        // edge case
        if (head == nullptr || head->next == nullptr){
            return head;
        }

        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* cur = head;
        ListNode* prev = dummy;
        int prev_val = cur->val;
        bool flag = false;

        while(cur->next!=nullptr){
            cur = cur->next;
            if(prev_val == cur->val){
                flag = true;
            }else{
                if(flag==true){
                    flag = false;
                    prev->next = cur;
                }else{
                    prev = prev->next;
                }
            }
            prev_val = cur->val;
        }

        if(flag == true){
            prev->next = nullptr;
        }

        return dummy->next;
    }
};