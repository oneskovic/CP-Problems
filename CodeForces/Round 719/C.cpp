#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        int n; cin>>n;
        if(n == 1)
        {
            cout << "1\n";
        }
        else if(n == 2)
        {
            cout << "-1\n";
        }
        else if(n == 3)
        {
            cout << "2 9 7\n4 6 3\n1 8 5\n";
        }
        else
        {
            vector<vector<int>> matrix(n,vector<int>(n));
            int number = 1;
            for(int col = 0; col < n; col++)
            {
                for(int row = 0; row < n; row += 2)
                {
                    matrix[row][col] = number++;
                }
            }
            for(int col = 0; col < n; col++)
            {
                for(int row = 1; row < n; row += 2)
                {
                    matrix[row][col] = number++;
                }
            }

            for(auto row: matrix)
            {
                for(int v: row)
                {
                    cout << v << " ";
                }
                cout << "\n";
            }
        }

    }
    return 0;
}
