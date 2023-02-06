#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		n *= 2;
		multiset<int> elements;
		for (int i = 0; i < n; i++)
		{
			int x; cin >> x;
			elements.insert(x);
		}

		int largest_el = *(--elements.end());
		vector<pair<int, int>> solution;
		for (auto it = elements.begin(); it != --elements.end(); it++)
		{
			vector<pair<int, int>> operations;
			auto elements_cpy = elements;
			elements_cpy.erase(elements_cpy.find(*it));
			elements_cpy.erase(elements_cpy.find(largest_el));
			operations.push_back({ *it + largest_el,-1 });
			operations.push_back({ *it,largest_el });

			int x = largest_el;
			while (!elements_cpy.empty())
			{
				int largest = *(--elements_cpy.end());
				elements_cpy.erase(elements_cpy.find(largest));

				int other = x - largest;
				if (elements_cpy.find(other) == elements_cpy.end())
					break;
				elements_cpy.erase(elements_cpy.find(other));
				
				operations.push_back({ largest,other });
				x = largest;
			}
			if (elements_cpy.empty())
			{
				solution = operations;
				break;
			}
		}
		if (solution.empty())
			cout << "NO" << endl;
		else
		{
			cout << "YES" << endl;
			for (auto op : solution)
			{
				cout << op.first;
				if (op.second != -1)
					cout << " " << op.second;
				cout << endl;
			}
		}
	}

	
	return 0;
}