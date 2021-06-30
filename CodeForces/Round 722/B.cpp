#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve_vector(ll start_value, const vector<ll>& v)
{
    int n = v.size();

    ll min_next_value = 0;
    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        if(v[i] <= min_next_value)
        {
            cnt++;
            min_next_value = v[i] - start_value;
        }
    }
    return cnt;
}

int solve(vector<ll> elements)
{
    vector<ll> negative,positive;
    int n = elements.size();
    for(int i = 0; i < n; i++)
    {
        ll element = elements[i];
        if(element > 0)
            positive.push_back(element);
        else
            negative.push_back(element);
    }
    ll min_positive = positive.empty() ? -1 : *min_element(positive.begin(),positive.end());
    sort(negative.begin(),negative.end(),greater<ll>());
    ll solution1 = positive.empty() ? 0 : solve_vector(min_positive,negative)+1;
    //ll solution2 = negative.empty() ? 0 : solve_vector(abs(negative[0]),negative);
    ll solution2 = negative.size();
    return max(solution1,solution2);
}

bool is_valid(vector<bool>& subset, const vector<ll>& v)
{
    vector<ll> values;
    for(int i = 0; i < subset.size(); i++)
    {
        if(subset[i])
            values.push_back(v[i]);
    }
    int n = values.size();
    if(n == 0)
        return true;
    ll max_el = *max_element(values.begin(),values.end());
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i != j && abs(values[i] - values[j]) < max_el)
            {
                return false;
            }
        }
    }
    return true;
}

int brutus_solution;
void brutus_recurse(int position, vector<bool>& subset, const vector<ll>& values)
{
    if(position == values.size())
    {
        if(is_valid(subset,values))
        {
            int sol_size = count(subset.begin(),subset.end(),1);
            brutus_solution = max(brutus_solution,sol_size);
        }
    }
    else
    {
        brutus_recurse(position+1,subset,values);
        subset[position] = 1;
        brutus_recurse(position+1,subset,values);
        subset[position] = 0;
    }

}

int brutus(vector<ll> elements)
{
    int n = elements.size();
    brutus_solution = -1;
    vector<bool> subset = vector<bool>(n);
    brutus_recurse(0,subset,elements);
    return brutus_solution;
}

void test()
{
    int n = rand() % 6;
    int max_el = 10;
    vector<ll> elements(n);
    for(int i = 0; i < n; i++)
    {
        int sign = rand()%2 == 0 ? -1:1;
        int rand_val = rand()%max_el + 1;
        rand_val*=sign;
        elements[i] = rand_val;
    }
    int s1 = brutus(elements);
    int s2 = solve(elements);
    if(s1 != s2)
    {
        cout<< "WA\n";
        system("pause");
    }
    else
        cout << "OK\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    srand(time(0));
    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        //test();
        int n; cin>>n;
        vector<ll> elements(n);
        for(int i = 0; i < n; i++)
            cin>>elements[i];
        cout << solve(elements) << "\n";


    }
    return 0;
}
