#include <algorithm>
#include <iostream>
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
		string input, solution;
		cin >> input;
		solution = input;
		for (int i = 0; i < n; i++)
		{
			if (input[i] == 'L' || input[i] == 'R')
			{
				solution[i] = 'L';
				solution[i + 1] = 'R';
				i++;
			}
			else if (input[i] == 'U')
			{
				solution[i] = 'D';
			}
			else
			{
				solution[i] = 'U';
			}
		}
		cout << solution << "\n";
	}
	return 0;
}