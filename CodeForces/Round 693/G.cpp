#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int node_count, edge_count;
		cin >> node_count >> edge_count;
		vector<vector<int>> graph(node_count + 1);
		for (size_t i = 0; i < edge_count; i++)
		{
			int source, target;
			cin >> source >> target;
			graph[source].push_back(target);
		}

		// Perform a bfs starting from the "capital" node
		vector<bool> visited(node_count + 1);
		
		// distance_to_capital is a vector of vectors of size 2 (basically pairs) where
		// distance_to_capital[i][0] is the distance if no back-edge has been used
		// and distance_to_capital[i][1] is the distance if a single back-edge has been used
		vector<vector<int>> distance_to_capital(node_count + 1, vector<int>(2));

		// node_queue is a queue of tuples where the first element is the node index
		// the second element is the distance to the capital
		// and the third element is the parent
		queue<vector<int>> node_queue; node_queue.push({ 1,0 });
		
		while (!node_queue.empty())
		{
			int current_node = node_queue.front()[0];
			int current_distance = node_queue.front()[1];
			int distance_by_back_edge = INT_MAX;
			node_queue.pop();
			visited[current_node] = true;

			for (int neighbor: graph[current_node])
			{
				if (visited[neighbor])
				{
					distance_by_back_edge = min(distance_by_back_edge, distance_to_capital[neighbor][0] + 1);
				}
				else
					node_queue.push({ neighbor, current_distance + 1, current_node });
			}

			distance_to_capital[current_node][0] = current_distance;
			distance_to_capital[current_node][1] = distance_by_back_edge;
		}
		cout << " ";
	}
	return 0;
}