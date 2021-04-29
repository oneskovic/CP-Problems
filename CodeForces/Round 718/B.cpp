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
        int n,m; cin>>n>>m;
        vector<deque<ll>> paths(n,deque<ll>());
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                ll element;
                cin>>element;
                paths[i].push_back(element);
            }
            sort(paths[i].begin(),paths[i].end());
        }

        vector<vector<ll>> sol(n, vector<ll>(m));
        for(int runner = 0; runner < m; runner++)
        {
            ll min_el = paths[0][0];
            int min_position = 0;
            for(int node = 0; node < n; node++)
            {
                if(paths[node][0] < min_el)
                {
                    min_position = node;
                    min_el = paths[node][0];
                }
            }
            paths[min_position].pop_front();
            sol[min_position][runner] = min_el;
            for(int node = 0; node < n; node++)
            {
                if(node != min_position)
                {
                    sol[node][runner] = paths[node].back();
                    paths[node].pop_back();
                }
            }
        }
        for(auto v: sol)
        {
            for(ll e: v)
            {
                cout << e << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
