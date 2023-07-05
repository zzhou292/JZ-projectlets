// Author: Jason Zhou
// accepted solution, not the best, but the concept is right
#include "../general_include.h"
using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        //edge case
        if(board.size()==0 || board[0].size()==0 || board[0].size()==1) return;
        
        int m = board.size();
        int n = board[0].size();
        vector<vector<char>> ans(m, vector<char>(n, 'X'));
        stack<pair<int,int>> st;
        vector<pair<int,int>> visited;

        //assign proper 'O' to edges
        for (int i = 0; i < m; i++){
            if(board[i][0]=='O'){
                ans[i][0]='O';
                st.push({i,0});
                visited.push_back({i,0});
            }

            if(board[i][n-1]=='O'){
                ans[i][n-1]='O';
                st.push({i,n-1});
                visited.push_back({i,n-1});
            }
        }

        for (int i = 0; i < n; i++){
            if(board[0][i]=='O'){
                ans[0][i]='O';
                st.push({0,i});
                visited.push_back({0,i});
            }

            if(board[m-1][i]=='O'){
                ans[m-1][i]='O';
                st.push({m-1,i});
                visited.push_back({m-1,i});
            }
        }

        while(!st.empty()){
            int cur_i = st.top().first;
            int cur_j = st.top().second;
            st.pop();

            vector<int> d_row = {0, 0, -1, 1};
            vector<int> d_col = {-1, 1, 0, 0};

            for(int i = 0; i < 4; i++){
                int t_i = cur_i+d_row[i];
                int t_j = cur_j+d_col[i];
                if(t_i >= 0 && t_i < m && t_j >= 0 && t_j < n){
                    if(board[t_i][t_j]=='O'){
                        pair<int,int> target = {t_i, t_j};
                        if(find(visited.begin(),visited.end(),target)==visited.end()){
                            ans[t_i][t_j] = 'O';
                            visited.push_back({t_i,t_j});
                            st.push({t_i,t_j});
                        }
                    }

                }
            }
        }

        board = ans;
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