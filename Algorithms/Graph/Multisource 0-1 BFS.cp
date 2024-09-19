// Author: Sahil Yasar
// Tested here:
// https://www.codechef.com/problems/PRISON

#include <iostream>
#include <vector>
#include <cstring>
#include <deque>
using namespace std;
#define endl '\n'

const int MAX = 3e5 + 10;
vector<vector<bool>> grid;
vector<vector<int>> d;
int n, m;
pair<int, int> adj[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void multiBFS(){
    d.assign(n+2, vector<int>(m+2, 0x7FFF));
    deque<pair<int, int>> q;
    // Multiple sources init
    for (int i = 1; i <= n; ++i){
        q.push_front({i, 0});
        q.push_front({i, m+1});
        d[i][0] = d[i][m+1] = 0;
    }
    for (int i = 1; i <= m; ++i){
        q.push_front({0, i});
        q.push_front({n+1, i});
        d[0][i] = d[n+1][i] = 0;
    }
    while(!q.empty()){
        auto [x, y] = q.front();
        q.pop_front();
        for (auto [dx, dy]: adj){
            int x2 = x+dx, y2 = y+dy;
            if (x2 <= 0 || x2 > n || y2 <= 0 || y2 > m)
                continue;
            if (d[x][y] + grid[x2][y2] < d[x2][y2]){
                d[x2][y2] = d[x][y] + grid[x2][y2];
                if (grid[x2][y2])
                    q.push_back({x2, y2});
                else
                    q.push_front({x2, y2});
            }
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t, i, j, ans;
    string temp;
    cin>>t;
    while(t--){
        cin>>n>>m;
        grid.assign(n+2, vector<bool>(m+2));
        for (i = 1; i <= n; ++i){
            cin>>temp;
            for (j = 0; j < m; ++j)
                grid[i][j+1] = (temp[j] == '1');
        }
        multiBFS();
        ans = 0;
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= m; ++j)
                ans = max(ans, (!grid[i][j])*d[i][j]);
        cout<<ans<<endl;
    }

    return 0;
}
