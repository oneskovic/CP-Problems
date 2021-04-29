#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    for(int test_no = 0; test_no < test_cnt; test_no++)
    {
        int n,k; cin>>n>>k;
        string s; cin>>s;
        int l = 0;
        while(s[l] != '*')
            l++;
        int solution = 1;
        while (true)
        {
            int max_pos = min(n - 1, l + k);
            while (l < max_pos && s[max_pos] == '.')
            {
                max_pos--;
            }
            if (l == max_pos) {
              break;
            }
            solution++;
            l = max_pos;
        }
        cout << solution << "\n";
    }

    return 0;
}
