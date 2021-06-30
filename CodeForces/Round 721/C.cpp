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
        map<int,vector<int>> element_positions;
        for(int i = 0; i < n; i++)
        {
            int element; cin>>element;
            element_positions[element].push_back(i+1);
        }
        ll res = 0;
        for(auto kvp: element_positions)
        {
            if(kvp.second.size() >= 2)
            {
                vector<int>& positions = kvp.second;
                vector<ll> prefix_sums(positions.size());
                prefix_sums[0] = positions[0];
                for(int i = 1; i < positions.size(); i++)
                {
                    prefix_sums[i] = prefix_sums[i-1] + positions[i];
                }
                for(int i = positions.size() - 1; i > 0; i--)
                {
                    res += (n - (positions[i] - 1)) * prefix_sums[i-1];
                }
            }
        }
        cout << res << "\n";
    }

    return 0;
}
