#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        int x; cin>>x;
        int mask = 1;
        int left_most_one = -1;
        for(int i = 0; i < 31; i++)
        {
            if(x & mask)
            {
                left_most_one = i;
            }
            mask <<= 1;
        }
        cout << (1 << left_most_one) - 1 << "\n";
    }

    return 0;
}
