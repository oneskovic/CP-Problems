#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
    SegmentTree(const vector<ll>& elements);
    pair<ll,int> max_query(int l, int r);
    void update(int position, ll new_value);
private:
    vector<ll> tree;
    vector<ll> index_from_which_max;
    int element_cnt;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<ll> right_reach(n);
    for(int i = 0; i < n-1; i++)
    {
        cin>>right_reach[i];
    }
    right_reach[n-1] = n-1;
    vector<ll> dp(n);
    SegmentTree max_reach(right_reach);
    for(int i = n-2; i >= 0; i--)
    {
        auto q = max_reach.max_query(i,right_reach[i]);
        int max_index = q.second;
        dp[i] = dp[max_index] - (right_reach[i] - max_index) + n - i - 1;
    }
    cout << accumulate(dp.begin(),dp.end(),(ll)0);

    return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
    element_cnt = elements.size();
    tree = vector<ll>(2*element_cnt);
    index_from_which_max = tree;

    copy(elements.begin(), elements.end(),tree.begin()+element_cnt);
    iota(tree.begin()+element_cnt, tree.end(), 0);
    for(int i = element_cnt-1; i > 0; i--)
    {
        if(tree[2*i] >= tree[2*i+1])
        {
            index_from_which_max[i]= index_from_which_max[2*i];
            tree[i] = tree[2*i];
        }
        else
        {
            index_from_which_max[i] = index_from_which_max[2*i+1];
            tree[i] = tree[2*i+1];
        }
    }
}

pair<ll,int> SegmentTree::max_query(int l, int r)
{
    l += element_cnt;
    r += element_cnt;
    ll max_val = LLONG_MIN;
    int max_index = -1;
    while(l < r)
    {
        if(l % 2 == 1)
        {
            int node = l++;
            if(tree[node] > max_val)
            {
                max_val = tree[node];
                max_index = index_from_which_max[node];
            }
        }
        if(r % 2 == 1)
        {
            int node = --r;
            if(tree[node] > max_val)
            {
                max_val = tree[node];
                max_index = index_from_which_max[node];
            }
        }
        l/=2;
        r/=2;
    }
    return {max_val,max_index};
}

void SegmentTree::update(int position, ll new_value)
{
    position += element_cnt;
    tree[position] = new_value;
    for(int i = position/2; i > 0; i/=2)
    {
        if(tree[2*i] >= tree[2*i+1])
        {
            index_from_which_max[i] = index_from_which_max[2*i];
            tree[i] = tree[2*i];
        }
        else
        {
            index_from_which_max[i] = index_from_which_max[2*i+1];
            tree[i] = tree[2*i+1];
        }
    }
}
