// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int helper(int ptr1, int ptr2, int ptr3, vector<vector<vector<int>>>& dp, string& s1, string& s2, string& s3){
        // termination conditions
        if(ptr1==s1.size() && ptr2==s2.size() && ptr3==s3.size()) return 1;
        if(ptr3==s3.size()) return 0;
        if(dp[ptr1][ptr2][ptr3]!=-1) return dp[ptr1][ptr2][ptr3];

        // procedural
        int l = 0; int r = 0;
        if(ptr1<s1.size() && s1[ptr1]==s3[ptr3]){
            l = helper(ptr1+1,ptr2,ptr3+1,dp,s1,s2,s3);
        }

        if(ptr2<s2.size() && s2[ptr2]==s3[ptr3]){
            r = helper(ptr1, ptr2+1, ptr3+1, dp, s1,s2,s3);
        }
        dp[ptr1][ptr2][ptr3] = l||r;
        return l||r;
    }

    bool isInterleave(string s1, string s2, string s3) {
        // edge cases
        if(s1.size()==0){
            if(s2==s3) return true;
            return false;
        }

        if(s2.size()==0){
            if(s1==s3) return true; 
            return false;
        }

        if(s3.size()==0){
            if(s1.size()!=0 || s2.size()!=0) return false;
            return true;
        }

        // main alg
        int s1_ptr = 0;
        int s2_ptr = 0;
        int s3_ptr = 0;

        int n1 = s1.size();
        int n2 = s2.size();
        int n3 = s3.size();
        vector<vector<vector<int>>> dp(n1+1, vector<vector<int>>(n2+1, vector<int>(n3+1, -1)));

        return helper(s1_ptr, s2_ptr, s3_ptr, dp, s1, s2, s3);
    }
};


int main(){
    string s1 = "aabcc";
    string s2 = "dbbca";
    string s3 = "aadbbbaccc";
    
    Solution a;
    cout << a.isInterleave(s1, s2, s3) << endl;
}