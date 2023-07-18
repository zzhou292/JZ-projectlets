// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    int checkdis(string& str1, string& str2){
        int res = 0;
        for(int i = 0; i < str1.size(); i++){
            if(str1[i]!=str2[i]) res++;
        }
        return res;
    }

    int minMutation(string startGene, string endGene, vector<string>& bank) {
        vector<string> visited;
        queue<pair<string,int>> qe;
        qe.push({startGene,0});

        int min_dis = INT_MAX;

        while(!qe.empty()){
            string cur = qe.front().first;
            int lv = qe.front().second;
            qe.pop();

            if(cur==endGene){
                min_dis = min(lv,min_dis);
            }

            for(int i = 0; i < bank.size(); i++){
                if(find(visited.begin(), visited.end(),bank[i])==visited.end() && bank[i]!=cur && bank[i]!=startGene){
                    if(checkdis(bank[i], cur)==1) qe.push({bank[i],lv+1});
                }
            }

            visited.push_back(cur);
        }

        if(min_dis==INT_MAX) return -1;
        return min_dis;
    }
};


int main(){
    vector<string> st = {"AACCGGTA","AACCGCTA","AAACGGTA"};

    Solution a;
    cout << a.minMutation("AACCGGTT", "AAACGGTA", st) << endl;
}