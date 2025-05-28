// Author: Sahil Yasar
// Tested here:
// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/a-chessboard-game

#include <iostream>
#include <cstring>
#include <bitset>
using namespace std;
#define endl '\n'

const int MAX = 300;
int dx[] = {-2, -2, 1, -1};
int dy[] = {1, -1, -2, -2};
int memo[15][15];
int grundy(int x, int y){
    if (x < 0 || x >= 15) return -1;
    if (y < 0 || y >= 15) return -1;
    if (memo[x][y] != -1) return memo[x][y];
    bitset<MAX> b;
    for (int i = 0; i < 4; ++i){
        int temp = grundy(x+dx[i], y+dy[i]);
        if (temp != -1) b[temp] = true;
    }
    int mex = 0;
    while(b[mex]) ++mex;
    return memo[x][y] = mex;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t, k, x, y, i, ans;
    memset(memo, -1, sizeof(memo));
    cin>>t;
    while(t--){
        cin>>k;
        ans = 0;
        for (i = 0; i < k; ++i){
            cin>>x>>y;
            ans ^= grundy(--x, --y);
        }
        cout<<((ans)? "First": "Second")<<endl;
    }

    return 0;
}
