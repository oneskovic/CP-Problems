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

	string s; cin >> s;
	int cnt1, cnt2; cin >> cnt1 >> cnt2;
	if (abs(cnt1-cnt2) <= 1)
	{
		bool start_char = 0;
		if (cnt2 > cnt1)
			start_char = 1;
		
		bool current_char = start_char;
		for (int i = 0; i < cnt1+cnt2; i++)
		{
			cout << s[current_char];
			current_char = !current_char;
		}
	}
	else
	{
		cout << "nemoguce";
	}

	return 0;
}