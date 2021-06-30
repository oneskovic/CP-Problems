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

        int min_el = *min_element(elements.begin(),elements.end());
        int min_cnt = count(elements.begin(),elements.end(),min_el);
        cout << n - min_cnt << "\n";
    }
    return 0;
}
