#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <chrono>

using namespace std;
#define ll long long

bool solve(vector<ll> differences)
{
	int n = differences.size() / 2;
	sort(differences.begin(), differences.end(), greater<ll>());
	bool possible = true;
	for (size_t i = 0; i < 2*n; i+=2)
	{
		if (differences[i] != differences[i+1])
		{
			possible = false;
		}
	}

	ll sum_to_subtract = 0;
	ll divisor = 2 * n;
	vector<ll> solution_vec; solution_vec.reserve(n);
	for (size_t i = 0; i < 2*n && possible; i+=2)
	{
		if ((differences[i] - sum_to_subtract) % divisor > 0)
		{
			possible = false;
			break;
		}
		ll solution = (differences[i] - sum_to_subtract) / divisor;
		if (solution <= 0)
		{
			possible = false;
			break;
		}
		solution_vec.push_back(solution);
		sum_to_subtract += 2 * solution;
		divisor -= 2;
	}
	sort(solution_vec.begin(), solution_vec.end());
	auto it = unique(solution_vec.begin(), solution_vec.end());
	if (possible && it == solution_vec.end())
		return true;
	else
		return false;
}

vector<ll> generate()
{
	srand(time(0));
	int n = rand() % 10 + 1;
	vector<ll> numbers(2 * n);
	set<ll> s;
	for (size_t i = 0; i < n; i++)
	{
		int num = rand() % 20 + 1;
		while (s.find(num) != s.end())
		{
			num = rand() % 20 + 1;
		}
		numbers[i] = num;
		s.insert(num);
	}
	for (size_t i = n; i < 2*n; i++)
	{
		numbers[i] = -numbers[i-n];
	}

	vector<ll> diffs(2 * n);
	for (size_t i = 0; i < 2*n; i++)
	{
		for (size_t j = 0; j < 2*n; j++)
		{
			diffs[i] += abs(numbers[i] - numbers[j]);
		}
	}
	return diffs;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<ll> differences(2 * n);
		for (size_t i = 0; i < 2*n; i++)
			cin>>differences[i];
		bool solution = solve(differences);
		if (solution)
		{
			cout << "YES\n";
		}
		else
			cout << "NO\n";
	}
	return 0;
}