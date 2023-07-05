// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    bool isCycle(vector<vector<int>>& adj, vector<int>& visited, int& ver){
        if(visited[ver] == 1) return true;

        visited[ver] = 1;

        for(int i = 0; i < adj[ver].size(); i++){
            if(visited[adj[ver][i]]!=2){
                if(isCycle(adj, visited,  adj[ver][i])==true) return true;
            }
        }

        visited[ver] = 2;

        return false;
    }


    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // edge case
        if(prerequisites.size()==0 || numCourses == 0 || numCourses == 1) return true;

        vector<vector<int>> adj(numCourses);
        vector<int> visited(numCourses, 0);

        for(int i = 0; i < prerequisites.size(); i++){
            adj[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }

        for(int i = 0; i < numCourses; i++){
            if(visited[i]==0){
                if(isCycle(adj, visited, i)) return false;
            } 
        }

        return true;
    }
};

int main(){
    int numCourses = 5;

    vector<int> vec1 = {1,4};
    vector<int> vec2 = {2,4};
    vector<int> vec3 = {3,1};
    vector<int> vec4 = {3,2};
    vector<vector<int>> input;
    input.push_back(vec1); input.push_back(vec2);input.push_back(vec3);input.push_back(vec4);

    Solution a;
    cout << a.canFinish(numCourses, input) << endl;

    return 0;
}