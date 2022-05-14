#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <chrono>

using namespace std;
typedef long long ll;

size_t hash_vector(const vector<int>& vec)
{
	size_t seed = vec.size();
	for (auto& i : vec) {
		seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

void generate_new_vector(vector<int>& v)
{
	map<int, int> number_counts;
	for (int i = 0; i < v.size(); i++)
		number_counts[v[i]]++;
	
	for (int i = 0; i < v.size(); i++)
		v[i] = number_counts[v[i]];
}

int check(vector<int> v, int step, int pos)
{
	for (int i = 0; i < step; i++)
	{
		generate_new_vector(v);
	}
	return v[pos];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand(time(0));
	
	int test_cnt; cin >> test_cnt;
	int max_cycle_len = 0;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> v(n);
		for (int i = 0; i < n; i++)
		{
			cin >> v[i];
		}

		vector<int> appeared_vector_hashes;
		vector<vector<int>> appeared_vectors;

		int cycle_start = -1;
		while (true)
		{
			auto current_hash = hash_vector(v);
			bool appeared = false;
			for (int i = 0; i < appeared_vector_hashes.size(); i++)
			{
				if (appeared_vector_hashes[i] == current_hash)
				{
					cycle_start = i;
					appeared = 1;
					break;
				}
			}
			if (!appeared)
			{
				appeared_vector_hashes.push_back(current_hash);
				appeared_vectors.push_back(v);
				generate_new_vector(v);
			}
			else
			{
				break;
			}
		}

		int query_cnt; cin >> query_cnt;
		for (int i = 0; i < query_cnt; i++)
		{
			int pos, step; cin >> pos >> step;
			pos--;
			if (step < appeared_vectors.size())
			{
				cout << appeared_vectors[step][pos] << "\n";
			}
			else
			{
				step -= cycle_start;
				int cycle_len = appeared_vectors.size() - cycle_start;
				int solution = appeared_vectors[cycle_start + step % cycle_len][pos];
				cout << solution << "\n";
			}
		}
	}


	return 0;
}