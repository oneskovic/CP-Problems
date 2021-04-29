#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    for(int test_no = 0; test_no < test_cnt; test_no++)
    {
        ll n,m,x; cin>>n>>m>>x;
        ll row = (x-1) % n;
        ll col = (x-1) / n;

        ll solution = 1 + row * m + col;
        cout << solution << "\n";
    }

    return 0;
}
