// Author: Sahil Yasar

#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

struct TrieNode{
    TrieNode* key[26];
    bool end = false;
    //int countWords = 0, countPrefix = 0;
};
struct Trie{
  TrieNode* root;
  int c;
  Trie(char c = 'a'): c(c) { root = new TrieNode(); }
  bool trav(string word, bool insert, bool prefix){
    TrieNode* temp = root;
    for (auto& x: word){
      if (!temp->key[x-c]){
        if (!insert) return false;
        temp->key[x-c] = new TrieNode();
      }
      temp = temp->key[x-c];
    }
    return (insert)? temp->end = true: (prefix)? true: temp->end;
  }
  bool insert(string word){ return trav(word, true, false); }
  bool search(string word, bool prefix = false)
  { return trav(word, false, prefix); }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    Trie t('a');
    t.insert("hello");
    t.insert("world");
    cout<<((t.search("hello"))?"YES":"NO")<<endl;
    cout<<((t.search("worl"))?"YES":"NO")<<endl;
    cout<<((t.search("worl", true))?"YES":"NO")<<endl;

    return 0;
}
