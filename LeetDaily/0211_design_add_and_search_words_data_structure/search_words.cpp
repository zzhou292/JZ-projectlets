// helper class
class node{
    public:
    bool isTerminal = false;
    node* child[26];

    node(){
        isTerminal = false;
        for(int i = 0; i < 26; i++) child[i]=nullptr;
    }
};

class WordDictionary {
public:
    node* root;

    WordDictionary() {
        root = new node();
    }
    
    void addWord(string word) {
        node* cur = root;
        for(int i = 0; i < word.size(); i++){
            if(cur->child[word[i]-'a']==nullptr) cur->child[word[i]-'a']=new node();
            cur = cur->child[word[i]-'a'];
        }
        cur->isTerminal = true;
    }

    bool search_helper(node* cur, string sub_word){
        for(int i = 0; i < sub_word.size();i++){
            if(sub_word[i]=='.'){
                vector<node*> candidates;
                for(int j = 0; j < 26; j++){
                    
                    if ((cur->child[j])!=nullptr){
                        candidates.push_back(cur->child[j]);
                    }
                }

                for(int j = 0; j < candidates.size();j++)
                {
                    
                    if(sub_word.size()-i>1){
                        if(search_helper(candidates[j],sub_word.substr(i+1,sub_word.size()-1))) return true;
                    }else{
                        if(candidates[j]->isTerminal) return true;
                    }
                }

                return false;
            }else{
                if(cur->child[sub_word[i]-'a']==nullptr) return false;
                cur = cur->child[sub_word[i]-'a'];
            }
        }
                
        if(cur->isTerminal==true) return true;
        return false;
    }
    
    bool search(string word) {
        node* cur = root;
        return search_helper(cur, word);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */