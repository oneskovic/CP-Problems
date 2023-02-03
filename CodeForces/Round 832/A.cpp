#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;
typedef long long ll;
 
int bruteforce(int sum_a, int sum_b, const vector<int>& elements, int pos = 0)
{
	if (pos == elements.size())
		return abs(sum_a) - abs(sum_b);
	
	int s1 = bruteforce(sum_a + elements[pos], sum_b, elements, pos + 1);
	int s2 = bruteforce(sum_a, sum_b + elements[pos], elements, pos + 1);
	return max(s1, s2);
}
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
 
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
 
		ll sum = 0;
		for (int i = 0; i < n; i++)
		{
			ll x; cin >> x;
			sum += x;
		}
		cout << abs(sum) << "\n";
	}
 
	return 0;
}