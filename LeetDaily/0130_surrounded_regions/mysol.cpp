// Author: Jason Zhou
// my own solution, correct but slow
#include "../general_include.h"
using namespace std;

class Solution {
public:
    pair<int,int> make_union(pair<pair<int,int>,pair<int,int>>& a, 
                    pair<pair<int,int>,pair<int,int>>& b,
                    int m,
                    int n){
        pair<int,int> old;
        if(a.second.first*m+a.second.second < b.second.first*m+b.second.second){
            old = b.second;
            b.second = a.second;
        }else{
            old = a.second;
            a.second = b.second;
        }
        return old;
    }


    void solve(vector<vector<char>>& board) {
        //edge case 
        if(board.size()==0 || board[0].size()==0) return;
        
        int m = board.size();
        int n = board[0].size();

        vector<pair<pair<int,int>,pair<int,int>>> st;   // {me, parent}

        // find all 'O'
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[i].size(); j++){
                if(board[i][j]=='O'){
                    st.push_back({{i,j}, {i,j}});
                }
            }
        }

        // make union
        for(int i = 0; i < st.size(); i++){
            for(int j = 0; j < st.size(); j++){
                bool v1 = (abs(st[i].first.first-st[j].first.first)==1) && (st[i].first.second == st[j].first.second);
                bool v2 = (abs(st[i].first.second-st[j].first.second)==1) && (st[i].first.first == st[j].first.first);
                if(v1||v2){
                    pair<int,int> old_par = make_union(st[i], st[j], m, n);
                    for(int k = 0; k < st.size(); k++){
                        if(st[k].second == old_par){
                            st[k].second = st[i].second;
                        }
                    }
                }
            }
        }

        // exclude edge
        unordered_set<int> repeat_itm;
        for(int i = 0; i < st.size();i++){
            if(st[i].first.first==0||st[i].first.first==m-1||st[i].first.second==0||st[i].first.second==n-1)
                repeat_itm.insert(st[i].second.first*m+st[i].second.second);
        }

        for(int i = 0; i < st.size(); i++){
            if(repeat_itm.count(st[i].second.first*m+st[i].second.second)!=0){
                st.erase(st.begin()+i);
                i--;
            }
        }

        for(auto& cur:st){
            board[cur.first.first][cur.first.second] = 'X';
        }
    }
};

int main(){
    vector<char> vec_1 = {'O','X','X','O','X'};
    vector<char> vec_2 = {'X','O','O','X','O'};
    vector<char> vec_3 = {'X','O','X','O','X'};
    vector<char> vec_4 = {'O','X','O','O','O'};
    vector<char> vec_5 = {'X','X','O','X','O'};

    vector<vector<char>> input;
    input.push_back(vec_1);
    input.push_back(vec_2);
    input.push_back(vec_3);
    input.push_back(vec_4);
    input.push_back(vec_5);

    Solution a;
    a.solve(input);

    for(auto& itm1:input){
        for(auto& itm2:itm1){
            cout << itm2 << ",";
        }
        cout << endl;
    }
}