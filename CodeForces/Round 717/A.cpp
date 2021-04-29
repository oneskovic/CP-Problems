#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    for(int test_no = 0; test_no < test_cnt; test_no++)
    {
        int n,k;
        cin>>n>>k;
        vector<int> elements(n);
        for(int i = 0; i < n; i++)
        {
            cin>>elements[i];
        }
        int l = 0, r = n-1;
        for(int i = 0; i < k && l < r; i++)
        {
            while(elements[l] == 0 && l < r)
            {
                l++;
            }
            elements[l]--;
            elements[r]++;
        }
        for(int e: elements)
            cout << e << " ";
        cout << "\n";
    }
    return 0;
}
