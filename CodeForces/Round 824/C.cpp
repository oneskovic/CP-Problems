#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;
typedef long long ll;

bool can_connect(int x, int y, const vector<int>& indegree, const vector<int>& chain_id)
{
	int cnt_indegree_0 = 0;
	for (int i = 0; i < indegree.size(); i++)
		if (indegree[i] == 0)
			cnt_indegree_0++;
	if (cnt_indegree_0 == 1)
		return indegree[y] == 0;
	else
		return chain_id[x] != chain_id[y] && indegree[y] == 0;
}

void update_chain(int old_id, int new_id, vector<int>& chain_id)
{
	for (int i = 0; i < chain_id.size(); i++)
	{
		if (chain_id[i] == old_id)
		{
			chain_id[i] = new_id;
		}
	}
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
		vector<int> chr_map(26, -1);
		vector<int> indegree(26, 0);
		vector<int> chain_id(26);
		iota(chain_id.begin(), chain_id.end(), 0);
		for (int i = 0; i < n; i++)
		{
			int ltr = s[i] - 'a';
			if (chr_map[ltr] == -1)
			{
				for (int j = 0; j < 26; j++)
				{
					if (ltr == j)
						continue;
					
					if (can_connect(ltr,j,indegree,chain_id))
					{
						chr_map[ltr] = j;
						indegree[j]++;
						update_chain(chain_id[ltr], chain_id[j], chain_id);
						break;
					}
				}
			}
			char mapped_ltr = 'a' + chr_map[ltr];
			cout << mapped_ltr;
		}
		cout << "\n";
	}

	return 0;
}