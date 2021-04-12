#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_count; cin >> test_count;
	for (int test_no = 0; test_no < test_count; test_no++)
	{
		int n, k;
		cin >> n >> k;
		if (k > (n-1)/2)
		{
			cout << "-1\n";
			continue;
		}
		vector<int> elements(n);
		for (int i = 0; i < n; i++)
			elements[i] = n - i;
		int peaks = 0;
		for (int i = 0; i < n && peaks < k; i+=2)
		{
			swap(elements[i], elements[i + 1]);
			peaks++;
		}
		for (int i : elements)
			cout << i << " ";
		cout << "\n";
	}
	return 0;
}