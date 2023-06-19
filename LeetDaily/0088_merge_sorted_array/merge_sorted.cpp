// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // edge case
        if(n==0) return;

        int ptr1 = m-1; int ptr2 = n-1; int merge_ptr = m+n-1;
        while(ptr1 >=0 && ptr2 >= 0 && merge_ptr >= 0){
            if(nums1[ptr1] > nums2[ptr2]){
                nums1[merge_ptr] = nums1[ptr1];
                ptr1--;
                merge_ptr--;
            }else{
                nums1[merge_ptr] = nums2[ptr2];
                ptr2--;
                merge_ptr--;
            }
        }

        // add in remain
        while(ptr1 >= 0){
            nums1[merge_ptr] = nums1[ptr1];
            ptr1--;
            merge_ptr--;
        }

        while(ptr2 >= 0){
            nums1[merge_ptr] = nums2[ptr2];
            ptr2--;
            merge_ptr--;
        }
    }
};

int main(){
    vector<int> nums1 = {1,2,3,0,0,0};
    vector<int> nums2 = {2,5,6};

    Solution a;
    a.merge(nums1, 3, nums2, 3);

    for(int i = 0; i < nums1.size(); i++){
        cout << nums1[i] << " ";
    }

    return 0;
}