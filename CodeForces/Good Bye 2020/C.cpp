#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		string s; cin >> s;
		int n = s.size();
		vector<bool> changed(n);
		for (int i = 1; i < n; i++)
		{
			if (s[i - 1] == s[i] && !changed[i - 1])
				changed[i] = true;
			else if (i > 1 && s[i - 2] == s[i] && !changed[i-2])
				changed[i] = true;
		}
		cout << count(changed.begin(), changed.end(), 1) << "\n";
	}

	return 0;
}