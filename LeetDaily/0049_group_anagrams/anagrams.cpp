// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> umap;
        for(auto& str:strs){
            string s = str;
            sort(s.begin(), s.end());
            umap[s].push_back(str);
        }

        vector<vector<string>> res;
        for(auto& pair:umap){
            res.push_back(pair.second);
        }

        return res;

    }
};

int main(){
    vector<string> input = {"eat","tea","tan","ate","nat","bat"};

    Solution a;
    auto output = a.groupAnagrams(input);

    for(auto& i:output){
        cout << "[";
        for(auto& str:i){
            cout << str << " ";
        }
        cout << "]";
    }

    return 0;
}