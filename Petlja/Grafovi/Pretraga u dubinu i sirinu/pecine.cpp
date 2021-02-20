#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
using namespace std;

struct stack_frame
{
	int node, height;
};

int main()
{
	int start_height; cin >> start_height;
	int node_count; cin >> node_count;
	vector<vector<pair<int,int>>> tree(node_count, vector<pair<int,int>>());
	for (size_t i = 0; i < node_count-1; i++)
	{
		int a, b, height_diff; cin >> a >> b >> height_diff;
		tree[a].push_back({ b,height_diff });
	}

	int min_height = start_height;
	stack<stack_frame> s;
	s.push({ 0,start_height });
	while (!s.empty())
	{
		stack_frame current = s.top();
		s.pop();
		int current_height = current.height;
		min_height = min(current_height, min_height);
		for (auto p: tree[current.node])
		{
			int neighbor = p.first;
			int height_diff = p.second;
			s.push({ neighbor,current_height + height_diff });
		}
	}
	cout << min_height << "\n";
	return 0;
}