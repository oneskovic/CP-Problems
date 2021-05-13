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
        ll n; cin>>n;
        int sol = 0;
        for(int digit = 1; digit <= 9; digit++)
        {
            ll number = digit;
            while(number <= n)
            {
                sol++;
                number *= 10;
                number += digit;
            }
        }
        cout << sol << "\n";
    }
    return 0;
}
