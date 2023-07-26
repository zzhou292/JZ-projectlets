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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // edge case
        if(head == NULL) return head;

        // count number of eles
        int count = 1;
        ListNode* cur = head;
        while(cur->next!=NULL){
            cur = cur->next;
            count++;
        }

        // count
        int target = count - n;
        cout << target << endl;
        int count_1 = 1;
        cur = head;

        if(n==count){
            head = head->next;
        }else{
            while(cur->next!=NULL){
                if(count_1 == target){
                    cur->next = cur->next->next;
                    break;
                }

                cur = cur->next;
                count_1++;
            }
        }


        return head;
    }
};