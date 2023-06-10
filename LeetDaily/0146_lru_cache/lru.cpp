// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class LRUCache {
public:
    std::map<int, pair<list<int>::iterator, int>> m_data;
    list<int> m_key_list;
    int m_capacity = 0;

    LRUCache(int capacity) {
        m_capacity = capacity;
    }
    
    int get(int key) {
        if(m_data.find(key)!=m_data.end()){
            m_key_list.erase(m_data[key].first);
            m_key_list.push_front(key);
            m_data[key].first = m_key_list.begin();

            return m_data[key].second;
        }else{
            return -1;
        }


    }
    
    void put(int key, int value) {
        // if I can find the element
        if(m_data.find(key)!=m_data.end())
        {
            m_data[key].second=value;
            
            m_key_list.erase(m_data[key].first);
            m_key_list.push_front(key);
            m_data[key].first = m_key_list.begin();
        }else{
            // if I cannot find the element
            m_key_list.push_front(key);
            m_data[key] = {m_key_list.begin(), value};
        }

        if(m_data.size() > m_capacity){
            int key_to_remove = m_key_list.back();
            m_key_list.pop_back();
            
            m_data.erase(key_to_remove);
        }

    }

    
};


int main(){
    LRUCache* lRUCache = new LRUCache(2);
    lRUCache->put(1, 1); // cache is {1=1}
    lRUCache->put(2, 2); // cache is {1=1, 2=2}
    lRUCache->get(1);    // return 1
    lRUCache->put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    lRUCache->get(2);    // returns -1 (not found)
    lRUCache->put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    lRUCache->get(1);    // return -1 (not found)
    lRUCache->get(3);    // return 3
    lRUCache->get(4);    // return 4
    return 0;
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */