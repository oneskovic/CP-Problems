#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <random>
#include <chrono>
using namespace std;
#define ll long long

struct cell
{
	int index, value;
};

int char_to_int(char c)
{
	if (c == '*')
		return 26;
	else
		return c - 'A';
}
vector<int> str_to_vector_int(string s)
{
	vector<int> v(s.size());
	for (size_t i = 0; i < s.size(); i++)
		v[i] = char_to_int(s[i]);
	return v;
}

bool is_valid_cell(int row, int col, int row_count, int col_count)
{
	if (row < 0 || col < 0 || row >= row_count || col >= col_count)
	{
		return false;
	}
	return true;
}

vector<cell> get_neighbors(int row, int col, const vector<vector<int>>& keyboard)
{
	vector<int> drow = { 0,0,1,-1 };
	vector<int> dcol = { 1,-1,0,0 };
	vector<cell> neighbors;

	int col_count = keyboard[0].size();
	for (int i = 0; i < drow.size(); i++)
	{
		int current_row = row;
		int current_col = col;
		int new_row = current_row + drow[i];
		int new_col = current_col + dcol[i];
		while (is_valid_cell(new_row, new_col, keyboard.size(), keyboard[0].size()) && keyboard[new_row][new_col] == keyboard[current_row][current_col])
		{
			current_row = new_row;
			current_col = new_col;
			new_row += drow[i];
			new_col += dcol[i];
		}
		if (is_valid_cell(new_row, new_col, keyboard.size(), keyboard[0].size()))
		{
			int index = new_row * col_count + new_col;
			neighbors.push_back({ index, keyboard[new_row][new_col] });
		}
		else
		{
			int index = current_row * col_count + current_col;
			neighbors.push_back({index,keyboard[current_row][current_col]});
		}
	}
	return neighbors;
}

vector<ll> shortest_paths(cell source_node, const vector<vector<cell>>& graph)
{
	queue<pair<cell, ll>> bfs_queue;
	vector<ll> computed_path(graph.size(), -1);
	bfs_queue.push({ source_node, 0 });
	computed_path[source_node.index] = 0;
	while (!bfs_queue.empty())
	{
		auto current_cell = bfs_queue.front().first;
		ll dist = bfs_queue.front().second;
		bfs_queue.pop();

		for (auto neighbor : graph[current_cell.index])
		{
			if (computed_path[neighbor.index] == -1)
			{
				bfs_queue.push({ neighbor, dist + 1 });
				computed_path[neighbor.index] = dist + 1;
			}
		}
	}
	return computed_path;
}

ll dijkstra(int source, int dest, const map<int,vector<int>>& graph, const map<int,vector<ll>>& weights)
{
	map<int, ll> computed_paths;
	priority_queue <pair<ll, int>, vector<pair<ll,int>>, greater<pair<ll,int>> > distance_node;
	computed_paths[source] = 0;
	distance_node.emplace(0, source);

	while (!distance_node.empty())
	{
		ll current_dist = distance_node.top().first;
		int current_node = distance_node.top().second;
		distance_node.pop();
		if (current_node == dest)
			break;
			
		if (graph.find(current_node) == graph.end() || computed_paths[current_node] < current_dist)
			continue;
		
		for (int i = 0; i < graph.at(current_node).size(); i++)
		{
			int neighbor = graph.at(current_node).at(i);
			ll w = weights.at(current_node).at(i);
			if (computed_paths.find(neighbor) == computed_paths.end() || current_dist + w < computed_paths[neighbor])
			{
				computed_paths[neighbor] = current_dist + w;
				distance_node.emplace(current_dist + w, neighbor);
			}
		}
	}
	if (computed_paths.find(dest) == computed_paths.end())
	{
		return LLONG_MAX;
	}
	return computed_paths[dest];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int row_count, col_count;
	cin >> row_count >> col_count;
	vector<vector<int>> keyboard(row_count, vector<int>(col_count));
	for (int row = 0; row < row_count; row++)
	{
		string s; cin >> s;
		keyboard[row] = str_to_vector_int(s);
	}

	int max_value = 26;
	vector<vector<cell>> graph(row_count*col_count, vector<cell>());
	for (int row = 0; row < row_count; row++)
	{
		for (int col = 0; col < col_count; col++)
		{
			int index = row * col_count + col;
			auto neighbors = get_neighbors(row, col, keyboard);
			for (auto n : neighbors)
			{
				graph[index].push_back(n);
			}
		}
	}

	vector<vector<int>> indices_with_chr(27, vector<int>());
	for (int row = 0; row < keyboard.size(); row++)
	{
		for (int col = 0; col < keyboard[0].size(); col++)
		{
			int index = row * keyboard[0].size() + col;
			indices_with_chr[keyboard[row][col]].push_back(index);
		}
	}

	vector<vector<ll>> shortest_path_from_to(graph.size(), vector<ll>());
	for (int i = 0; i < graph.size(); i++)
		shortest_path_from_to[i] = shortest_paths({ i,-1 }, graph);

	string str_to_type; cin >> str_to_type;
	auto vec_to_type = str_to_vector_int(str_to_type+"*");
	map<int,vector<int>> new_graph;
	map<int,vector<ll>> new_weights;
	for (size_t i = 0; i < vec_to_type.size() - 1; i++)
	{
		for (int current_node: indices_with_chr[vec_to_type[i]])
		{
			for (int next_node: indices_with_chr[vec_to_type[i+1]])
			{
				if (shortest_path_from_to[current_node][next_node] < LLONG_MAX)
				{
					new_graph[current_node+i*graph.size()].push_back(next_node+(i+1)*graph.size());
					new_weights[current_node+i*graph.size()].push_back(shortest_path_from_to[current_node][next_node]);
				}
			}
		}
	}
	for (int next_node: indices_with_chr[vec_to_type[0]])
	{
		new_graph[0].push_back(next_node);
		new_weights[0].push_back(shortest_path_from_to[0][next_node]);
	}

	ll solution = LLONG_MAX;
	for (int possible_dest: indices_with_chr[26])
	{
		int dest_index = graph.size() * (vec_to_type.size() - 1) + possible_dest;
		solution = min(solution, dijkstra(0, dest_index, new_graph, new_weights));
	}
	cout << solution + str_to_type.size() + 1;
	return 0;
}