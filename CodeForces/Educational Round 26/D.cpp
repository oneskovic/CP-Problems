#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int find_max_fives(const vector<int>& cnt_fives, int k)
{
    vector<int> temp = cnt_fives;
    sort(temp.begin(),temp.end(), greater<int>());
    return accumulate(temp.begin(),temp.begin()+k,0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,k; cin>>n>>k;
    vector<int> cnt_twos(n);
    vector<int> cnt_fives(n);
    for(int i = 0; i < n; i++)
    {
        ll number; cin>>number;
        while(number % 2 == 0)
        {
            cnt_twos[i]++;
            number /= 2;
        }
        while(number % 5 == 0)
        {
            cnt_fives[i]++;
            number /= 5;
        }
    }
    const int max_fives = find_max_fives(cnt_fives,k);

    vector<vector<int>> dp = vector<vector<int>>(k+1, vector<int>(max_fives+1, -1));
    dp[1][cnt_fives[0]] = cnt_twos[0];
    dp[0][0] = 0;
    for(int pos = 1; pos < n; pos++)
    {
        auto prev_dp = dp;
        for(int taken_elements = 0; taken_elements <= k; taken_elements++)
        {
            for(int taken_fives = 0; taken_fives <= max_fives; taken_fives++)
            {
                dp[taken_elements][taken_fives] = max(dp[taken_elements][taken_fives], prev_dp[taken_elements][taken_fives]);
                if(taken_elements < k && prev_dp[taken_elements][taken_fives] > -1)
                {
                    dp[taken_elements+1][taken_fives+cnt_fives[pos]] = max(prev_dp[taken_elements+1][taken_fives+cnt_fives[pos]],
                                                                            prev_dp[taken_elements][taken_fives]+cnt_twos[pos]);
                }
            }
        }
    }

    int solution = 0;
    for(int taken_fives = 0; taken_fives <= max_fives; taken_fives++)
    {
        int zeros_cnt = min(dp[k][taken_fives], taken_fives);
        solution = max(solution, zeros_cnt);
    }

    cout << solution << "\n";

    return 0;
}
