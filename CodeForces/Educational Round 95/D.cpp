#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
#define ll long long

/// <summary>
/// Checks if the given point has a point to the right
/// </summary>
bool has_right_point(const set<ll>& points, set<ll>::iterator point)
{
	return (++point) != points.end();
}

bool has_left_point(const set<ll>& points, set<ll>::iterator point)
{
	return point != points.begin();
}

void erase_first(multiset<ll>& m, ll element)
{
	auto it = m.find(element);
	m.erase(it);
}

/// <summary>
/// Modifies the given sets when a new point is added
/// </summary>
void query_add(set<ll>& points, multiset<ll>& distances, ll point)
{
	auto it = points.insert(point).first;
	if (has_left_point(points, it))
	{
		auto left_point = it; left_point--;
		ll distance = (*it) - (*left_point);
		distances.insert(distance);
	}
	if (has_right_point(points, it))
	{
		auto right_point = it; right_point++;
		ll distance = (*right_point) - (*it);
		distances.insert(distance);
	}
	if (has_left_point(points, it) && has_right_point(points, it))
	{
		auto left_point = it; left_point--;
		auto right_point = it; right_point++;
		auto distance = (*right_point) - (*left_point);
		erase_first(distances, distance);
	}
}

void query_remove(set<ll>& points, multiset<ll>& distances, ll point)
{
	auto it = points.find(point);
	if (has_left_point(points, it))
	{
		auto left_point = it; left_point--;
		ll distance = (*it) - (*left_point);
		erase_first(distances, distance);
	}
	if (has_right_point(points, it))
	{
		auto right_point = it; right_point++;
		ll distance = (*right_point) - (*it);
		erase_first(distances, distance);
	}
	if (has_left_point(points, it) && has_right_point(points, it))
	{
		auto left_point = it; left_point--;
		auto right_point = it; right_point++;
		auto distance = (*right_point) - (*left_point);
		distances.insert(distance);
	}
	points.erase(it);
}

ll cleanup_cost(const set<ll>& points, const multiset<ll>& distances)
{
	if (points.size() <= 2)
	{
		return 0;
	}
	auto min_point = points.begin();
	auto max_point = --points.end();
	// Distance between min and max points
	ll distance_ends = (*max_point) - (*min_point);
	ll max_distance = *(--distances.end());
	ll solution = distance_ends - max_distance;
	return solution;
}

int main()
{
	ios::sync_with_stdio(false);
	int n, query_count;
	cin >> n >> query_count;
	set<ll> points;
	multiset<ll> distances;
	for (size_t i = 0; i < n; i++)
	{
		ll point; cin >> point;
		query_add(points, distances, point);
	}
	cout << cleanup_cost(points, distances) << "\n";

	for (size_t i = 0; i < query_count; i++)
	{
		int query_type; cin >> query_type;
		ll point; cin >> point;

		if (query_type == 0)
			query_remove(points, distances, point);
		else
			query_add(points, distances, point);
		

		cout << cleanup_cost(points,distances) << "\n";
	}
	return 0;
}