#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#define ll long long

int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		string s;
		cin >> s;
		int count_t = 0;
		for (size_t i = 0; i < n; i++)
			if (s[i] == 't')
				count_t++;
		
		s.erase(remove_if(s.begin(), s.end(), [](char c) {return c == 't'; }),s.end());
		string only_t(count_t, 't');
		cout << s + only_t << "\n";
	}
	return 0;
}