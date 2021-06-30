#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int solve(vector<ll> elements)
{
    int n = elements.size();
    priority_queue<ll, vector<ll>,greater<ll>> pq;
    ll positive_potion_sum = 0;
    ll negative_potion_sum = 0;
    int positive_potion_cnt = 0;
    int sol = 0;
    for(int i = 0; i < n; i++)
    {
        if(elements[i] > 0)
        {
            positive_potion_sum += elements[i];
            positive_potion_cnt++;
        }
        else
        {
            if(positive_potion_sum + negative_potion_sum + elements[i] >= 0)
            {
                negative_potion_sum += elements[i];
                pq.push(elements[i]);
            }
            else if(!pq.empty() && pq.top() < elements[i])
            {
                negative_potion_sum -= pq.top();
                pq.pop();
                negative_potion_sum += elements[i];
                pq.push(elements[i]);
            }
        }
        sol = max(positive_potion_cnt+(int)pq.size(),sol);
    }
    return sol;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    srand(time(0));
    int n; cin>>n;
    vector<ll> elements(n);
    for(int i = 0; i < n; i++)
        cin>>elements[i];
    cout << solve(elements);

    return 0;
}
