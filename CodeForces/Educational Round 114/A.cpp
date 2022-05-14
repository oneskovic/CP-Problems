#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
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
		string solution(2 * n, ' ');
		for (int start_len = 0; start_len < n; start_len++)
		{
			for (int i = 0; i < start_len; i++)
				cout << '(';
			for (int i = 0; i < start_len; i++)
				cout << ')';
			int rem = n - start_len;
			for (int i = 0; i < rem; i++)
				cout << '(';
			for (int i = 0; i < rem; i++)
				cout << ')';
			cout << "\n";
		}
		
		
	}
	return 0;
}