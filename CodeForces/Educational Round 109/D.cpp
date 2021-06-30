#include <bits/stdc++.h>
using namespace std;

int bruteforce_recurse(vector<int> one_positions, int current_position, set<int> remaining_zero_positions)
{
    if(current_position >= one_positions.size())
        return 0;
    int min_dist = INT_MAX;
    for(auto zero_pos: remaining_zero_positions)
    {
        int dist = abs(one_positions[current_position] - zero_pos);
        auto temp = remaining_zero_positions;
        temp.erase(zero_pos);
        min_dist = min(min_dist,dist+bruteforce_recurse(one_positions,current_position+1,temp));
    }
    return min_dist;
}

int brutus(set<int> one_positions, set<int> zero_positions)
{
    vector<int> ones = vector<int>(one_positions.begin(),one_positions.end());
    return bruteforce_recurse(ones,0,zero_positions);
}

vector<int> generate_test(int n)
{
    vector<int> v = vector<int>(n);
    for(int i = 0; i < n/2; i++)
        v[rand()%n] = 1;
    return v;
}

void print_vec(vector<vector<int>> v)
{
    for(auto row: v)
    {
        for(auto i: row)
            cout << i << " ";
        cout << "\n";
    }
    cout << "\n";
}

int solve(set<int> one_positions, set<int> zero_positions)
{
    vector<int> ones = vector<int>(one_positions.begin(),one_positions.end());
    vector<int> zeros = vector<int>(zero_positions.begin(),zero_positions.end());
    int n = ones.size();
    int m = zeros.size();
    if(n == 0)
        return 0;
    vector<vector<int>> dp = vector<vector<int>>(n,vector<int>(m, INT_MAX));
    for(int i = 0; i < n; i++)
    {
        int ones_on_right = n - i - 1;
        int ones_on_left = i;
        for(int j = ones_on_left; j < m && j < m - ones_on_right; j++)
        {
            int dist = abs(ones[i] - zeros[j]);
            if(j > 0)
            {
                dp[i][j] = dp[i][j-1];
            }
            if(i > 0 && j > 0)
                dp[i][j] = min(dp[i][j],dp[i-1][j-1]+dist);
            if(i == 0)
                dp[i][j] = min(dp[i][j],dist);
        }
        //print_vec(dp);
    }
    return *min_element(dp[n-1].begin(),dp[n-1].end());
}


void test()
{
    srand(time(0));
    for(int i = 0; i < 1000; i++)
    {
        int n = rand()%6 + 2;
        auto v = generate_test(n);
        set<int> zero_positions, one_positions;
        for(int i = 0; i < n; i++)
        {
            int a = v[i];
            if(a == 0)
                zero_positions.insert(i);
            else
                one_positions.insert(i);
        }
        int s1 = solve(one_positions,zero_positions);
        int s2 = brutus(one_positions, zero_positions);
        if(s1 != s2)
        {
            cout << "WA\n";
            for(int i: v)
            {
                cout << i << " ";
            }
            cout << "\n";
            system("pause");
        }
        else
            cout << "OK\n";
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    //test();

    int n; cin>>n;
    set<int> one_positions, zero_positions;
    for(int i = 0; i < n; i++)
    {
        int a; cin>>a;
        if(a == 0)
            zero_positions.insert(i);
        else
            one_positions.insert(i);
    }
    cout << solve(one_positions,zero_positions);

    return 0;
}
