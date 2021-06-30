#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
public:
    SegmentTree(const vector<int>& elements);
    void update(int position, int new_value);
    int max_query(int l, int r);
private:
    int element_cnt;
    vector<int> tree;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin>>n;
    vector<int> a(n),b(n);
    for(int i = 0; i < n; i++)
        cin>>a[i];
    vector<int> position_of_element_in_b(n+1,-1);
    for(int i = 0; i < n; i++)
    {
        cin>>b[i];
        position_of_element_in_b[b[i]] = i;
    }
    SegmentTree b_segment_tree = SegmentTree(vector<int>(n,0));
    int solution = INT_MIN;
    for(int i = n-1; i >= 0; i--)
    {
        int pos_in_b = position_of_element_in_b[a[i]];
        int current_solution = b_segment_tree.max_query(pos_in_b,n) + 1;
        b_segment_tree.update(pos_in_b,current_solution);
        solution = max(current_solution, solution);
    }
    cout << solution << "\n";

    return 0;
}

SegmentTree::SegmentTree(const vector<int>& elements)
{
    element_cnt = elements.size();
    tree = vector<int>(2*element_cnt);
    copy(elements.begin(),elements.end(),tree.begin()+element_cnt);
    for(int i = element_cnt-1; i > 0; i--)
        tree[i] = max(tree[2*i],tree[2*i + 1]);
}

void SegmentTree::update(int position, int new_value)
{
    position += element_cnt;
    tree[position] = new_value;
    for(int i = position/2; i > 0; i/=2)
        tree[i] = max(tree[2*i],tree[2*i+1]);
}

int SegmentTree::max_query(int l, int r)
{
    l += element_cnt;
    r += element_cnt;
    int max_val = INT_MIN;
    while(l < r)
    {
        if(l %2 == 1)
            max_val = max(max_val,tree[l++]);
        if(r % 2 == 1)
            max_val = max(max_val, tree[--r]);

        l/= 2;
        r/= 2;
    }
    return max_val;
}
