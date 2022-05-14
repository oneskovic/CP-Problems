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
		vector<string> bigrams(n-2);
		for (int i = 0; i < n-2; i++)
			cin >> bigrams[i];
		bool found = false;
		cout << bigrams[0][0];
		for (int i = 1; i < bigrams.size(); i++)
		{
			if (bigrams[i - 1][1] != bigrams[i][0])
			{
				cout << bigrams[i - 1][1];
				cout << bigrams[i][0];
				found = 1;
			}
			else
				cout << bigrams[i][0];
		}
		cout << bigrams.back()[1];
		if (!found)
		{
			cout << "a";
		}
		cout << "\n";
	}
	return 0;
}
