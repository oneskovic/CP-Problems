#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> elements(n);
		int sum = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> elements[i];
			sum += elements[i];
		}
		int max_sum = INT_MIN;
		for (int i = 0; i < n-1; i++)
		{
			int temp = sum;
			sum -= elements[i];
			sum -= elements[i + 1];
			sum += -elements[i];
			sum += -elements[i + 1];
			max_sum = max(max_sum, sum);
			sum = temp;
		}
		cout << max_sum << endl;
	}

	return 0;
}