#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void get_ands_ors(vector<int>& ands, vector<int>& ors)
{
	cout << "and 1 2\n" << "and 1 3\n" << "and 2 3\n";
	cout << "or 1 2\n" << "or 1 3\n" << "or 2 3\n";
	fflush(stdout);
	cin >> ands[0] >> ands[1] >> ands[2] >> ors[0] >> ors[1] >> ors[2];
}

bool find_from_values(bool x_and_y, bool x_or_y, bool& x_bit, bool& y_bit)
{
	if (x_and_y == 0 && x_or_y == 1)
		return false;
	if (x_and_y == 0 && x_or_y == 0)
	{
		x_bit = 0; y_bit = 0;
	}
	if (x_and_y == 1 && x_or_y == 1)
	{
		x_bit = 1; y_bit = 1;
	}
	return true;
}

bool find_when_one_known(bool x, bool x_and_y, bool x_or_y)
{
	if (x_and_y == 0 && x_or_y == 0)
	{
		return 0;
	}
	else if (x_and_y == 1 && x_or_y == 1)
	{
		return 1;
	}
	else
	{
		if (x == 1)
			return 0;
		else
			return 1;
	}
}

void get_first_3(vector<int>& elements)
{
	vector<int> ands(3), ors(3);
	get_ands_ors(ands, ors);
	int a = 0, b = 0, c = 0;
	int mask = 1;
	for (int i = 0; i < 30; i++)
	{
		bool a_and_b = (ands[0] & mask), a_and_c = (ands[1] & mask), b_and_c = (ands[2] & mask);
		bool a_or_b = (ors[0] & mask), a_or_c = (ors[1] & mask), b_or_c = (ors[2] & mask);
		bool a_found = false, b_found = false, c_found = false;
		bool a_bit = 0, b_bit = 0, c_bit = 0;
		if (find_from_values(a_and_b, a_or_b, a_bit, b_bit))
		{
			a_found = 1; b_found = 1;
		}
		if (find_from_values(a_and_c, a_or_c, a_bit, c_bit))
		{
			a_found = 1; c_found = 1;
		}
		if (find_from_values(b_and_c, b_or_c, b_bit, c_bit))
		{
			b_found = 1; c_found = 1;
		}
		if (!a_found)
			a_bit = find_when_one_known(b_bit, a_and_b, a_or_b);
		if (!b_found)
			b_bit = find_when_one_known(a_bit, a_and_b, a_or_b);
		if (!c_found)
			c_bit = find_when_one_known(a_bit, a_and_c, a_or_c);
		
		a |= (mask * a_bit);
		b |= (mask * b_bit);
		c |= (mask * c_bit);
		mask <<= 1;
	}
	elements[0] = a;
	elements[1] = b;
	elements[2] = c;
}

int main()
{
	int n, k; cin >> n >> k;
	vector<int> elements(n);
	get_first_3(elements);
	for (int i = 3; i < n; i++)
	{
		cout << "and 1 " << i+1 << "\n";
		cout << "or 1 " << i+1 << "\n";
		fflush(stdout);
		int x_and_0, x_or_0;
		cin >> x_and_0 >> x_or_0;
		
		int mask = 1;
		for (int j = 0; j < 30; j++)
		{
			bool x_bit = find_when_one_known(elements[0] & mask, x_and_0 & mask, x_or_0 & mask);
			if (x_bit)
				elements[i] |= mask;
			mask <<= 1;
		}
	}
	sort(elements.begin(), elements.end());
	cout << "finish " << elements[k - 1] << "\n";
	fflush(stdout);

	return 0;
}
