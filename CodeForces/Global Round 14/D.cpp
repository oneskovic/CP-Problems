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
        int n, left_cnt, right_cnt; cin>>n>>left_cnt>>right_cnt;
        map<int,int> left,right;
        for(int i = 0; i < left_cnt; i++)
        {
            int a; cin>>a;
            left[a]++;
        }
        for(int i = 0; i < right_cnt; i++)
        {
            int a; cin>>a;
            right[a]++;
        }
        int operation_cnt = 0;

        for(auto kvp: left)
        {
            int cnt_in_right = right[kvp.first];
            int m = min(cnt_in_right, kvp.second);
            right[kvp.first] -= m;
            left[kvp.first] -= m;
            left_cnt -= m;
            right_cnt -= m;
        }
        if(left_cnt > right_cnt)
        {
            swap(left,right);
            swap(left_cnt,right_cnt);
        }
        // left_cnt <= right_cnt
        for(auto kvp: right)
        {
            while(right_cnt - left_cnt > 0 && right[kvp.first] > 1)
            {
                operation_cnt++;
                right_cnt -= 2;
                right[kvp.first] -= 2;
            }
        }
        // All the elements in right are singles
        int delta = right_cnt - left_cnt;
        operation_cnt += delta;
        right_cnt -= delta;

        //left_cnt == right_cnt
        operation_cnt += right_cnt;
        cout << operation_cnt << "\n";
    }
    return 0;
}
