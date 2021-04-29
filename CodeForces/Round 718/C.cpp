#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void print_board(const vector<vector<int>>& b)
{
    int n = b.size();
    for(int row = 0; row < n; row++)
    {
        for(int col = 0; col <= row; col++)
        {
            cout << b[row][col] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    int n; cin>>n;
    vector<vector<int>> board(n,vector<int>(n));
    vector<int> remaining; remaining.reserve(n-1);
    vector<int> cnt(n-1,1);
    for(int row = 0; row < n; row++)
    {
        int el; cin>>el;
        board[row][row] = el;
        if(el != 1)
        {
            remaining.push_back(el);
        }
    }
    bool possible = 1;
    for(int row = 1; row < n; row++)
    {
        vector<int> new_rem, new_cnt;
        int temp_row = row;
        if(remaining.size() > n - row)
        {
            possible = 0;
            break;
        }
        for(int i = 0; i < n - row; i++)
        {
            board[temp_row++][i] = remaining[i];
            if(cnt[i]+1 < remaining[i])
            {
                new_rem.push_back(remaining[i]);
                new_cnt.push_back(cnt[i]+1);
            }
        }
        remaining = new_rem;
        cnt = new_cnt;
    }
    if(!possible)
        cout << "-1" << endl;

    else
        print_board(board);

    return 0;
}
