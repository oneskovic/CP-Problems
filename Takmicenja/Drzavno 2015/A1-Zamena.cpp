#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<int> elements(n), dp(1e7, 0);
    for(int i = 0; i < n; i++)
        cin>>elements[i];
    vector<bool> available(1e7, false);
    int solution = INT_MIN;
    for(int i = n-1; i >= 0; i--)
    {
        int digits_left = elements[i];
        int multiply_left = 1;
        while(digits_left > 0)
        {
            int d = digits_left % 10;
            digits_left /= 10;
            multiply_left *= 10;

            for(int new_digit = 0; new_digit < 10; new_digit++)
            {
                int new_number = (digits_left*10+new_digit)*(multiply_left/10) + (elements[i] % (multiply_left/10));
                if(available[new_number])
                {
                    dp[elements[i]] = max(dp[elements[i]], dp[new_number] + abs(new_digit - d));
                }
            }
        }
        available[elements[i]] = 1;
        solution = max(solution, dp[elements[i]]);
    }
    cout << solution << "\n";

    return 0;
}
