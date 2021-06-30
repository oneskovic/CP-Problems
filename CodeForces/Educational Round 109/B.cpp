#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        int n; cin>>n;
        vector<int> elements(n);
        for(int i = 0; i < n; i++)
            cin>>elements[i];
        if(is_sorted(elements.begin(),elements.end()))
            cout << "0\n";
        else if(elements[0] == 1 || elements[n-1] == n)
            cout << "1\n";
        else if(elements[0] != n || elements[n-1] != 1)
            cout << "2\n";
        else
            cout << "3\n";
    }
    return 0;
}
