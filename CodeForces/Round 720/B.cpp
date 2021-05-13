#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b)
{
    if(b == 0)
        return a;
    return gcd(b, a%b);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        int n; cin>>n;
        vector<ll> elements(n);
        for(int i = 0; i < n; i++)
        {
            cin>>elements[i];
        }
        int min_pos = min_element(elements.begin(),elements.end()) - elements.begin();
        ll swap_number = elements[min_pos]+1;
        cout << n-1 << "\n";
        for(int i = min_pos-1; i >= 0; i--)
        {
            cout << i+1 << " " << min_pos+1 << " " << swap_number << " " << elements[min_pos] << "\n";
            swap_number++;
        }
        swap_number = elements[min_pos]+1;
        for(int i = min_pos+1; i < n; i++)
        {
            cout << i+1 << " " << min_pos+1 << " " << swap_number << " " << elements[min_pos] << "\n";
            swap_number++;
        }
    }
    return 0;
}
