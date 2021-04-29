#include <bits/stdc++.h>
#include <string>
using namespace std;

bool check(const string& s1, const string& s2, int l, int r)
{
    bool all_equal = true, all_different = true;
    for(int i = l; i <= r; i++)
    {
        if(s1[i] == s2[i])
            all_different = false;
        else
            all_equal = false;
    }
    return all_equal || all_different;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    for (int test_no = 0; test_no < test_cnt; test_no++)
    {
        int n; cin>>n;
        string s1, s2;
        cin >> s1 >> s2;
        int cnt_zeros = 0, cnt_ones = 0;
        int prev_pos = 0;
        bool possible = true;
        for(int i = 0; i < n; i++)
        {
            if(s1[i] == '0')
                cnt_zeros++;
            else
                cnt_ones++;
            if(cnt_zeros == cnt_ones)
            {
                if (!check(s1,s2,prev_pos,i))
                {
                    possible = false;
                    break;
                }
                prev_pos = i+1;
            }
        }
        if (possible)
        {
            if(prev_pos < n)
            {
                for(int i = prev_pos; i < n; i++)
                {
                    if(s1[i] != s2[i])
                    {
                        possible = false;
                        break;
                    }
                }
            }
        }

        if(possible)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
