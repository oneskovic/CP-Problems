#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	int count_a, count_b;
	cin >> count_a;
	vector<ll> elements_a(count_a);
	for (size_t i = 0; i < count_a; i++)
		cin>>elements_a[i];

	cin >> count_b;
	vector<ll> elements_b(count_b);
	for (size_t i = 0; i < count_b; i++)
		cin >> elements_b[i];
	
	if (accumulate(elements_a.begin(), elements_a.end(), 0) != accumulate(elements_b.begin(), elements_b.end(), 0))
	{
		cout << "-1\n";
		return 0;
	}

	int index_a = 0, index_b = 0;
	int max_length = 0;
	while (index_a < count_a && index_b < count_b)
	{
		if (elements_a[index_a] == elements_b[index_b])
		{
			index_a++;
			index_b++;
			max_length++;
		}
		else if (elements_a[index_a] < elements_b[index_b])
		{
			elements_b[index_b] -= elements_a[index_a];
			index_a++;
		}
		else
		{
			elements_a[index_a] -= elements_b[index_b];
			index_b++;
		}
	}
	if (elements_a[count_a-1] != elements_b[count_b-1])
		cout << "-1\n";
	else
		cout << max_length << "\n";

	return 0;
}