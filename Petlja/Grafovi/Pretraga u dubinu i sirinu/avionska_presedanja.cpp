#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

int main()
{
	unordered_map<string, vector<string>> graph;
	int edge_count; cin >> edge_count;
	for (size_t i = 0; i < edge_count; i++)
	{
		string source, dest;
		cin >> source >> dest;
		graph[source].push_back(dest);
	}

	int query_count; cin >> query_count;
	for (size_t i = 0; i < query_count; i++)
	{
		unordered_map<string, bool> visited;
		string start_node, end_node;
		cin >> start_node >> end_node;
		int solution = -1;
		queue<pair<string,int>> bfs_queue;

		for (string neighbor : graph[start_node])
		{
			if (!visited[neighbor])
			{
				visited[neighbor] = true;
				bfs_queue.emplace(neighbor, 0 + 1);
			}
		}
		while (!bfs_queue.empty())
		{
			auto current = bfs_queue.front();
			bfs_queue.pop();
			string current_node = current.first;
			int current_distance = current.second;

			visited[current_node] = true;
			if (current_node == end_node)
			{
				solution = current_distance;
				break;
			}
			for (string neighbor: graph[current_node])
			{
				if (!visited[neighbor])
				{
					visited[neighbor] = true;
					bfs_queue.emplace(neighbor, current_distance + 1);
				}
			}
		}
		if (solution == -1)
		{
			cout << "ne\n";
		}
		else
		{
			cout << solution << "\n";
		}
	}

	return 0;
}