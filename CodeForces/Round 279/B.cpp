#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	ll available_time; cin >> available_time;
	vector<ll> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];
	vector<ll> prefix_sum(n);
	prefix_sum[0] = elements[0];
	for (int i = 1; i < n; i++)
		prefix_sum[i] = prefix_sum[i - 1] + elements[i];
	
	ll prefix_sum_l = 0;
	int l = -1, r = 0;
	int solution = 0;
	while (l < n-1 && r < n)
	{
		while (r < n && prefix_sum[r] - prefix_sum_l <= available_time)
			r++;
		
		solution = max(solution, r - l - 1);
		l++;
		prefix_sum_l = prefix_sum[l];
	}
	cout << solution << "\n";
	return 0;
}