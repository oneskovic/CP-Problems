#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <queue>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
vector<ll> factorial;

ll extended_euclidean(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll d = extended_euclidean(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return d;
}

ll mod_inv(ll x)
{
	ll inverse, temp;
	extended_euclidean(x, mod, inverse, temp);
	return (inverse + mod) % mod;
}

ll n_choose_k(ll n, ll k)
{
	ll x = (factorial[n] * mod_inv(factorial[n - k])) % mod;
	return (x * mod_inv(factorial[k])) % mod;
}

void find_subset_containing(int x_a, int x_b, const vector<int>& perm_a, const vector<int>& number_pos_map_a,
	const vector<int>& perm_b, const vector<int>& number_pos_map_b, vector<int>& subsets, int subset_id)
{
	queue<pair<int, bool>> bfs_queue;
	bfs_queue.push({ x_a, 1 });
	bfs_queue.push({ x_b, 0 });
	subsets[x_a] = subset_id;
	subsets[x_b] = subset_id;
	while (!bfs_queue.empty())
	{
		int number = bfs_queue.front().first;
		bool arr = bfs_queue.front().second;
		bfs_queue.pop();
		bool next_arr = !arr;
		int pos_of_number = -1;
		if (arr == 0)
		{
			pos_of_number = number_pos_map_a[number];
		}
		else
		{
			pos_of_number = number_pos_map_b[number];
		}
		int x_a = perm_a[pos_of_number];
		int x_b = perm_b[pos_of_number];
		if (subsets[x_a] == -1)
		{
			bfs_queue.push({ x_a, 1 });
			subsets[x_a] = subset_id;
		}
		if (subsets[x_b] == -1)
		{
			bfs_queue.push({ x_b, 0 });
			subsets[x_b] = subset_id;
		}
	}
}

void compute_factorial(int max_n)
{
	factorial = vector<ll>(max_n + 1);
	factorial[0] = 1;
	for (int i = 1; i <= max_n; i++)
	{
		factorial[i] = factorial[i - 1] * i;
		factorial[i] %= mod;
	}
}

vector<int> rand_perm(int n)
{
	vector<int> v(n);
	iota(v.begin(), v.end(), 1);
	int perm_cnt = rand() % factorial[n];
	for (int i = 0; i < perm_cnt; i++)
	{
		next_permutation(v.begin(), v.end());
	}
	return v;
}

bool check_perms(const vector<int>& perm_a, const vector<int>& perm_b, bool check_row = false)
{
	for (int i = 0; i < perm_a.size(); i++)
	{
		if (perm_a[i] == perm_b[i])
		{
			return false;
		}
	}
	if (check_row)
	{
		vector<bool> set(perm_a.size() + 1);
		for (int i = 0; i < perm_a.size(); i++)
		{
			set[perm_a[i]] = 1;
		}
		if (count(set.begin(),set.end(),1) < perm_a.size())
		{
			return false;
		}
	}
	return true;
}

pair<vector<int>,vector<int>> generate()
{
	int n = rand() % 6 + 2;
	vector<int> perm_a = rand_perm(n), perm_b = rand_perm(n);
	while (!check_perms(perm_a,perm_b))
	{
		perm_b = rand_perm(n);
	}
	return { perm_a,perm_b };
}
ll solve(const vector<int>& perm_a, const vector<int>& perm_b)
{
	int n = perm_a.size();
	vector<int> number_pos_map_a(n + 1, -1), number_pos_map_b(n + 1, -1);
	for (int i = 0; i < n; i++)
		number_pos_map_a[perm_a[i]] = i;
	for (int i = 0; i < n; i++)
		number_pos_map_b[perm_b[i]] = i;
	

	vector<int> subsets(n + 1, -1);
	int subset_id = 0;
	for (int i = 0; i < n; i++)
	{
		if (subsets[perm_a[i]] == -1)
		{
			find_subset_containing(perm_a[i], perm_b[i], perm_a, number_pos_map_a, perm_b, number_pos_map_b, subsets, subset_id++);
		}
	}
	int subset_cnt = subset_id;
	ll solution = 0;
	for (int i = 0; i <= subset_cnt; i++)
	{
		solution += n_choose_k(subset_cnt, i);
		solution %= mod;
	}
	return solution;
}

ll count_recursive(vector<int>& perm_a, vector<int>& perm_b, int pos)
{
	if (pos == perm_a.size())
	{
		if (check_perms(perm_a,perm_b,true))
			return 1;
		return 0;
	}
	else
	{
		ll cnt_1 = count_recursive(perm_a, perm_b, pos + 1);
		swap(perm_a[pos], perm_b[pos]);
		ll cnt_2 = count_recursive(perm_a, perm_b, pos + 1);
		return cnt_1 + cnt_2;
	}
}

ll brutus(const vector<int>& perm_a, const vector<int>& perm_b)
{
	auto cpy_a = perm_a;
	auto cpy_b = perm_b;
	return count_recursive(cpy_a, cpy_b, 0);
}

void test()
{
	auto p = generate();
	auto perm_a = p.first;
	auto perm_b = p.second;
	

	ll sol1 = brutus(perm_a, perm_b);
	ll sol2 = solve(perm_a, perm_b);
	if (sol1 != sol2)
	{
		cout << "WA\n";
		solve(perm_a, perm_b);
	}
	else
		cout << "OK\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand(time(0));

	compute_factorial(4 * 1e5);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		
		int n; cin >> n;
		vector<int> perm_a(n), perm_b(n);
		for (int i = 0; i < n; i++)
		{
			cin >> perm_a[i];
		}
		for (int i = 0; i < n; i++)
		{
			cin >> perm_b[i];
		}
		auto sol = solve(perm_a, perm_b);
		cout << sol << endl;
	}
	return 0;
}