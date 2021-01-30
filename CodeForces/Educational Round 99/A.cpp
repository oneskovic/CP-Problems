#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		string s; cin >> s;
		cout << s.size() << "\n";
	}
	return 0;
}