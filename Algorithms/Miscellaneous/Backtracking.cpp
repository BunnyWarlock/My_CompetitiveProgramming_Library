// Author: Sahil Yasar
// Tested here:
// https://leetcode.com/problems/n-queens/

const int MAX = 20;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));
        bitset<MAX> col, d1, d2;

        auto search = [&](int r, auto&& search){
            if (r == n){
                ans.push_back(board);
                return;
            }
            for (int c = 0; c < n; ++c){
                if (col[c] || d1[r+c] || d2[r-c+n])
                    continue;
                col[c] = d1[r+c] = d2[r-c+n] = true;
                board[r][c] = 'Q';
                search(r+1, search);
                col[c] = d1[r+c] = d2[r-c+n] = false;
                board[r][c] = '.';
            }
        };

        search(0, search);
        return ans;
    }
};
