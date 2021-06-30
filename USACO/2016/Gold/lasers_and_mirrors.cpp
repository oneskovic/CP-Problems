#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct point
{
	int x, y;
};

bool operator==(const point& lhs, const point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=(const point& lhs, const point& rhs)
{
	return !(lhs == rhs);
}

istream& operator>>(istream& stream, point& p)
{
	stream >> p.x >> p.y;
	return stream;
}

int main()
{
	freopen("lasers.in", "r", stdin);
	freopen("lasers.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	point laser, barn;
	cin >> laser >> barn;
	vector<vector<point>> vertical_components, horizontal_components;
	map<int, int> x_coordinate_id, y_coordinate_id;


	int current_id_x = 0, current_id_y = 0;
	for (int i = 0; i < n+2; i++)
	{
		point p;
		if (i == 0)
			p = laser;
		else if (i == 1)
			p = barn;
		else
			cin >> p;

		if (x_coordinate_id.find(p.x) == x_coordinate_id.end())
		{
			x_coordinate_id[p.x] = current_id_x++;
			vertical_components.push_back(vector<point>());
		}
		vertical_components[x_coordinate_id[p.x]].push_back(p);

		if (y_coordinate_id.find(p.y) == y_coordinate_id.end())
		{
			y_coordinate_id[p.y] = current_id_y++;
			horizontal_components.push_back(vector<point>());
		}
		horizontal_components[y_coordinate_id[p.y]].push_back(p);
	}
	

	map<int, bool> vertical_component_visited, horizontal_component_visited;
	queue<pair<int,point>> to_visit;
	to_visit.push({ 0,laser });
	
	int dist_to_barn = -1;
	while (!to_visit.empty())
	{
		point p = to_visit.front().second;
		int distance = to_visit.front().first;
		if (p == barn)
		{
			dist_to_barn = distance-1;
			break;
		}

		to_visit.pop();
		int horizontal_comp_id = y_coordinate_id[p.y];
		if (!horizontal_component_visited[horizontal_comp_id])
		{
			for (point q: horizontal_components[horizontal_comp_id])
			{
				if (p != q)
				{
					to_visit.push({ distance + 1,q });
				}
			}
			horizontal_component_visited[horizontal_comp_id] = 1;
		}

		int vertical_comp_id = x_coordinate_id[p.x];
		if (!vertical_component_visited[vertical_comp_id])
		{
			for (point q : vertical_components[vertical_comp_id])
			{
				if (p != q)
				{
					to_visit.push({ distance + 1,q });
				}
			}
			vertical_component_visited[vertical_comp_id] = 1;
		}
	}
	cout << dist_to_barn << endl;

	return 0;
}