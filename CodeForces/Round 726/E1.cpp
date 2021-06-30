#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;
typedef long long ll;

string append_copies(int length, const string& s)
{
	string result(length, ' ');
	int j = 0;
	for (int i = 0; i < length; i++, j = (++j % s.size()))
	{
		result[i] = s[j];
	}
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k; cin >> n >> k;
	string original_str; cin >> original_str;
	string optimal_str = string(k, 'z');
	for (int len = 1; len <= n; len++)
	{
		string substr = original_str.substr(0, len);
		string s = append_copies(k, substr);
		if (s < optimal_str)
		{
			optimal_str = s;
		}
	}
	
	cout << optimal_str << "\n";
	return 0;
}