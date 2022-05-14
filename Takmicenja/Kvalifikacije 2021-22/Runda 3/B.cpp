#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
using namespace std;
typedef long long ll;

tuple<ll, ll, ll> solve(ll n, ll A, ll B, ll C)
{
	if (2*n < A+B+C || n < 3)
	{
		return tuple<ll, ll, ll>{ -1, -1, -1 };
	}
	ll c = n - A + 1;
	ll z = n - B + 1;
	ll p = n - C + 1;
	ll delta = c + z + p - n;
	if (delta > 0)
	{
		c -= min(c - 1, delta);
	}
	delta = c + z + p - n;
	if (delta > 0)
	{
		z -= min(z - 1, delta);
	}
	delta = c + z + p - n;
	if (delta > 0)
	{
		p -= min(p - 1, delta);

	}
	return { c,z,p };

	return tuple<ll, ll, ll>{ c, z, p};
}

bool check(ll c, ll z, ll p, ll A, ll B, ll C, ll n)
{
	return z + p + 1 >= A && c + p + 1>= B && c + z + 1>= C && c + z + p == n && c > 0 && z > 0 && p > 0;
}

bool bruteforce(ll n, ll A, ll B, ll C)
{
	for (int c = 1; c <= n-A; c++)
	{
		for (int z = 1; z <= n-B; z++)
		{
			ll p = n - c - z;
			if (check(c,z,p,A,B,C,n))
			{
				return true;
			}
		}
	}
	return false;
}

void test()
{
	for (int n = 1; n <= 100; n++)
	{
		for (int A = 1; A <= n; A++)
		{
			for (int B = 1; B <= n; B++)
			{
				for (int C = 1; C <= n; C++)
				{

					auto sol = solve(n, A, B, C);
					bool possible = (get<0>(sol) != -1);
					bool sol_brutus = bruteforce(n, A, B, C);
					if (possible != sol_brutus || (possible && !check(get<0>(sol), get<1>(sol), get<2>(sol), A, B, C, n)))
					{
						solve(n, A, B, C);
						bruteforce(n, A, B, C);
						check(get<0>(sol), get<1>(sol), get<2>(sol), A, B, C, n);
						cout << "wa\n";
					}
					else
						cout << "ok\n";
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	test();

	ll n, pz, pc, zc;
	cin >> n >> pz >> pc >> zc;
	auto sol = solve(n, pz, pc, zc);
	if (get<0>(sol) == -1)
	{
		cout << "nemoguce\n";
	}
	else
	{
		cout << "moguce\n";
		cout << get<0>(sol) << " " << get<1>(sol) << " " << get<2>(sol) << "\n";
	}

	return 0;
}