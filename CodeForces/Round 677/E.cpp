#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
#include <unordered_set>
#include <bitset>
using namespace std;
#define ll long long

ll hash_dance(const vector<int>& dance)
{
	ll m = 1e9 + 9;
	ll p = 31;
	int min_pos = min_element(dance.begin(), dance.end()) - dance.begin();
	int current_pos = min_pos;
	ll hash = 0;
	for (int i = 0; i < dance.size(); i++)
	{
		hash += dance.at(current_pos) * pow(p, i);
		hash %= m;
		current_pos++;
		current_pos %= dance.size();
	}
	return hash;
}

ll hash_vector(const vector<int>& vec)
{
	ll hash = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		hash ^= vec[i] + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	}

	return hash;
}

ll number_of_unique_dances(int no_people)
{
	unordered_set<ll> hashes;
	vector<int> dance(no_people);
	iota(dance.begin(), dance.end(), 1);
	do
	{
		hashes.insert(hash_dance(dance));
	} while (next_permutation(dance.begin(),dance.end()));
	return hashes.size();
}

vector<ll> no_unique_dances = { 0,1,1,2,6,24,120,720,5040,40320,362880 };

unordered_set<ll> valid_choices;

void invert_vector(vector<int>& v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i] == 0)
			v[i] = 1;
		else
			v[i] = 0;
	}
}

void generate(int position, int remaining, vector<int>& choices)
{
	if (position == choices.size())
	{
		invert_vector(choices);
		bool already_found_inverted = (valid_choices.find(hash_vector(choices)) != valid_choices.end());
		invert_vector(choices);
		if (remaining == 0 && !already_found_inverted)
		{
			valid_choices.insert(hash_vector(choices));
		}
		return;
	}
	if (remaining > 0)
	{
		choices[position] = 1;
		generate(position + 1, remaining - 1, choices);
		choices[position] = 0;
	}
	generate(position + 1, remaining, choices);
}

int main()
{
	ios::sync_with_stdio(false);
	int n; cin >> n;
	vector<int> choices(n);
	generate(0, n/2, choices);
	ll solution = valid_choices.size() * no_unique_dances[n / 2] * no_unique_dances[n / 2];
	cout << solution << "\n";
	return 0;
}