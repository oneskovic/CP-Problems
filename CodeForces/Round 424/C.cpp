#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k; cin >> n >> k;
	vector<int> to_add(n);
	for (int i = 0; i < n; i++)
		cin >> to_add[i];
	vector<int> pref_sum(n);
	pref_sum[0] = to_add[0];
	for (int i = 1; i < n; i++)
		pref_sum[i] = pref_sum[i - 1] + to_add[i];

	vector<int> scores(k);
	for (int i = 0; i < k; i++)
		cin >> scores[i];
	int solution = 0;
	set<int> possible_x;
	for (int i = 0; i < n; i++)
	{
		int x = scores[0] - pref_sum[i];
		set<int> scores_for_x;
		for (int j = 0; j < n; j++)
		{
			scores_for_x.insert(x + pref_sum[j]);
		}

		bool possible = 1;
		for (int j = 0; j < k; j++)
		{
			if (scores_for_x.find(scores[j]) == scores_for_x.end())
			{
				possible = 0;
				break;
			}
		}
		if (possible)
		{
			possible_x.insert(x);
		}
	}
	cout << possible_x.size();
	return 0;
}