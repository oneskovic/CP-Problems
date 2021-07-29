#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s; cin >> s;
	int n = s.size();
	vector<int> elements(n);
	for (int i = 0; i < n; i++)
	{
		elements[i] = s[i] - '0';
	}

	int suffix = 0;
	vector<int> remainders(2019);
	remainders[0] = 1;
	long long cnt = 0;
	int power_of_ten = 1;
	for (int i = n - 1; i >= 0; i--)
	{
		suffix = (suffix + power_of_ten * elements[i]) % 2019;
		power_of_ten = (power_of_ten * 10) % 2019;
		cnt += remainders[suffix];
		remainders[suffix]++;
	}

	cout << cnt << endl;

	return 0;
}