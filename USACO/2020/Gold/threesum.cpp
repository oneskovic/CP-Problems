#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
using namespace std;
typedef long long ll;

vector<ll> rand_vec(int n)
{
	vector<ll> v(n);
	for (int i = 0; i < n; i++)
		v[i] = rand() % 200 - 100;
	return v;
}

ll bruteforce(const vector<ll>& elements, int l, int r)
{
	ll solution = 0;
	for (int i = l; i <= r-2; i++)
	{
		map<ll, int> m;
		m[elements[i + 1]] = 1;
		for (int j = i+2; j <= r; j++)
		{
			ll sum = elements[i] + elements[j];
			solution += m[-sum];
			m[elements[j]]++;
		}
	}
	return solution;
}
struct query
{
	int l, r, index;
};

int main()
{
	//freopen("threesum.in", "r", stdin);
	//freopen("threesum.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, query_cnt; cin >> n >> query_cnt;
	vector<int> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];

	int map_offset = 1e6 + 5;
	vector<int> elements_between_map(2e6+10);

	vector<vector<int>> precomputed_pairs(n, vector<int>(n));
	for (int i = 0; i < n-1; i++)
	{
		elements_between_map[elements[i + 1] + map_offset] = 1;
		for (int j = i+2; j < n; j++)
		{ 
			int sum = elements[i] + elements[j];
			int cnt_valid = 0;
			if (-sum + map_offset < elements_between_map.size())
				cnt_valid = elements_between_map[-sum + map_offset];
			
			precomputed_pairs[i][j] = cnt_valid;
			elements_between_map[elements[j] + map_offset]++;
		}

		elements_between_map[elements[i + 1] + map_offset] = 0;
		for (int j = i + 2; j < n; j++)
			elements_between_map[elements[j] + map_offset]=0;
	}

	vector<vector<ll>> prefix_sums(n, vector<ll>(n));
	for (int col = 0; col < n; col++)
	{
		prefix_sums[col][0] = precomputed_pairs[0][col];
		for (int row = 1; row < n; row++)
			prefix_sums[col][row] = prefix_sums[col][row - 1] + precomputed_pairs[row][col];
	}

	
	for (int i = 0; i < n; i++)
	{
		ll solution = 0;
		for (int j = i+2; j < n; j++)
		{
			if (i == 0)
				solution += prefix_sums[j][j-2];
			else
				solution += prefix_sums[j][j - 2] - prefix_sums[j][i-1];
			
			precomputed_solutions[i][j] = solution;
		}
	}
	
	for (int q = 0; q < query_cnt; q++)
	{
		int l, r; cin >> l >> r;
		l--; r--;
		cout << precomputed_solutions[l][r] << "\n";
	}

	return 0;
}