#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	vector<pair<int,int>> queries(test_cnt);
	for (int i = 0; i < test_cnt; i++)
	{
		cin >> queries[i].first;
		queries[i].second = i;
	}
	sort(queries.begin(), queries.end());
	vector<int> answers(test_cnt);
	int total_cnt = 0;
	int j = 0;
	for (int i = 1; i <= queries.back().first; i++)
	{
		total_cnt++;
		if (i % 2 == 0)
			total_cnt+=2;
		if (i % 3 == 0)
			total_cnt+=2;
		while (j < queries.size() && queries[j].first == i)
		{
			int query_ind = queries[j].second;
			answers[query_ind] = total_cnt;
			j++;
		}
	}
	for (int ans: answers)
		cout << ans << "\n";
	

	return 0;
}
