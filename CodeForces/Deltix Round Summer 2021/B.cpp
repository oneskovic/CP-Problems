#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

ll count_swaps(vector<bool> elements, const vector<bool>& target)
{
	set<int> ones_positions, zeros_positions;
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i] == 0)
			zeros_positions.insert(i);
		else
			ones_positions.insert(i);
	}
	ll total_swaps = 0;
	for (int i = 0; i < target.size(); i++)
	{
		if (target[i] == elements[i])
		{
			if (elements[i] == 0)
				zeros_positions.erase(zeros_positions.begin());
			else
				ones_positions.erase(ones_positions.begin());
		}
		else
		{
			if (target[i] == 0)
			{
				int zero_pos = *zeros_positions.begin();
				total_swaps += zero_pos - i;
				swap(elements[i], elements[zero_pos]);
				zeros_positions.erase(zeros_positions.begin());
				ones_positions.erase(i);
				ones_positions.insert(zero_pos);
			}
			else
			{
				int one_pos = *ones_positions.begin();
				total_swaps += one_pos - i;
				swap(elements[i], elements[one_pos]);
				ones_positions.erase(ones_positions.begin());
				zeros_positions.erase(i);
				zeros_positions.insert(one_pos);
			}
		}
	}
	return total_swaps;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<bool> elements(n);
		vector<int> counts(2);
		for (int i = 0; i < n; i++)
		{
			ll a; cin >> a;
			elements[i] = a % 2;
			counts[elements[i]]++;
		}
		if ((n % 2 == 0 && counts[0] != counts[1]) || (n%2 == 1 && abs(counts[0] - counts[1]) != 1))
		{
			cout << "-1\n";
		}
		else
		{
			vector<bool> target1(n), target2(n);
			for (int i = 0; i < n; i++)
			{
				target1[i] = i % 2;
				target2[i] = (i + 1) % 2;
			}
			if (n % 2 == 0)
			{
				ll swaps1 = count_swaps(elements, target1);
				ll swaps2 = count_swaps(elements, target2);
				cout << min(swaps1, swaps2) << "\n";
			}
			else
			{
				if (counts[0] > counts[1])
					cout << count_swaps(elements, target1) << "\n";
				else
					cout << count_swaps(elements, target2) << "\n";
			}
		}
	}

	return 0;
}
