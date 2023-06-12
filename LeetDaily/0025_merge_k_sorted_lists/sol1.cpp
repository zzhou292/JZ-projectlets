
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

// acceptable solution but it is very very slow
// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // edge cases
        if(lists.size()==0) return nullptr;

        // check if all empty
        bool empty_flag = true;
        for(int i = 0; i < lists.size(); i++){
            if(lists[i]!=nullptr){
                empty_flag=false;
                break;
            } 
        }
        if (empty_flag) return nullptr;

        // actual algorithm
        vector<int> temp_val;
        for (int i = 0; i < lists.size(); i++){
            temp_val.push_back(0);
        }

        vector<ListNode*> temp_head;
        for (int i = 0; i < lists.size();i++){
            temp_head.push_back(lists[i]);
        }

        ListNode* head = nullptr;
        ListNode* root = nullptr;

        bool finished = false;

        while(!finished){

            // copy current head value to temp_val
            for (int i = 0; i < temp_head.size(); i++){
                if(temp_head[i]!=nullptr){
                    temp_val[i] = temp_head[i]->val;
                }else{
                    temp_val[i] = INT_MAX;
                }
            }

            // find the minimum value and corresponding idx
            int min_idx = 0;
            int min_val = INT_MAX;
            for (int i = 0; i < temp_val.size(); i++){
                if (temp_val[i] < min_val){
                    min_idx = i;
                    min_val = temp_val[i];
                }
            }

            // add to the new list
            if(head == nullptr){
                ListNode* temp_ele = new ListNode(temp_val[min_idx]);
                head = temp_ele;
                root = head;
            }else{
                ListNode* temp_ele = new ListNode(temp_val[min_idx]);
                head->next = temp_ele;
                head = head->next;
            }
            temp_head[min_idx] = temp_head[min_idx]->next;

            // check if finished
            for (int i = 0; i < temp_head.size(); i++){
                if (temp_head[i]!=nullptr){
                    break;
                }

                if(i==temp_head.size()-1){
                    finished = true;
                }
            }
        }

        return root;
    }
};

int main(){
    ListNode* a1 = new ListNode(1);
    ListNode* a2 = new ListNode(4);
    a1->next = a2;
    ListNode* a3 = new ListNode(5);
    a2->next = a3;

    ListNode* b1 = new ListNode(2);
    ListNode* b2 = new ListNode(6);
    b1->next = b2;

    vector<ListNode*> input = {a1,b1};

    Solution a;
    ListNode* head = a.mergeKLists(input);

    while(head!=nullptr){
        cout << head->val << ", ";
        head = head->next;
    }
    cout << endl;
}