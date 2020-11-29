#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
const ll mod = 998244353;
ll factorial(ll n)
{
	ll product = 1;
	for (ll i = 2; i <= n; i++)
	{
		product *= i;
		product %= mod;
	}
	return product % mod;
}
int main()
{
	int n; cin >> n;
	vector<int> degree(n);
	for (size_t i = 0; i < n-1; i++)
	{
		int node1, node2; cin >> node1 >> node2;
		degree[--node1]++;
		degree[--node2]++;
	}
	ll solution = n;
	for (size_t i = 0; i < n; i++)
	{
		solution *= factorial(degree[i]);
		solution %= mod;
	}
	cout << solution % mod;
	return 0;
}