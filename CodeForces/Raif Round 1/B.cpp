#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main()
{
	int no_tests; cin >> no_tests;
	for (size_t i = 0; i < no_tests; i++)
	{
		int n; cin >> n;
		string graph; cin >> graph;
		unordered_map<char, int> counts;
		for (size_t i = 0; i < n; i++)
			counts[graph[i]]++;
		if (counts['<'] == 0 || counts['>'] == 0)
			cout << n;
		else
		{
			vector<bool> is_returnable(n);
			for (size_t i = 0; i < n; i++)
			{
				if (graph[i] == '-')
				{
					is_returnable[i] = 1;
					is_returnable[(i + 1) % n] = 1;
				}
			}
			cout << count(is_returnable.begin(),is_returnable.end(),1);
		}
		cout << "\n";

	}
	return 0;
}