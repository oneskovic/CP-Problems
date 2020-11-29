#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		string s; cin >> s;
		int count_b = 0;
		int un_erasable = 0;
		for (int i = s.size()-1; i >= 0; i--)
		{
			if (s[i] == 'A')
			{
				if (count_b > 0)
				{
					count_b--;
				}
				else
					un_erasable++;
			}
			else
				count_b++;
		}
		un_erasable += count_b % 2;
		cout << un_erasable << "\n";
	}
	return 0;
}