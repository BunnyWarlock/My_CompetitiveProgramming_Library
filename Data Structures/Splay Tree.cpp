// Author: Sahil Yasar
// Add or remove functionalities from the node struct depending on the problem to save memory

#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace splayTree{
    template <class T>
    struct node{
        T value;
        T valMin;
        T valMax;
        T labelAdd;
        pair<bool, T> labelSet;
        T sum;
        node* parent;
        node* child[2];
        int size;
        bool rev;

        node(const T& val = T()){
            size = 1;
            rev = false;
            parent = child[0] = child[1] = nullptr;
            value = sum = val;
            labelSet.second = valMax = valMin = labelAdd = T();
            labelSet.first = false;
        }
        void update(){
            size = 1;
            valMax = valMin = sum = value;
            for (int i = 0; i < 2; ++i)
                if (child[i]){
                    size += child[i]->size;
                    valMin = min(valMin, child[i]->valMin);
                    sum += child[i]->sum;
                    valMax = max(valMax, child[i]->valMax);
                }
        }
        bool side() const {
            return parent->child[1] == this;
        }
        void reverse() {
            swap(child[0], child[1]);
            rev = !rev;
        }
        void add(const T& val){
            value += val;
            valMin += val;
            valMax += val;
            labelAdd += val;
            sum += size*val;
        }
        void set(const T& val){
            value = val;
            valMin = val;
            valMax = val;
            labelAdd = T();
            labelSet = make_pair(true, val);
            sum = size*val;
        }
        void push_down(){
            if (rev) {
                for (int i = 0; i < 2; ++i)
                    if (child[i]) child[i]->reverse();
                rev = false;
            }
            for (int i = 0; i < 2; ++i)
                if (child[i]){
                    if (labelSet.first) child[i]->set(labelSet.second);
                    child[i]->add(labelAdd);
                }
            labelAdd = T();
            labelSet.first = false;
        }
    };

    template <class T>
    struct SPtree{
        node<T>* root;
        node<T>* dummy[2];

        node<T>* newNode(const T& val = T()){
            node<T>* n = new node<T>(val);
            return n;
        }
        SPtree(){
            dummy[0] = root = newNode();
            dummy[1] = root->child[1] = newNode();
            root->size = 2;
            root->child[1]->parent = root;
        }
        ~SPtree(){
            destroy(root);
        }
        // Checks if the node is the root
        bool isRoot(node<T>* v) {
            if (v == NULL) return false;
            return (v->parent == NULL || (v->parent->child[0] != v && v->parent->child[1] != v));
        }
        // Get the size of the tree.
        int size(){
            return root->size - 2;
        }
        // Helper function to walk down the tree.
        int walk(node<T>* n, int& v, int& pos){
            n->push_down();
            int s = (n->child[0])?n->child[0]->size:0;
            v = (s < pos);
            if (v) pos -= s+1;
            return s;
        }
        // Find the node at position pos. If sp is true, splay it.
        node<T>* find(int pos, int sp = true){
            node<T>* c = root;
            int v;
            ++pos;
            while ((pos < walk(c, v, pos) || v) && (c = c->child[v]));
            if (sp) splay(c);
            return c;
        }
        // Insert node n to position pos.
        void insert(node<T>* n, int pos = -1){
            if (pos == -1)
                pos = size();
            node<T>* c = root;
            int v;
            ++pos;
            for (walk(c, v, pos); c->child[v];){
                c = c->child[v];
                walk(c, v, pos);
            }
            c->child[v] = n;
            n->parent = c;
            splay(n);
        }
        void insert(const T& val, int pos = -1){
            insert(newNode(val), pos);
        }
        // Helper function to rotate node.
        void rotate(node<T>* n) {
            int v = !(n->side());
            node<T>* p = n->parent;
            node<T>* m = n->child[v];
            n->push_down();
            p->push_down();
            if (p->parent)
                p->parent->child[p->side()] = n;
            n->parent = p->parent;
            n->child[v] = p;
            p->parent = n;
            p->child[v ^ 1] = m;
            if (m) m->parent = p;
            p->update();
            n->update();
        }
        // Splay n so that it is under s (or to root if s is null).
        void splay(node<T>* n, node<T>* s = nullptr) {
            while (n->parent != s) {
                node<T>* m = n->parent;
                node<T>* l = m->parent;
                if (l == s)
                    rotate(n);
                else if (m->side() == n->side()){
                    rotate(m);
                    rotate(n);
                }
                else{
                    rotate(n);
                    rotate(n);
                }
            }
            if (!s) root = n;
        }
        // Return vector containing the In-order traversal of the tree.
        void inorder(vector<T>& v, bool mode = true, node<T>* r = nullptr){
            if (mode) r = root;
            if (!r) return;
            r->push_down();
            inorder(v, false, r->child[0]);
            if (r != dummy[0] && r != dummy[1])
                v.push_back(r->value);
            inorder(v, false, r->child[1]);
        }
        // Find the range [posl, posr] on the splay tree.
        node<T>* find_range(int posl, int posr){
            node<T>* r = find(posr + 1);
            node<T>* l = find(posl - 1, false);
            splay(l, r);
            if (l->child[1]) l->child[1]->push_down();
            return l->child[1];
        }
        // helper function for deleting
        void destroy(node<T>* n){
            if (!n) return;
            destroy(n->child[0]);
            destroy(n->child[1]);
            delete n;
        }
        // Remove from position [posl, posr] or splits [posl, posr] if split is true
        node<T>* erase_range(int posl, int posr, bool split = false) {
            node<T>* n = find_range(posl, posr);
            n->parent->child[1] = nullptr;
            n->parent->update();
            n->parent->parent->update();
            n->parent = nullptr;
            if (split)
                return n;
            destroy(n);
            return nullptr;
        }
        // Remove position pos
        void erase(int pos){
            erase_range(pos, pos);
        }
    };
}
using namespace splayTree;

/*
To reverse a segment [l, r] use
    spt.find_range(l, r)->reverse();
To set a value to every element in a range
    spt.find_range(l, r)->set(500);
To add a value to all elements in a range
    spt.find_range(l, r)->add(2);
To get sum, valMin, valMax of a segment [l, r]
    spt.find_range(l, r)->valMin;
To split up a range [l, r] use
    node<T>* temp = spt.erase_range(y-a, y-1, true);
*/

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Random code
    // You can ignore
    // Basically a small peek as to how to use it
    // Good Luck!

    SPtree<int> spt;
    cout<<spt.size()<<" *** "<<endl;
    for (int i = 0; i < 10; ++i){
        spt.insert(i);
    }
    cout<<spt.size()<<" *** "<<endl;

    for (int i = 0; i < spt.size(); ++i)
        cout<<(spt.find(i))->value<<endl;

    //spt.erase_range(0, spt.size()-1);
    //spt.insert(100, 7);
    //spt.erase(7);
    //spt.reverse_range(0, 9);
    spt.find_range(3, 7)->set(5);
    spt.find_range(3, 7)->add(2);
    spt.find_range(4, 6)->set(500);
    vector<int> p;
    spt.inorder(p);
    for (int i = 0; i < p.size(); ++i)
        cout<<p[i]<<" ";
    cout<<endl;
    cout<<" ++ "<<(spt.find_range(3, 7))->sum<<endl;



    int n, i, m, x, y, a;
    string s;
    cin>>n;
    SPtree<int> spt1;
    for (i = 0; i < n; ++i){
        cin>>a;
        spt1.insert(a);
    }
    cin>>m;
    while(m--){
        cin>>s;
        if (s == "ADD"){
            cin>>x>>y>>a;
            spt1.find_range(x-1, y-1)->add(a);
        }
        else if (s == "REVERSE"){
            cin>>x>>y;
            spt1.find_range(x-1, y-1)->reverse();
        }
        else if (s == "REVOLVE"){
            cin>>x>>y>>a;
            a %= y - x + 1;
            if (a > 0){
                node<int>* temp = spt1.erase_range(y-a, y-1, true);
                spt1.insert(temp, x-1);
            }
        }
        else if (s == "INSERT"){
            cin>>x>>a;
            spt1.insert(a, x);
        }
        else if (s == "DELETE"){
            cin>>x;
            spt1.erase(x-1);
        }
        else{
            cin>>x>>y;
            cout<<spt1.find_range(x-1, y-1)->valMin<<endl;
        }
    }

    return 0;
}
