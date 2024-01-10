#include <iostream>
#include <math.h>
using namespace std;
#define endl '\n'

// const long long LLONG_MAX = 2000000000000000007;

namespace KDTree{
    template <int k>
    struct node{
        int point[k];
        node* left;
        node* right;

        node(int arr[k]){
            left = right = nullptr;
            for (int i = 0; i < k; ++i)
                point[i] = arr[i];
        }
        void updatePoint(int arr[k]){
            for (int i = 0; i < k; ++i)
                point[i] = arr[i];
        }
        void print(){
            cout<<"(";
            for (int i = 0; i < k; ++i)
                cout<<point[i]<<", ";
            cout<<"\b\b)"<<endl;
        }
    };

    template <int k>
    struct KDtree{
        node<k>* root;

        node<k>* newNode(int arr[k]){
            node<k>* n = new node<k>(arr);
            return n;
        }
        KDtree(){
            root = nullptr;
        }
        // Helper function for deleting.
        void destroy(node<k>* n){
            if (!n) return;
            destroy(n->left);
            destroy(n->right);
            delete n;
        }
        ~KDtree(){
            destroy(root);
        }
        // Insert a new point to the tree.
        node<k>* insert(int arr[k], node<k>* n, unsigned depth = 0){
            if (!n) return newNode(arr);
            unsigned cd = depth%k;
            if (arr[cd] < n->point[cd])
                n->left = insert(arr, n->left, depth+1);
            else
                n->right = insert(arr, n->right, depth+1);
            return n;
        }
        void insert(int arr[k]){
            node<k>* n = insert(arr, root, 0);
            if (!root) root = n;
        }
        // Helper function checks if two points are the same or not.
        bool checkPoints(int p1[k], int p2[k]){
            for (int i = 0; i < k; ++i)
                if (p1[i] != p2[i])
                    return false;
            return true;
        }
        // Checks if a point exists in the tree or not.
        bool search(int arr[k], node<k>* n, unsigned depth = 0){
            if (!n) return false;
            if (checkPoints(n->point, arr)) return true;
            unsigned cd = depth%k;
            if (arr[cd] < n->point[cd])
                return search(arr, n->left, depth+1);
            return search(arr, n->right, depth+1);
        }
        bool search(int arr[k]){
            return search(arr, root, 0);
        }
        // Find the point with the smallest value in the ith dimension
        node<k>* findMin(int i, node<k>* n, unsigned depth = 0){
            if (!n) return nullptr;
            unsigned cd = depth%k;
            if (cd == k){
                if (!(n->left))
                    return n;
                return findMin(i, n->left, depth+1);
            }
            node<k>* a[3] = {n, findMin(i, n->left, depth+1), findMin(i, n->right, depth+1)};
            for (int j = 1; j < 3; ++j)
                if (a[j] && a[0]->point[i] > a[j]->point[i])
                    swap(a[0], a[j]);
            return a[0];
        }
        node<k>* findMin(int i){
            return findMin(i, root, 0);
        }
        // Find the point with the largest value in the ith dimension
        node<k>* findMax(int i, node<k>* n, unsigned depth = 0){
            if (!n) return nullptr;
            unsigned cd = depth%k;
            if (cd == k){
                if (!(n->right))
                    return n;
                return findMin(i, n->right, depth+1);
            }
            node<k>* a[3] = {n, findMax(i, n->left, depth+1), findMax(i, n->right, depth+1)};
            for (int j = 1; j < 3; ++j)
                if (a[j] && a[0]->point[i] < a[j]->point[i])
                    swap(a[0], a[j]);
            return a[0];
        }
        node<k>* findMax(int i){
            return findMax(i, root, 0);
        }
        // Delete a point from the tree
        node<k>* remove(int arr[], node<k>* n, int depth = 0){
            if (!n) return nullptr;
            unsigned cd = depth%k;
            if (checkPoints(arr, n->point)){
                if (n->right){
                    node<k>* min = findMin(cd, n->right);
                    n->updatePoint(min->point);
                    n->right = remove(min->point, n->right, depth+1);
                }
                else if (n->left){
                    node<k>* min = findMin(cd, n->left);
                    n->updatePoint(min->point);
                    n->right = remove(min->point, n->left, depth+1);
                }
                else{
                    delete n;
                    return nullptr;
                }
                return n;
            }
            if (arr[cd] < n->point[cd])
                n->left = remove(arr, n->left, depth+1);
            else
                n->right = remove(arr, n->right, depth+1);
            return n;
        }
        void remove(int arr[]){
            remove(arr, root, 0);
        }
        // Helper function to get distance between two points.
        long long sqrDist(int p1[k], int p2[k]){
            long long dist = 0;
            for (int i = 0; i < k; ++i)
                dist += (p1[i] - p2[i]) * 1LL * (p1[i] - p2[i]);
            return dist;
        }
        // Returns the nearest neighbor to the input point
        void nearest(int arr[], node<k>* n, node<k>*& minNode, long long& minDist = LLONG_MAX, int depth = 0){
            if (!n) return;
            long long dist = sqrDist(n->point, arr);
            if (!dist) dist = LLONG_MAX; // This line may or may not be included
            if (minDist > dist){
                minDist = dist;
                minNode = n;
            }
            unsigned cd = depth%k;
            if (arr[cd] < n->point[cd]){
                nearest(arr, n->left, minNode, minDist, depth+1);
                if ((arr[cd] - n->point[cd]) * 1LL * (arr[cd] - n->point[cd]) <= minDist)
                    nearest(arr, n->right, minNode, minDist, depth+1);
            }
            else{
                nearest(arr, n->right, minNode, minDist, depth+1);
                if ((arr[cd] - n->point[cd]) * 1LL * (arr[cd] - n->point[cd]) <= minDist)
                    nearest(arr, n->left, minNode, minDist, depth+1);
            }
        }
        node<k>* nearest(int arr[], long long& sqrdist){
            node<k>* n = nullptr;
            sqrdist = LLONG_MAX;
            nearest(arr, root, n, sqrdist, 0);
            return n;
        }
    };
}
using namespace KDTree;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.exceptions(cin.failbit);

    // KDtree<2> kdt;
    // int points[][2] = {{-3, -6}, {17, 15}, {13, 15}, {6, 12},
    //                     {9, 1}, {-2, -5}, {10, 19}};
    // int n = sizeof(points)/sizeof(points[0]);
    // for (int i=0; i<n; i++)
    //     kdt.insert(points[i]);
    // 
    // int point1[] = {10, 19};
    // int point2[] = {12, 19};
    // kdt.remove(point1);
    // kdt.insert(point2);
    // cout<<((kdt.search(point1))?"FOUND":"NOT FOUND")<<endl;
    // cout<<((kdt.search(point2))?"FOUND":"NOT FOUND")<<endl;
    // kdt.findMin(0)->print();
    // kdt.findMax(1)->print();
    // 
    // cout<<endl;
    // int point3[] = {9, 9};
    // long long sqrdist;
    // kdt.nearest(point3, sqrdist)->print();
    // cout<<sqrdist<<endl;

    long long t, n, i, temp;
    cin>>t;
    while(t--){
      cin>>n;
      int p[n][2];
      KDtree<2> kdt;
      for (i = 0; i < n; ++i){
        cin>>p[i][0]>>p[i][1];
        kdt.insert(p[i]);
      }

      for (i = 0; i < n; ++i){
        kdt.nearest(p[i], temp);
        cout<<temp<<endl;
      }
    }

    return 0;
}
