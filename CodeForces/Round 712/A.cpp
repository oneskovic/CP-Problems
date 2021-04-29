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
        string s; cin>>s;
        int l = 0, r = s.size()-1;
        bool possible = false;
        while(l <= r && !possible)
        {
            if(s[l] == s[r] && s[l] != 'a')
            {
                s.insert(l, "a");
                possible = 1;
            }
            else
            {
                if(s[l] != 'a')
                {
                    s.insert(r, "a");
                    possible = 1;
                }
                else if (s[r] != 'a')
                {
                    s.insert(l, "a");
                    possible = 1;
                }
            }
            l++;
            r--;
        }
        if(possible)
        {
            cout << "YES\n" << s << "\n";
        }
        else
            cout << "NO\n";
    }

    return 0;
}
