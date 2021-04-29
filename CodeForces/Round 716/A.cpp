#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<pair<int,int>> factor(int number)
{
    vector<pair<int,int>> factors;
    for(int possible_factor = 2; possible_factor*possible_factor <= number; possible_factor++)
    {
        int cnt = 0;
        while(number % possible_factor == 0)
        {
            cnt++;
            number /= possible_factor;
        }
        if(cnt > 0)
        {
            factors.push_back({possible_factor, cnt});
        }
    }
    if(number > 1)
        factors.push_back({number,1});
    return factors;
}



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    for (int test_no = 0; test_no < test_cnt; test_no++)
    {
        int n; cin>>n;
        bool possible = false;
        for(int i = 0; i < n; i++)
        {
            int number; cin>>number;
            if(!possible)
            {
                auto factors = factor(number);
                for(auto fact: factors)
                {
                    int f = fact.first;
                    int cnt = fact.second;
                    if(cnt % 2 == 1)
                    {
                        possible = true;
                        break;
                    }
                }
            }
        }
        if(possible)
        {
            cout << "YES\n";
        }
        else
            cout << "NO\n";
    }
    return 0;
}
