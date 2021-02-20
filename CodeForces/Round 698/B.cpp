#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define ll long long

bool check_achievable(int number, set<int>& achievable)
{
	if (achievable.find(number) != achievable.end())
		return true;
	
	bool possible = false;
	for (int i: achievable)
	{
		if (i > 0 && number >= i && check_achievable(number-i,achievable))
		{
			achievable.insert(number);
			possible = true;
			break;
		}
	}
	return possible;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n, d; cin >> n >> d;
		set<int> achievable = set<int>({ 0 });
		for (int first_digit = 0; first_digit <= 9; first_digit++)
		{
			int number = first_digit * 10 + d;
			if (number <= d*10+d)
			{
				achievable.insert(number);
			}
		}
		for (int second_digit = 0; second_digit <= 9; second_digit++)
		{
			int number = d * 10 + second_digit;
			if (number <= d*10+d)
			{
				achievable.insert(number);
			}
		}

		for (int i = d; i < d*10+d; i++)
		{
			check_achievable(i, achievable);
		}
		
		for (size_t i = 0; i < n; i++)
		{
			ll number; cin >> number;
			if (number >= d*10+d ||
				achievable.find(number) != achievable.end())
			{
				cout << "YES\n";
			}
			else
			{
				cout << "NO\n";
			}
		}

	}
	return 0;
}