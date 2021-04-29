#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    for(int test_no = 0; test_no < test_cnt; test_no++)
    {
        int n;
        cin>>n;
        vector<int> elements(n);
        vector<int> prefix_xor(n);
        cin>>elements[0];
        prefix_xor[0] = elements[0];
        for(int i = 1; i < n; i++)
        {
            cin>>elements[i];
            prefix_xor[i] = elements[i] ^ prefix_xor[i-1];
        }

        bool possible = false;
        for(int i = 0; i < n; i++)
        {
            int left_xor, right_xor;
            left_xor = prefix_xor[i];
            right_xor = prefix_xor[n-1] ^ prefix_xor[i];
            if(left_xor == right_xor)
            {
                possible = 1;
                break;
            }
        }
        if(!possible && elements.size() > 2)
        {
            for(int i = 0; i < n-2; i++)
            {
                for(int j = i+2; j < n; j++)
                {
                    int left_xor = prefix_xor[i];
                    int right_xor = prefix_xor[n-1] ^ prefix_xor[j-1];
                    int middle_xor = prefix_xor[j-1] ^ prefix_xor[i];
                    if(left_xor == right_xor && right_xor == middle_xor)
                    {
                        possible = 1;
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
