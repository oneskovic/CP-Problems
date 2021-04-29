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
        ll n; cin>>n;
        if(n % 2050 > 0)
        {
            cout << "-1\n";
        }
        else
        {
            n /= 2050;
            ll solution = 0;
            while(n > 0)
            {
                ll digit = n % 10;
                solution += digit;
                n/=10;
            }
            cout << solution << "\n";
        }
    }
    return 0;
}
