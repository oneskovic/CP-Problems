#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

class DSU
{
public:
	DSU(int element_count);
	int find_set(int element);
	/// <summary>
	/// Joins the sets the given two elements belong to
	/// </summary>
	void join_sets(int element1, int element2);
private:
	void join(int set1, int set2);
	vector<int> representative, rank;
};

bool is_valid_cell(int row, int col, int col_count, int row_count)
{
	if (row < 0 || col < 0 || row >= row_count || col >= col_count )
	{
		return false;
	}
	return true;
}
vector<int> get_neighbors(int cell_index, int col_count, int row_count)
{
	int row = cell_index / col_count;
	int col = cell_index % col_count;
	vector<int> drow = { 0,0,-1,1 };
	vector<int> dcol = { -1,1,0,0 };
	vector<int> neighbors;
	for (size_t i = 0; i < drow.size(); i++)
	{
		int new_row = row + drow[i];
		int new_col = col + dcol[i];
		if (is_valid_cell(new_row, new_col, col_count, row_count))
		{
			neighbors.push_back(new_row * col_count + new_col);
		}
	}
	return neighbors;
}

bool should_add_neighbor(int caller_node, int neighbor, int col_count, int row_count, const vector<vector<bool>>& is_cell_empty, DSU& dsu)
{
	auto neighbor_neighbors = get_neighbors(neighbor, col_count, row_count);
	vector<int> neighbor_neighbors_sets;
	int empty_count = 0;
	for (auto nn: neighbor_neighbors)
	{
		if (is_cell_empty[nn/col_count][nn%col_count])
			empty_count++;
		neighbor_neighbors_sets.push_back(dsu.find_set(nn));
	}

	for (int i = 0; i < neighbor_neighbors_sets.size(); i++)
	{
		for (int j = i+1; j < neighbor_neighbors_sets.size(); j++)
		{
			if (neighbor_neighbors_sets[i] == neighbor_neighbors_sets[j])
			{
				return false;
			}
		}
	}

	return empty_count > 0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int row_count, col_count; cin >> row_count >> col_count;
		vector<vector<bool>> is_cell_empty(row_count, vector<bool>(col_count));
		queue<int> bfs_queue;
		vector<bool> visited(row_count * col_count);
		for (size_t i = 0; i < row_count; i++)
		{
			for (size_t j = 0; j < col_count; j++)
			{
				char c; cin >> c;
				if (c == 'X')
				{
					is_cell_empty[i][j] = 1;
					bfs_queue.push(i * col_count + j);
					visited[i * col_count + j] = 1;
				}
			}
		}

		DSU dsu(row_count * col_count);
		while (!bfs_queue.empty())
		{
			int current_cell_index = bfs_queue.front();
			bfs_queue.pop();
			auto neighbors = get_neighbors(current_cell_index, col_count, row_count);
			for (int neighbor_index: neighbors)
			{
				if (!visited[neighbor_index])
				{
					if (should_add_neighbor(current_cell_index, neighbor_index, col_count, row_count, is_cell_empty, dsu))
					{
						for (int nn: get_neighbors(neighbor_index,col_count,row_count))
						{
							if (is_cell_empty[nn/col_count][nn%col_count])
							{
								dsu.join_sets(nn, neighbor_index);
							}
						}
						is_cell_empty[neighbor_index / col_count][neighbor_index % col_count] = 1;
					}
					bfs_queue.push(neighbor_index);
					visited[neighbor_index] = 1;
				}
			}
		}

		for (int i = 0; i < row_count; i++)
		{
			for (int j = 0; j < col_count; j++)
			{
				cout << (is_cell_empty[i][j] ? "X" : ".");
			}
			cout << "\n";
		}
	}

	return 0;
}

DSU::DSU(int element_count)
{
	representative = vector<int>(element_count, -1);
	rank = vector<int>(element_count, 1);
	iota(representative.begin(), representative.end(), 0);
}

int DSU::find_set(int element)
{
	if (representative[element] == element)
		return element;
	
	return representative[element] = find_set(representative[element]);
}

void DSU::join_sets(int element1, int element2)
{
	join(find_set(element1), find_set(element2));
}

void DSU::join(int representative1, int representative2)
{
	if (rank[representative1] > rank[representative2])
		swap(representative1, representative2);

	// rank[representative1] <= rank[representative2]
	if (rank[representative1] == rank[representative2])
		rank[representative1]++;
	
	representative[representative1] = representative2;
}
