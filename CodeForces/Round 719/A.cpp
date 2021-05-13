#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        int n; cin>>n;
        string s; cin>>s;
        vector<int> first(26, -1);
        vector<int> last(26, -1);
        for(int i = 0; i < n; i++)
        {
            int c = s[i] - 'A';
            if(first[c] == -1)
                first[c] = i;
            last[c] = i;
        }

        bool correct = true;
        for(int letter = 0; letter < 26; letter++)
        {
            if(first[letter] == -1)
                continue;
            for(int other_letter = 0; other_letter < 26; other_letter++)
            {
                if(first[other_letter] == -1)
                    continue;
                if(other_letter == letter)
                    continue;
                if(first[other_letter] > first[letter] && first[other_letter] < last[letter])
                {
                    correct = false;
                }
            }
        }
        if(correct)
        {
            cout << "YES\n";
        }
        else
            cout << "NO\n";

    }
    return 0;
}
