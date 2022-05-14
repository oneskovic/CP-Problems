#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h> 
#include <chrono>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	vector<ll> precomputed_pows(11);
	for (int i = 0; i < 11; i++)
		precomputed_pows[i] = pow(10, i);
	
	while (test_cnt--)
	{
		int n; cin >> n;
		ll k; cin >> k; k++;

		vector<int> pows_of_10(n);
		for (int i = 0; i < n; i++)
			cin >> pows_of_10[i];
		
		vector<ll> max_ammounts(n);
		for (int i = 0; i < n-1; i++)
		{
			int p = pows_of_10[i + 1] - pows_of_10[i];
			ll max_ammount = precomputed_pows[p] - 1;
			max_ammounts[i] = max_ammount;
		}

		ll solution = 0;
		for (int i = 0; i < n-1 && k > 0; i++)
		{
			solution += precomputed_pows[pows_of_10[i]]*min(max_ammounts[i], k);
			k -= max_ammounts[i];
		}
		if (k > 0)
		{
			int max_p = pows_of_10.back();
			solution += precomputed_pows[max_p] * k;
		}
		if (pows_of_10[0] != 0)
			solution = 1;
		
		cout << solution << "\n";
	}
	return 0;
}