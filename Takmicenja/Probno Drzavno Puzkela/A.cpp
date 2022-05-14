#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
using namespace std;
typedef long long ll;

ll bruteforce(vector<ll>& v)
{
    ll solution = 0;
    int n = v.size();
    for(int i = 0; i < n; i++)
    {
        bool done = false;
        for (int j0 = 0; j0 <= i && !done; j0++)
        {
            for (int j1 = 0; j1 <= j0 && !done; j1++)
            {
                for (int j2 = 0; j2 <= j1 && !done; j2++)
                {
                    if(v[j2]+v[j1]+v[j0] == v[i])
                    {
                        solution++;
                        done = true;
                    }
                }
            }
        }
    }
    return solution;
}

vector<ll> rand_vec(int n)
{
    vector<ll> v(n);
    for (int i = 0; i < n; i++)
    {
        v[i] = rand()%30;
        if(rand()%2)
            v[i] *= -1;
    }
    return v;
}

ll solve(const vector<ll>& elements)
{
    int n = elements.size();
    ll max_val = 100;
    ll offset = 2*max_val;
    vector<vector<int>> sum_position_map(2*offset, vector<int>());
    

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            sum_position_map[elements[i]+elements[j]+offset].push_back(j);
        }
    }

    for (int i = 0; i < sum_position_map.size(); i++)
    {
        sort(sum_position_map[i].begin(), sum_position_map[i].end());
    }

    ll solution = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            ll diff = elements[i] - elements[j];
            if(sum_position_map[diff+offset].empty())
                continue;
            auto lb = upper_bound(sum_position_map[diff+offset].begin(), sum_position_map[diff+offset].end(),j);
            lb--;
            if(*lb <= j)
            {
                solution++;
                break;
            }
        }
    }
    return solution;
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    srand(time(0));
    // int n; cin >> n;
    // vector<ll> elements(n);
    // for (int i = 0; i < n; i++)
    // {
    //     cin>>elements[i];
    // }
    int test_cnt = 500000;
    while(test_cnt--)
    {
        int n = rand()%10+1;
        auto v= rand_vec(n);
        auto sol1 = solve(v);
        auto sol2 = bruteforce(v);
        if (sol1 != sol2)
        {
            cout << "wa\n";
            for(int i: v)
            {
                cout << i << " ";
            }
            break;
        }
        
    }

    // cout << solution << "\n";
    return 0;
}