#include <bits/stdc++.h>
#include <string>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    for (int test_no = 0; test_no < test_cnt; test_no++)
    {
        int n; cin>>n;
        string s; cin>>s;
        int cnt_zeros = 0, cnt_ones = 0;
        for(int i = 0; i < n; i++)
        {
            if(s[i] == '0')
                cnt_zeros++;
            else
                cnt_ones++;
        }
        if(cnt_zeros % 2 != 0)
        {
            cout << "NO\n";
        }
        else
        {
            int ones_set = 0;
            int zeros_set = 0;
            string brackets1 = string(n,' '), brackets2 = string(n, ' ');
            for(int i = 0; i < n; i++)
            {
                if(s[i] == '1')
                {
                    if(ones_set < cnt_ones/2)
                    {
                        brackets1[i] = '(';
                        brackets2[i] = '(';
                        ones_set++;
                    }
                    else
                    {
                        brackets1[i] = ')';
                        brackets2[i] = ')';
                    }
                }
                else
                {
                    if(zeros_set % 2 == 0)
                    {
                        brackets1[i] = '(';
                        brackets2[i] = ')';
                    }
                    else
                    {
                        brackets1[i] = ')';
                        brackets2[i] = '(';
                    }
                    zeros_set++;
                }
            }
            // Check if brackets are valid
            bool valid = true;
            int sum1 = 0, sum2 = 0;
            for(int i = 0; i < n; i++)
            {
                if(brackets1[i] == '(')
                    sum1++;
                else
                    sum1--;

                if(brackets2[i] == '(')
                    sum2++;
                else
                    sum2--;

                if(sum1 < 0 || sum2 < 0)
                {
                    valid = 0;
                    break;
                }
            }
            if (sum1 > 0 || sum2 >0)
                valid = 0;
            if(valid)
            {
                cout << "YES\n";
                cout << brackets1 << "\n" << brackets2 << "\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
