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
        vector<int> elements(n);
        map<int, int> diff;
        for(int i = 0; i < n; i++)
            cin>>elements[i];

        for(int i = 1; i < n; i++)
        {
            int needed_number = elements[0] + i;
            diff[needed_number - elements[i]]++;
        }
        ll solution = diff[0];
        for(int i = 1; i < n; i++)
        {
            int needed_number = elements[0] + i;
            diff[needed_number - elements[i]]--;
            int diff_from_prev = elements[0] - elements[i] + i;
            solution += diff[diff_from_prev];
        }
        cout << solution << "\n";

    }
    return 0;
}
