#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b,a%b);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        int x,y; cin>>x; y = 100;
        int g = gcd(x,y);
        x/=g;
        y/=g;
        cout << y << "\n";
    }
    return 0;
}
