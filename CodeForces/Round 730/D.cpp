#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, k; cin >> n >> k;
		int prev_number = 0;
		for (int i = 0; i < n; i++)
		{
			int number_to_try = (i^prev_number);
			prev_number = i;
			cout << number_to_try << endl;
			cout.flush();
			int answer; cin >> answer;
			if (answer == 1)
				break;
			if (answer == -1)
			{
				return 0;
			}
		}
	}
	return 0;
}