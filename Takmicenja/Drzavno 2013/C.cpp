#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;
typedef long long ll;

int construct_upto(int n, int pow_of_2, vector<int>& solution, int pos)
{
	if (n == 0)
	{
		return 0;
	}
	int mask = 1 << pow_of_2;
	solution[pos] |= mask;	
	return -1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, s, k; cin >> n >> s >> k;
	vector<int> sum_pows_of2(15,0);
	int mask = 1;
	for (int i = 0; i < 15; i++)
	{
		if (mask & s)
		{
			sum_pows_of2[i]++;
		}
		mask <<= 1;
	}
	vector<int> solution(n);
	for (int j = 0; j < n; j++)
	{
		mask = 1 << 14;
		for (int i = 14; i >= 0; i--)
		{
			int remaining = 0;
			if (mask & k)
			{
				if (sum_pows_of2[i] % 2 == 0)
				{
					remaining += 2;
					construct_upto(sum_pows_of2[i] - 1, i, solution,j);
					sum_pows_of2[i]--;
				}
				else
				{
					construct_upto(sum_pows_of2[i], i, solution,j);
				}
			}
			else
			{
				if (sum_pows_of2[i] % 2 == 1)
				{
					remaining += 2;
					construct_upto(sum_pows_of2[i] - 1, i, solution,j);
					sum_pows_of2[i]--;
				}
				else
				{
					construct_upto(sum_pows_of2[i], i, solution,j);
				}
			}
			if (i > 0)
			{
				sum_pows_of2[i - 1] += remaining;
			}
			if (mask & solution[j])
			{
				sum_pows_of2[i]--;
			}
			mask >>= 1;
		}
	}

	for (int x: solution)
	{
		cout << x << " ";
	}

	return 0;
}