#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
using namespace std;
typedef long long ll;

ll calculate(const vector<ll>& heights)
{
	ll solution = heights[0];
	int n = heights.size();
	for (int i = 1; i < n; i++)
	{
		solution += abs(heights[i] - heights[i - 1]);
	}
	solution += heights.back();
	return solution;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<ll> heights(n);
		for (int i = 0; i < n; i++)
		{
			cin >> heights[i];
		}
		if (n == 1)
		{
			cout << heights[0] << endl;
			continue;
		}
		heights.push_back(0);
		deque<ll> window;
		window.push_back(0);
		window.push_back(heights[0]);
		ll solution = 0;
		for (int i = 1; i <= n; i++)
		{
			window.push_back(heights[i]);
			if (window[0] < window[1] && window[1] > window[2])
			{
				solution += heights[i - 1] - max(window[0], window[2]);
				heights[i - 1] = max(window[0], window[2]);
				window[1] = heights[i - 1];
			}
			window.pop_front();
		}
		solution += calculate(heights);
		cout << solution << endl;
	}
	return 0;
}