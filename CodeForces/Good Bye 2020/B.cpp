#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		set<int> s;
		int n; cin >> n;
		for (size_t i = 0; i < n; i++)
		{
			int element; cin >> element;
			if (s.find(element) != s.end())
				s.insert(element + 1);
			else
				s.insert(element);
		}
		cout << s.size() << "\n";
	}

	return 0;
}