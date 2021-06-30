#include <bits/stdc++.h>
using  namespace std;
typedef long long ll;

char oposite_chr(char c)
{
    if(c == '0')
        return '1';
    else if(c == '1')
        return '0';
    else
        return '2';
}

ll solve(const string& s)
{
    int n = s.size();
        int current_good_len = 1;
        char prev_char = '2';
        ll solution = 0;

        bool qm_started = false;
        int qm_l = -1, qm_r = -1;
        if(s[0] == '?')
        {
            prev_char = '?';
            qm_started = 1;
            qm_l = 0;
            qm_r = 0;
        }
        for(int i = 1; i < n; i++)
        {
            if(s[i] == '?')
            {
                if(qm_started)
                    qm_r++;
                else
                {
                    prev_char = s[i-1];
                    qm_l = i;
                    qm_r = i;
                    qm_started = true;
                }
                current_good_len++;
            }
            else
            {
                qm_started = false;

                if(s[i] == s[i-1] && s[i] != '?')
                {
                    solution += current_good_len*(current_good_len+1)/2;
                    current_good_len = 1;
                    qm_l = -1;
                    qm_r = -1;
                }
                else if((s[i] == prev_char && (qm_r - qm_l + 1) % 2 == 0) ||
                        (s[i] == oposite_chr(prev_char) && (qm_r - qm_l + 1) % 2 == 1))
                {
                    solution += current_good_len*(current_good_len+1)/2;
                    if(qm_l != -1)
                    {
                        prev_char = '?';
                        current_good_len = (i - qm_l +1);

                        int len = (qm_r - qm_l + 1);
                        solution -=  len*(len+1) / 2; // Remove double counting
                    }
                    else
                    {
                        current_good_len = 1;
                    }
                }
                else
                {
                    current_good_len++;
                }
            }

        }
        solution += current_good_len*(current_good_len+1)/2;
        return solution;
}

int main()
{
    /*ios::sync_with_stdio(false);
    cin.tie(0);*/
    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        string s; cin>>s;

        cout << solve(s) << "\n";
    }

    return 0;
}
