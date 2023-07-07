class Trie {
public:
    Trie* child[26];
    bool isTerminal = false;

    Trie() {
        isTerminal = false;
        for(int i = 0; i < 26; i++) child[i]=NULL;
    }
    
    void insert(string word) {
        Trie* cur = this;
        for(int i = 0; i < word.size();i++){
            if(cur->child[word[i]-'a']==NULL) cur->child[word[i]-'a']=new Trie();
            cur = cur->child[word[i]-'a'];
        }
        cur->isTerminal = true;
    }
    
    bool search(string word) {
        Trie* cur = this;
        for(int i = 0; i < word.size();i++){
            if(cur->child[word[i]-'a']==NULL) return false;
            cur = cur->child[word[i]-'a'];
        }
        if(cur->isTerminal==true) return true;
        return false;
    }
    
    bool startsWith(string prefix) {
        Trie* cur = this;
        for(int i = 0; i < prefix.size();i++){
            if(cur->child[prefix[i]-'a']==NULL) return false;
            cur = cur->child[prefix[i]-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */