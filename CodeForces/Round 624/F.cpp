#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>
using namespace std;
#define ll long long

class MergeSortTree
{
private:
	vector<vector<pair<ll,ll>>> element_tree;
	vector<vector<ll>> prefix_sum_tree;
	size_t element_count;

	static bool compare_pair_by_second(const pair<ll, ll>& lhs, const pair<ll, ll>& rhs)
	{
		return lhs.second < rhs.second;
	}
public:
	MergeSortTree(const vector<pair<ll,ll>>& elements)
	{
		element_count = elements.size();
		element_tree = vector<vector<pair<ll, ll>>>(2 * element_count);
		prefix_sum_tree = vector<vector<ll>>(2 * element_count);
		for (size_t i = 0; i < element_count; i++)
		{
			element_tree[i + element_count] = { elements[i] };
			prefix_sum_tree[i + element_count] = { elements[i].first };
		}
		for (int i = element_count-1; i >= 1; i--)
		{
			element_tree[i] = vector<pair<ll,ll>>(element_tree[i * 2].size() + element_tree[i * 2 + 1].size());
			merge(element_tree[i * 2].begin(), element_tree[i * 2].end(),
				element_tree[i * 2 + 1].begin(), element_tree[i * 2 + 1].end(),
				element_tree[i].begin(), &MergeSortTree::compare_pair_by_second);
			
			prefix_sum_tree[i] = vector<ll>(element_tree[i].size());
			prefix_sum_tree[i][0] = element_tree[i][0].first;
			for (size_t j = 1; j < element_tree[i].size(); j++)
				prefix_sum_tree[i][j] = prefix_sum_tree[i][j - 1] + element_tree[i][j].first;
		}
	}
	pair<int, ll> Query(int l, int r, ll x)
	{
		l += element_count;
		r += element_count;
		int count = 0;
		ll sum = 0;
		while (l < r)
		{
			if (l % 2 == 1)
			{
				auto it = upper_bound(element_tree[l].begin(), element_tree[l].end(), pair<ll, ll>(0, x), &MergeSortTree::compare_pair_by_second);
				count += it - element_tree[l].begin();

				int i = it - element_tree[l].begin();
				if (i > 0)
					sum += prefix_sum_tree[l][--i];
				l++;
			}
			if (r % 2 == 1)
			{
				r--;
				auto it = upper_bound(element_tree[r].begin(), element_tree[r].end(), pair<ll, ll>(0, x), &MergeSortTree::compare_pair_by_second);
				count += it - element_tree[r].begin();

				int i = it - element_tree[r].begin();
				if (i > 0)
					sum += prefix_sum_tree[r][--i];
			}
			l /= 2;
			r /= 2;
		}
		return { count,sum };
	}
};

ll solve(vector<pair<ll, ll>> position_velocity)
{
	sort(position_velocity.begin(), position_velocity.end());
	auto mst = MergeSortTree(position_velocity);
	ll solution = 0;
	for (size_t i = 0; i < position_velocity.size(); i++)
	{
		auto query = mst.Query(0, i, position_velocity[i].second);
		ll sum_of_paths = query.second; // Sum of paths of all points with velocity smaller than the current velocity	
		ll count_smaller_velocity = query.first;
		solution += count_smaller_velocity * position_velocity[i].first - sum_of_paths;
	}
	return solution;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n; cin >> n;
	vector<pair<ll, ll>> position_velocity(n);
	for (size_t i = 0; i < n; i++)
		cin >> position_velocity[i].first;
	for (size_t i = 0; i < n; i++)
		cin >> position_velocity[i].second;
	cout << solve(position_velocity) << "\n";
	return 0;
}