#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		string keyboard; cin >> keyboard;
		map<pair<char, char>, int> distances;
		for (int i = 0; i < keyboard.size(); i++)
		{
			for (int j = 0; j < keyboard.size(); j++)
			{
				distances[{keyboard[i], keyboard[j]}] = abs(i-j);
			}
		}
		string sentence_to_type; cin >> sentence_to_type;
		ll solution = 0;
		for (int i = 1; i < sentence_to_type.size(); i++)
		{
			pair<char, char> p = { sentence_to_type[i - 1],sentence_to_type[i] };
			solution += distances[p];
		}
		cout << solution << "\n";
	}
	return 0;
}