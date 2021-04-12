#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
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

	int current_row = row;
	int current_col = col;

	int col_count = keyboard[0].size();
	for (int i = 0; i < drow.size(); i++)
	{
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
		current_row = row;
		current_col = col;
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

void debug_print(const vector<vector<int>>& dp, int pos)
{
	int n = 5, m = 5;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int index = i * m + j;
			cout << dp[index][pos] << " ";
		}
		cout << "\n";
	}
}

ll solve(const vector<int>& str_to_find, const vector<vector<cell>>& graph, const vector<vector<int>>& k)
{
	vector<vector<ll>> shortest_path_from_to(graph.size(), vector<ll>());
	for (int i = 0; i < graph.size(); i++)
		shortest_path_from_to[i] = shortest_paths({ i,-1 }, graph);

	vector<vector<int>> indices_with_chr (27, vector<int>());
	vector<int> keyboard(k.size() * k[0].size());
	for (int row = 0; row < k.size(); row++)
	{
		for (int col = 0; col < k[0].size(); col++)
		{
			int index = row * k[0].size() + col;
			keyboard[index] = k[row][col];
			indices_with_chr[k[row][col]].push_back(index);
		}
	}

	vector<vector<ll>> dp(graph.size(), vector<ll>(str_to_find.size(), -1));

	for (int i = 0; i < dp.size(); i++)
	{
		dp[i][0] = shortest_path_from_to[0][i];
	}
	//debug_print(dp, 0);
	
	for (int pos_in_str = 1; pos_in_str < str_to_find.size(); pos_in_str++)
	{
		for (int i = 0; i < graph.size(); i++)
		{
			if (dp[i][pos_in_str-1] == -1)
			{
				continue;
			}
			if (keyboard[i] == str_to_find[pos_in_str])
			{
				if (dp[i][pos_in_str-1] == -1)
					dp[i][pos_in_str] = -1;
				else
					dp[i][pos_in_str] = dp[i][pos_in_str - 1];
			}
			else
			{
				ll min_over_all_neighbors = LLONG_MAX;
				for (int neighbor: indices_with_chr[str_to_find[pos_in_str]])
				{
					if (dp[neighbor][pos_in_str - 1] > -1)
					{
						min_over_all_neighbors = min(min_over_all_neighbors, dp[neighbor][pos_in_str - 1] + shortest_path_from_to[neighbor][i]);
					}
				}
				if (min_over_all_neighbors == LLONG_MAX)
					dp[i][pos_in_str] = -1;
				else
					dp[i][pos_in_str] = min_over_all_neighbors;
			}
		}
		//debug_print(dp, pos_in_str);
	}

	ll solution = INT_MAX;
	for (int i = 0; i < graph.size(); i++)
	{
		if (keyboard[i] == 26 && dp[i].back() > -1)
		{
			solution = min(solution, dp[i].back());
		}
	}
	return solution;
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

	string str_to_type; cin >> str_to_type;
	auto vec_to_type = str_to_vector_int("A"+str_to_type+"*");
	cout << solve(vec_to_type, graph, keyboard) + str_to_type.size()+1;
	return 0;
}