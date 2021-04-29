#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> factor_count;

void sieve(int max_n)
{
	factor_count = vector<int>(max_n+1, 0);
	for (int i = 2; i <= max_n; i++)
	{
		if (factor_count[i] > 0)
			continue;
		
		int j = i;
		while (j <= max_n)
		{
			int cnt = 0;
			int temp = j;
			while (temp % i == 0)
			{
				cnt++;
				temp /= i;
			}
			factor_count[j] += cnt;
			j += i;
		}
	}
}

map<int, int> convert_vector_pair_to_map(const vector<pair<int, int>>& v)
{
	map<int, int> m;
	for (auto p: v)
		m[p.first] = p.second;
	return m;
}

int gcd(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	return gcd(b, a % b);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	sieve(1e6);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		int p, q;
		cin >> p >> q;
		int g = gcd(p, q);
		p /= g;
		q /= g;
		cout << factor_count[p] + factor_count[q] << "\n";
	}
	return 0;
}