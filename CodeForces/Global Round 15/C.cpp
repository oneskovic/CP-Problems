#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
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
		for (int i = 0; i < n; i++)
			cin >> elements[i];

		sort(elements.begin(), elements.end());
		bool solved = false;
		vector<int> s;
		do
		{
			vector<int> solution(n);
			solution[0] = 0;
			for (int i = 0; i < n-1; i++)
			{
				if (elements[i] != 0)
				{
					solution[i+1] = elements[i];
				}
			}

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (solution[i] - solution[j] == elements[i])
					{
						solved = true;
						s = solution;
					}
				}
			}
		} while (next_permutation(elements.begin(),elements.end()) && !solved);
		if (solved)
		{
			cout << "YES\n";
		}
		else
			cout << "NO\n";
	}

	return 0;
}