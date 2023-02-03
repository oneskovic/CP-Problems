#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;
typedef long long ll;

int count_matches(const string& s)
{
	string s_reversed = s;
	reverse(s_reversed.begin(), s_reversed.end());
	int mid = (s.size() - 1) / 2;
	int match_cnt = 0;
	for (int i = 0; i <= mid; i++)
	{
		if (s[i] != s_reversed[i])
			break;
		else
			match_cnt++;
	}
	return match_cnt;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s_start; cin >> s_start;
	vector<int> precomputed_score(12);
	for (int start_pos = 0; start_pos <= min(11, (int)s_start.size()-1); start_pos++)
	{
		string s(s_start.begin()+start_pos,s_start.end());
		
		precomputed_score[start_pos] = count_matches(s);
	}

	int query_cnt; cin >> query_cnt;
	for (int i = 0; i < query_cnt; i++)
	{
		string query_str; cin >> query_str;
		for (int start_pos = 1; start_pos < query_str.size(); start_pos++)
		{
			if (start_pos >= s_start.size())
			{
				string qs = string(query_str.begin(), query_str.begin()+start_pos);
				cout << count_matches(s_start + qs) << " ";
			}
			else
			{
				string l = string(s_start.begin(), s_start.begin() + start_pos);
				string qs = string(query_str.begin(), query_str.begin() + start_pos);
				reverse(qs.begin(), qs.end());
				if (l != qs)
				{
					reverse(qs.begin(), qs.end());
					cout << count_matches(l + qs) << " ";
				}
				else
				{
					cout << count_matches(l + qs) + precomputed_score[start_pos + 1] << " ";
				}
			}
		}
	}

	return 0;
}