#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n, m; cin >> n >> m;
		unordered_set<int> bottom_trains;
		for (size_t i = 0; i < n; i++)
		{
			int position; cin >> position;
			bottom_trains.insert(position);
		}

		int solution = 0;
		for (size_t i = 0; i < m; i++)
		{
			int position; cin >> position;
			if (bottom_trains.find(position) != bottom_trains.end())
			{
				solution++;
			}
		}
		
		cout << solution << "\n";
	}
	return 0;
}