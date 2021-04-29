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
        int n; cin>>n;
        map<int,int> number_cnt;
        for(int i = 0; i < n; i++)
        {
            ll number; cin>>number;
            number_cnt[number]++;
        }
        priority_queue<int> counts;
        for(auto kvp: number_cnt)
        {
            counts.push(kvp.second);
        }
        while(counts.size() > 1)
        {
            int largest = counts.top();
            counts.pop();
            int second_largest = counts.top();
            counts.pop();
            largest--;
            second_largest--;
            if(largest > 0)
                counts.push(largest);
            if(second_largest > 0)
                counts.push(second_largest);
        }
        if(counts.empty())
            cout << 0 << "\n";
        else
            cout << counts.top() << "\n";
    }

    return 0;
}
