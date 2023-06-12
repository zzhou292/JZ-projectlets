
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

// the key to this solution is a quicksort algorithm
// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    // Partition the vector and return the index of the pivot
    int partition(std::vector<int>& nums, int low, int high) {
        int pivot = nums[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (nums[j] <= pivot) {
                i++;
                std::swap(nums[i], nums[j]);
            }
        }

        std::swap(nums[i + 1], nums[high]);
        return i + 1;
    }

    // Quicksort algorithm
    void quicksort(std::vector<int>& nums, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(nums, low, high);
            quicksort(nums, low, pivotIndex - 1);
            quicksort(nums, pivotIndex + 1, high);
        }
    }

    // Sorting function using Quicksort
    void sortVector(std::vector<int>& nums) {
        quicksort(nums, 0, nums.size() - 1);
    }


    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // actual algorithm
        vector<int> all_val;
        vector<ListNode*> all_nodes = lists;
        for (int i = 0; i < all_nodes.size(); i++){
            while(all_nodes[i]!=nullptr){
                all_val.push_back(all_nodes[i]->val);
                all_nodes[i] = all_nodes[i]->next;
            }
        }

        sortVector(all_val);

        ListNode* root = nullptr;
        ListNode* head = nullptr;

        for(int i = 0; i < all_val.size(); i++){
            if(root==nullptr){
                ListNode* temp_node = new ListNode(all_val[i]);
                root = temp_node;
                head = temp_node;
            }else{
                ListNode* temp_node = new ListNode(all_val[i]);
                head->next = temp_node;
                head=head->next;
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