#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int gcd(const vector<int>& elements)
{
	int g = elements[0];
	for (int i = 1; i < elements.size(); i++)
	{
		g = gcd(g, elements[i]);
	}
	return g;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];
		if (gcd(elements) == 1)
		{
			cout << "0\n";
		}
		else
		{
			auto elements_copy = elements;
			elements[n-1] = gcd(elements[n-1], n);
			if (gcd(elements) == 1)
			{
				cout << "1\n";
				continue;
			}
			elements[n - 1] = elements_copy[n - 1];
			elements[n - 2] = gcd(elements[n - 2], n - 1);
			if (gcd(elements) == 1)
			{
				cout << "2\n";
				continue;
			}
			cout << "3\n";
		}

	}

	return 0;
}