#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<int> elements(n);
		vector<int> solution(n);
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];

		for (size_t i = 0; i < n; i++)
		{
			if (i % 2 == 0)
			{
				solution[i] = elements[i / 2];
			}
			else
			{
				solution[i] = elements[n - 1 - i / 2];
			}
		}
		for (size_t i = 0; i < n; i++)
		{
			cout << solution[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}