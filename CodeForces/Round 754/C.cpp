#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <numeric>
using namespace std;
typedef long long ll;

bool exists_substr_of_len(int length, const string& s)
{
	map<char, int> cnt;
	int i = 0, j = 0;
	for (j = 0; j < length; j++)
	{
		cnt[s[j]]++;
	}
	if (cnt['a'] > cnt['b'] && cnt['a'] > cnt['c'])
		return true;
	
	for (j; j < s.size(); j++, i++)
	{
		cnt[s[i]]--;
		cnt[s[j]]++;
		if (cnt['a'] > cnt['b'] && cnt['a'] > cnt['c'])
			return true;
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		string s; cin >> s;
		bool found = 0;
		for (int len = 2; len <= min(10,(int)s.size()); len++)
		{
			if (exists_substr_of_len(len,s))
			{
				cout << len << "\n";
				found = 1;
				break;
			}
		}
		if (!found)
			cout << "-1\n";
	}
	return 0;
}