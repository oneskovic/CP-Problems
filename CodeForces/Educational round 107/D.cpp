#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <numeric>
#include <set>
#include <list>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	// A complete graph must contain an eulerian cycle
	// To solve the given problem, an eulerian cycle can be
	// constructed and repeated as many times as needed

	int string_len, alphabet_size; 
	cin >> string_len >> alphabet_size;
	set<int> all_letters;
	for (int i = 0; i < alphabet_size; i++)
		all_letters.insert(i);

	vector<set<int>> graph(alphabet_size, all_letters);
	
	// Find an eulerian cycle
	list<int> euler_path = { 0 };
	int used_edges = 0;
	while (used_edges < alphabet_size*alphabet_size)
	{
		for (auto it = euler_path.begin(); it != euler_path.end() && used_edges < alphabet_size*alphabet_size; it++)
		{
			int vertex = *it;
			list<int> current_path;
			while (graph[vertex].size() > 0)
			{
				int prev_vertex = vertex;
				vertex = *graph[vertex].begin();
				graph[prev_vertex].erase(vertex);

				current_path.push_back(vertex);
				used_edges++;
			}
			auto temp_it = it;
			euler_path.splice(++temp_it, current_path);
		}
	}
	euler_path.pop_back(); // This is an eulerian cycle so it will be of from 0 -> ... -> 0

	string s; s.reserve(string_len);
	int inserted_chars = 0;
	while (inserted_chars < string_len)
	{
		for (auto it = euler_path.begin(); it != euler_path.end() && inserted_chars < string_len; it++)
		{
			s.push_back('a'+*it);
			inserted_chars++;
		}
	}
	cout << s;
	return 0;
}