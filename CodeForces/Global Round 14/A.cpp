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
        int n, x; cin>>n >> x;
        vector<int> elements(n);
        for(int i = 0; i < n; i++)
            cin>>elements[i];
        sort(elements.begin(),elements.end());
        int prefix_sum = 0;
        bool possible = true;
        for(int i = 0; i < n; i++)
        {
            prefix_sum += elements[i];
            if(prefix_sum == x)
            {
                possible = false;
                if(i < n-1)
                {
                    swap(elements[i],elements[n-1]);
                    possible = true;
                }
                break;
            }
        }
        if(possible)
        {
            cout << "YES\n";
            for(int i: elements)
                cout << i << " ";
            cout << "\n";
        }
        else
            cout << "NO\n";

    }
    return 0;
}
