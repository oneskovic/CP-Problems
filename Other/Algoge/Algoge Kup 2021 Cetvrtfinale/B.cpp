#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <set>
using namespace std;
typedef long long ll;

vector<bool> is_prime;
void sieve(int max_n)
{
	is_prime = vector<bool>(max_n + 1, 1);
	is_prime[0] = 0;
	is_prime[1] = 0;
	for (int i = 2; i <= max_n; i++)
	{
		if (is_prime[i])
		{
			for (int j = i + i; j <= max_n; j += i)
			{
				is_prime[j] = 0;
			}
		}
	}
}

vector<int> get_jumps(int a, int b, int n)
{
	int pos = 0;
	vector<int> positions; positions.reserve(n);

	while (true)
	{
		while (pos + a <= n)
		{
			pos += a;
			positions.push_back(pos);
		}
		if (pos == n)
		{
			return positions;
		}
		while (pos - b > 0)
		{
			pos -= b;
			positions.push_back(pos);
		}
	}
	return positions;
}

bool check(int n, vector<int> jumps)
{
	if (jumps.empty())
	{
		return 1;
	}
	set<int> s;
	for (int i : jumps)
	{
		if (s.find(i) != s.end())
		{
			return false;
		}
		s.insert(i);
	}
	return s.size() == n;
}

vector<int> solve(int n)
{
	sieve(n);
	if (n % 2 == 0)
	{
		for (int i = 2; i <= n; i++)
		{
			if (is_prime[i] && is_prime[n - i])
			{
				return get_jumps(i, n - i, n);
			}

			else if (is_prime[i] && (n - i) % 2 == 0 && is_prime[(n - i) / 2])
			{
				return get_jumps(i, n - i, n);
			}
		}
	}
	//cout << "NE\n";
	return vector<int>();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	auto s = solve(n);
	if (s.empty())
	{
		cout << "NE\n";
	}
	else
	{
		cout << "DA\n";
		for (int i : s)
		{
			cout << i << " ";
		}
	}

	/*for (int i = 5; i <= n; i++)
	{
		auto s = solve(i);
		if (!check(i,s))
		{
			cout << i << "\n";
			cout << "AAAAAAAAAA\n";
		}
	}*/

	return 0;
}