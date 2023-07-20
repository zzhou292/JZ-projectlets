class RandomizedSet {
public:
    unordered_map<int,int> myMap;
    vector<int> myIdxSt;
    RandomizedSet() {
        // Create an unordered_set of integers
        
    }
    
    bool insert(int val) {
        if(myMap.count(val)!=0) return false;

        myMap[val] = myIdxSt.size();
        myIdxSt.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if(myMap.count(val)!=0){
            int idx_to_remove = myMap[val];
            myIdxSt[idx_to_remove] = myIdxSt[myIdxSt.size()-1];
            myIdxSt.pop_back();
            myMap[myIdxSt[idx_to_remove]]=idx_to_remove;
            myMap.erase(val);
            return true;
        }else{
            return false;
        }
    }
    
    int getRandom() {
        int idx = rand()%myIdxSt.size();

        return myIdxSt[idx];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */