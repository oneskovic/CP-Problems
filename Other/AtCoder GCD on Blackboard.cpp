#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> elements(n), prefix(n), suffix(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];
	prefix[0] = elements[0];
	for (int i = 1; i < n; i++)
		prefix[i] = gcd(prefix[i - 1], elements[i]);
	
	suffix[n - 1] = elements[n - 1];
	for (int i = n - 2; i >= 0; i--)
		suffix[i] = gcd(suffix[i + 1], elements[i]);
	int max_gcd = -1;
	for (int i = 0; i < n; i++)
	{
		int prefix_gcd = i == 0 ? suffix[i + 1] : prefix[i - 1];
		int suffix_gcd = i == n - 1 ? prefix[i - 1] : suffix[i + 1];
		int g = gcd(prefix_gcd, suffix_gcd);
		max_gcd = max(max_gcd, g);
	}
	cout << max_gcd;
	return 0;
}