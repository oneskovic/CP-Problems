#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class SegmentTree
{
public:
    SegmentTree(const vector<ll>& elements);
    ll sum(int l, int r);
    void update(int position, ll new_value);
private:
    int element_cnt;
    vector<ll> tree;
};

void solve()
{
    int n,q; cin>>n>>q;
    vector<ll> elements(n);
    for(int i = 0; i < n; i++)
        cin>>elements[i];

    vector<ll> even_elements(n), odd_elements(n);
    vector<ll> even_elements_mult(n), odd_elements_mult(n);

    ll multiply = 1;
    for(int i = 0; i < n; i+= 2)
    {
        even_elements[i] = elements[i];
        even_elements_mult[i] = elements[i] * multiply;
    }

    multiply = 1;
    for(int i = 1; i < n; i+= 2)
    {
        odd_elements[i] = elements[i];
        odd_elements_mult[i] = elements[i] * multiply;
    }

    SegmentTree even_seg_tree = SegmentTree(even_elements);
    SegmentTree odd_seg_tree = SegmentTree(odd_elements);
    SegmentTree even_seg_tree_mult = SegmentTree(even_elements_mult);
    SegmentTree odd_seg_tree_mult = SegmentTree(odd_elements_mult);

    for(int i = 0; i < q; i++)
    {
        string type; cin>>type;
        if(type == "U")
        {
            int pos; cin>>pos;
            ll val; cin>>val;
            pos--;
            if(pos % 2 == 0)
            {
                even_seg_tree_mult.update(pos, val*(pos+1));
                even_seg_tree.update(pos, val);
            }
            else
            {
                odd_seg_tree_mult.update(pos, val*pos);
                odd_seg_tree.update(pos, val);
            }
        }
        else
        {
            int l, r; cin>>l>>r;
            l--; r--;
            ll even_sum = even_seg_tree_mult.sum(l,r);
            even_sum -=
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
    element_cnt = elements.size();
    tree = vector<ll>(2*element_cnt);
    copy(elements.begin(),elements.end(),tree.begin()+element_cnt);
    for(int i = element_cnt - 1; i > 0; i--)
    {
        tree[i] = tree[2*i] + tree[2*i+1];
    }
}

void SegmentTree::update(int position, ll new_value)
{
    position += element_cnt;
    tree[position] = new_value;
    for(int i = position/2; i > 0; i /= 2)
        tree[i] = tree[2*i] + tree[2*i+1];
}

ll SegmentTree::sum(int l, int r)
{
    l += element_cnt;
    r += element_cnt;
    ll sum = 0;
    while(l < r)
    {
        if(l % 2 == 1)
        {
            sum += tree[l++];
        }
        if(r % 2 == 1)
        {
            sum += tree[--r];
        }
        l /= 2;
        r /= 2;
    }
    return sum;
}
