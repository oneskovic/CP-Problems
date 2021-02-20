#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ll long long

int divisions_to_zero(ll number, ll base)
{
	int l = 0;
	while (number > 0)
	{
		number = number / base;
		l++;
	}
	return l;
}
int main()
{
	int test_count; cin >> test_count;
	for (size_t i = 0; i < test_count; i++)
	{
		ll a, b; cin >> a >> b;
		if (b > a)
		{
			cout << "1\n";
		}
		else
		{
			int start_op_count = 0;
			if (b == 1)
			{
				start_op_count = 1;
				b = 2;
			}

			int max_increase_ops = divisions_to_zero(a, b) + 1;
			int min_op_count = INT_MAX;
			for (int i = 0; i <= max_increase_ops; i++)
			{
				int op_count = i + start_op_count + divisions_to_zero(a,b+i);
				min_op_count = min(min_op_count, op_count);
			}
			cout << min_op_count << "\n";
		}
	}
	return 0;
}