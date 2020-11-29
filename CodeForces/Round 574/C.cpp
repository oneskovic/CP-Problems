#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
 
int main()
{
 
    int n; cin>>n;
    vector<ll> a(n),b(n);
    for (size_t i = 0; i < n; i++)
        cin>>a[i];
    for (size_t i = 0; i < n; i++)
        cin>>b[i];
 
    vector<ll> dp_a(n), dp_b(n);
    dp_a[n-1] = a[n-1];
    dp_b[n-1] = b[n-1];
    for(int i = n-2; i >= 0; i--)
    {
        dp_a[i] = max(dp_a[i+1],a[i]+dp_b[i+1]);
        dp_b[i] = max(dp_b[i+1],b[i]+dp_a[i+1]);
    }
    cout << max(dp_a[0],dp_b[0]);
    return 0;
}