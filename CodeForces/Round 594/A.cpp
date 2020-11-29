#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;

ll fibonacci(int n)
{	
	vector<ll> computed_values(n + 2);
	computed_values[1] = 1;
	computed_values[2] = 2;
	
	for (size_t i = 3; i <= n; i++)
	{
		computed_values[i] = computed_values[i - 1] + computed_values[i - 2];
		computed_values[i] %= mod;
	}

	return (2*computed_values[n])%mod;
}

int main()
{
	int rows, cols; cin >> rows >> cols;
	ll result = fibonacci(rows) + fibonacci(cols) - 2;
	result %= mod;
	cout << result;
	return 0;
}