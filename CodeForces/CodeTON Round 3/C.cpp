#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

void flip_pos(int pos, string& s)
{
	if (s[pos] == '0')
		s[pos] = '1';
	else
		s[pos] = '0';
}

vector<pair<int, int>> solve(string a, string b)
{
	int n = a.size();
	int cnt_equal = 0;
	int cnt_diff = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == b[i])
			cnt_equal++;
		else
			cnt_diff++;
	}
	if (cnt_diff > 0 && cnt_equal > 0)
	{
		//cout << "NO\n";
		return { {-1,-1} };
	}
	int cnt_ops = 0;
	vector<pair<int, int>> ops;
	if (cnt_equal == 0)
	{
		cnt_ops++;
		ops.push_back({ 1,1 });
		flip_pos(0, a);
	}

	int cnt_pairs1 = 0;
	int cnt_pairs0 = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == '0')
			cnt_pairs0++;
		else
			cnt_pairs1++;
	}
	if (cnt_pairs1 == 1)
	{
		if (cnt_pairs0 == 0)
		{
			//cout << "NO\n";
			return { {-1,-1} };
		}
		else
		{
			int pos = -1;
			for (int i = 0; i < n; i++)
			{
				if (a[i] == '1')
				{
					pos = i;
					break;
				}
			}
			if (pos == 0)
			{
				ops.push_back({ 1,2 });
				ops.push_back({ 2,2 });
			}
			else
			{
				ops.push_back({ pos,pos + 1 });
				ops.push_back({ pos,pos });
			}
		}
	}
	else
	{
		if (cnt_pairs1 % 2 == 1)
		{
			if (cnt_pairs0 == 0)
			{
				ops.push_back({ 1,2 });
				flip_pos(0, a);
				flip_pos(1, a);
			}
			else
			{
				for (int i = 0; i < n - 1; i++)
				{
					if (a[i] == '1' && a[i + 1] == '0')
					{
						flip_pos(i, a);
						ops.push_back({ i + 1,i + 2 });
						ops.push_back({ i + 2, i + 2 });
						break;
					}
					if (a[i] == '0' && a[i + 1] == '1')
					{
						flip_pos(i + 1, a);
						ops.push_back({ i + 1,i + 2 });
						ops.push_back({ i + 1, i + 1 });
						break;
					}
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (a[i] == '1')
			{
				ops.push_back({ i + 1,i + 1 });
			}
		}
	}
	return ops;
}

bool check(string a, string b, const vector<pair<int, int>>& ops)
{
	if (ops.size() > 0 && ops[0].first == -1)
	{
		return true;
	}
	for (auto op: ops)
	{
		int l = op.first - 1;
		int r = op.second - 1;
		for (int i = l; i <= r; i++)
			flip_pos(i, a);
		for (int i = 0; i < l; i++)
			flip_pos(i, b);
		for (int i = r + 1; i < b.size(); i++)
			flip_pos(i, b);
	}
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != '0' || b[i] != '0')
		{
			return false;
		}
	}
	return true;
}

string rand_str(int len)
{
	string s(len, '0');
	for (int i = 0; i < len; i++)
		s[i] = '0' + rand() % 2;
	return s;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		string a, b;
		cin >> a >> b;
		auto ops = solve(a, b);
		if (ops.size() > 0 && ops[0].first == -1)
		{
			cout << "NO\n";
		}
		else
		{
			cout << "YES\n";
			cout << ops.size() << "\n";
			for (auto op : ops)
			{
				cout << op.first << " " << op.second << "\n";
			}
		}
	}

	return 0;
}