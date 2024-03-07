// Author: Sahil Yasar

#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

struct TrieNode{
    TrieNode* key[26];
    bool end = false;
    int countWords = 0, countPrefix = 0;
};
struct Trie{
	TrieNode* root;
	int c;
	Trie(char c = 'a'): c(c) { root = new TrieNode(); }
	void destroy(TrieNode* n){
		if (!n) return;
		for (int i = 0; i < 10; ++i)
		    destroy(n->key[i]);
		delete n;
	}
	~Trie(){ destroy(root); }
	bool insert(string word){
		TrieNode* temp = root;
		for (auto& x: word){
			if (!temp->key[x-c])
				temp->key[x-c] = new TrieNode();
			temp = temp->key[x-c];
			++temp->countPrefix;
		}
		++temp->countWords;
		return temp->end = true;
	}
	bool search(string word, bool prefix = false){
		TrieNode* temp = root;
		for (auto& x: word){
			if (!temp->key[x-c])
				return false;
			temp = temp->key[x-c];
		}
		return (prefix)? true: temp->end;
	}
	int count(string word, bool prefix = true){
		TrieNode* temp = root;
		int cnt = 0;
		for (auto& x: word){
			if (!temp->key[x-c])
				return false;
			temp = temp->key[x-c];
			cnt += (prefix)?temp->countPrefix :temp->countWords;
		}
		return cnt;
	}
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
