// Author: Sahil Yasar
// Tested on:
// https://codeforces.com/problemset/problem/1851/F

#include <iostream>
using namespace std;
#define endl '\n'

const int BIT = 30;
struct TrieNode{
    TrieNode* key[2];
    int index = -1;
};
struct Trie{
	TrieNode* root;
	Trie() { root = new TrieNode(); }
	void destroy(TrieNode* n){
		if (!n) return;
		destroy(n->key[0]);
		destroy(n->key[1]);
		delete n;
	}
	~Trie(){ destroy(root); }
	bool insert(int n, int i){
        bool ret = false;
		TrieNode* temp = root;
		for (int b = BIT; b >= 0; --b){
            bool id = (n>>b)&1;
			if (!temp->key[id])
				ret = 1, temp->key[id] = new TrieNode();
			temp = temp->key[id];
		}
		temp->index = i;
        return ret;
	}
    int maXOR(int n){
        TrieNode* temp = root;
		for (int b = BIT; b >= 0; --b){
            bool id = (n>>b)&1;
			if (temp->key[!id])
				temp = temp->key[!id];
            else if (temp->key[id])
			    temp = temp->key[id];
            else
                return -1;
		}
		return temp->index;
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t, n, k, i, j, l, x, temp, ind;
    cin>>t;
    while(t--){
        cin>>n>>k;
        int a[n];
        for (i = 0; i < n; ++i)
			cin>>a[i];
        i = j = x = -1;
        Trie bit;
        for (l = 0; l < n; ++l){
            temp = ((1<<k)-1)^a[l];
			ind = bit.maXOR(temp);
			bit.insert(a[l], l);
			if (ind == -1) continue;
			if ((temp^a[ind]) > x)
				i = ind, j = l, x = temp^a[ind];
        }
		x = (((1<<k)-1)^a[i]) & (((1<<k)-1)^a[j]);
        cout<<i+1<<" "<<j+1<<" "<<x<<endl;
    }

    return 0;
}
