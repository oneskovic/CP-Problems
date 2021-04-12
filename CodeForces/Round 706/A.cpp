#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool is_palindrome(const string& s)
{
	return s == string(s.rbegin(), s.rend());
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int test_count; cin>>test_count;
	for (int test_no = 0; test_no < test_count; test_no++)
	{
		int n, k;
		cin >> n >> k;
		string s; cin >> s;
		if (k == 0)
		{
			cout << "YES\n";
		}
		else
		{

			if (n%2 == 0 && k == n/2)
				cout << "NO\n";
			else
			{
				string left = string(s.begin(), s.begin() + k );
				string right = string(s.rbegin(), s.rbegin() + k );
				reverse(right.begin(), right.end());

				cout << (is_palindrome(left+right) ? "YES\n" : "NO\n");
			}
		}
	}
	return 0;
}
