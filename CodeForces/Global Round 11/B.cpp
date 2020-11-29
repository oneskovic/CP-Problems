#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

long long solve(string S, int K)
{
	int N = S.size();
	int winning_streaks_cnt = 0;
	int wins = 0;
	int losses = 0;
	vector<int> losing_streaks;
	for (int i = 0; i < N; i++) {
		if (S[i] == 'W') {
			wins++;
			if (i == 0 or S[i - 1] == 'L') winning_streaks_cnt++;
		}
		if (S[i] == 'L') {
			losses++;
			if (i == 0 or S[i - 1] == 'W') losing_streaks.push_back(0);
			losing_streaks.back()++;
		}
	}
	if (K >= losses) {
		return 2 * N - 1;
	}
	if (wins == 0) {
		if (K == 0) return 0;
		return 2 * K - 1;
	}
	if (S[0] == 'L') losing_streaks[0] = 1e8;
	if (S[N - 1] == 'L') losing_streaks.back() = 1e8;
	sort(losing_streaks.begin(), losing_streaks.end());
	wins += K;
	for (int ls : losing_streaks) {
		if (ls > K) break;
		K -= ls;
		winning_streaks_cnt--;
	}
	return 2 * wins - winning_streaks_cnt;
}

long long compute_points(const string& elements, int l, int r)
{
	long long points = 0;
	for (size_t i = l; i <= r; i++)
	{
		if (elements[i] == 'W')
		{
			if (i > 0)
				points += elements[i - 1] == 'W' ? 2 : 1;
			else
				points++;
		}
	}
	return points;
}

long long my_solution(string elements, int k)
{
	int n = elements.size();
	int l = 0, r = 0;
	int no_losses = 0;
	int max_increase = -1;
	int max_l = -1, max_r = -1;
	while (r != n)
	{
		if (elements[r] == 'W')
		{
			int original_points = compute_points(elements, l, r);
			int new_points = (r - l) * 2 + 1;
			if (new_points - original_points > max_increase)
			{
				max_r = r;
				max_l = l;
				max_increase = new_points - original_points;
			}
		}
		else
		{
			no_losses++;

			if (no_losses <= k)
			{
				int original_points = compute_points(elements, l, r);
				int new_points = (r - l)*2 + 1;
				if (new_points-original_points > max_increase)
				{
					max_r = r;
					max_l = l;
					max_increase = new_points - original_points;
				}
			}
			if (no_losses == k + 1 && r > 0)
			{
				int original_points = compute_points(elements, l, r-1);
				int new_points = (r - l - 1)*2 + 1;
				if (new_points - original_points > max_increase)
				{
					max_r = r - 1;
					max_l = l;
					max_increase = new_points - original_points;
				}
			}

			while (no_losses > k)
			{
				if (elements[l++] == 'L')
					no_losses--;
			}
		}
		r++;
	}
	if (no_losses <= k)
	{
		r--;
		int original_points = compute_points(elements, l, r);
		int new_points = (r - l) * 2 + 1;
		if (new_points - original_points > max_increase)
		{
			max_r = r;
			max_l = l;
			max_increase = new_points - original_points;
		}
	}

	if (max_l >= 0 && max_r >= 0)
	{
		for (size_t i = max_l; i <= max_r; i++)
		{
			if (elements[i] == 'L')
				elements[i] = 'W';
		}
	}
	
	return compute_points(elements,0,elements.size()-1);
}

int counter = 0;

void try_all_permutations(int count, int no_wins)
{
	for (int k = 0; k <= count; k++)
	{
		string a(count, 'L');
		for (size_t i = 0; i < no_wins; i++)
			a[i] = 'W';
		sort(a.begin(), a.end());
		do
		{
			counter++;
			long long correct = solve(a, k);
			long long test = my_solution(a, k);
			if (correct != test)
			{
				my_solution(a, k);
				cout << "AAAAAAAAAAAAAAAAAAAAAAAAA";
			}
		} while (next_permutation(a.begin(), a.end()));
	}
}

int main()
{
	/*
	ios::sync_with_stdio(false);
	int t; cin >> t;
	for (size_t test_no = 0; test_no < t; test_no++)
	{
		int n; cin >> n; int k; cin >> k;
		cin.ignore();
		string elements; getline(cin, elements);
		
	}*/
	for (int i = 1; i < 10; i++)
	{
		for (int w = 0; w <= i; w++)
		{
			try_all_permutations(i, w);
		}
	}
	return 0;
}