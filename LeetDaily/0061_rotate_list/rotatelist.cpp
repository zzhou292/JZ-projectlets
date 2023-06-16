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
  ListNode *rotateRight(ListNode *head, int k) {
    // edge case
    if (head == nullptr) {
      return head;
    }

    vector<int> st;
    st.push_back(head->val);

    while (head->next != nullptr) {
      head = head->next;
      st.push_back(head->val);
    }

    k = k % st.size();

    // recreate list - rotated part
    ListNode *cur = nullptr;
    ListNode *root = nullptr;
    int counter = 0;
    for (int a = k - 1; a >= 0; a--) {
      int idx = st.size() - 1 - a;
      if (counter == 0) {
        ListNode *temp = new ListNode(st[st.size() - 1 - a]);
        cur = temp;
        root = temp;
      } else {
        ListNode *temp = new ListNode(st[st.size() - 1 - a]);
        cur->next = temp;
        cur = cur->next;
      }
      counter++;
    }

    // recreate list - orginal
    for (int a = 0; a < st.size() - k; a++) {
      int idx = a;
      if (a >= 0) {
        if (counter == 0) {
          ListNode *temp = new ListNode(st[a]);
          cur = temp;
          root = cur;
        } else {
          ListNode *temp = new ListNode(st[a]);
          cur->next = temp;
          cur = cur->next;
        }
        counter++;
      }
    }

    return root;
  }
};