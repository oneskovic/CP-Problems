#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> largest_perm(const vector<pair<int,int>>& prefix_max, int n)
{
    vector<int> perm;
    set<int> remaining;
    for(int i = 1; i <= n; i++)
    {
        remaining.insert(i);
    }
    for(auto p: prefix_max)
    {
        remaining.erase(p.first);
    }
    for(int i = 0; i < prefix_max.size(); i++)
    {
        int number = prefix_max[i].first;
        int cnt = prefix_max[i].second;
        perm.push_back(number);
        for(int j = 0; j < cnt-1; j++)
        {
            auto lb = remaining.lower_bound(number);
            lb--;
            perm.push_back(*lb);
            remaining.erase(lb);
        }
    }
    return perm;
}
vector<int> smallest_perm(const vector<pair<int,int>>& prefix_max, int n)
{
    vector<int> perm;
    set<int> remaining;
    for(int i = 1; i <= n; i++)
        remaining.insert(i);

    for(auto p: prefix_max)
        remaining.erase(p.first);

    for(int i = 0; i < prefix_max.size(); i++)
    {
        int number = prefix_max[i].first;
        int cnt = prefix_max[i].second;
        perm.push_back(number);
        for(int j = 0; j < cnt-1; j++)
        {
            int smallest = *remaining.begin();
            perm.push_back(smallest);
            remaining.erase(smallest);
        }
    }
    return perm;
}
void print_vec(const vector<int>& v)
{
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    for(int test_no = 0; test_no < test_cnt; test_no++)
    {
        int n; cin>>n;
        vector<pair<int,int>> prefix_max;
        int current_number; cin>>current_number;
        int current_cnt = 1;
        for(int i = 0; i < n-1; i++)
        {
             int number; cin>>number;
             if(number == current_number)
             {
                 current_cnt++;
             }
             else
             {
                 prefix_max.push_back({current_number,current_cnt});
                 current_number = number;
                 current_cnt = 1;
             }
        }
        prefix_max.push_back({current_number, current_cnt});

        auto perm = smallest_perm(prefix_max, n);
        print_vec(perm);
        perm = largest_perm(prefix_max, n);
        print_vec(perm);
    }

    return 0;
}
