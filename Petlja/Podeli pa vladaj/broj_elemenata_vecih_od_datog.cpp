#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

class SegmentTree
{
private:
	vector<ll> tree;
	size_t element_count;
public:
	SegmentTree(const vector<ll>& elements)
	{
		element_count = elements.size();
		tree = vector<ll>(2 * element_count);
		copy(elements.begin(), elements.end(), tree.begin() + element_count);
		for (int i = element_count-1; i >= 1; i--)
			tree[i] = tree[i * 2] + tree[i * 2 + 1];
	}
	void IncrementElement(int position, ll ammount = 1)
	{
		position += element_count;
		tree[position] += ammount;
		for (int i = position / 2; i >= 1; i /= 2)
			tree[i] = tree[i * 2] + tree[i * 2 + 1];
	}
	/// <summary>
	/// Sum in range [l,r)
	/// </summary>
	ll SumRange(int l, int r)
	{
		l += element_count;
		r += element_count;
		ll sum = 0;
		while (l < r)
		{
			if (l % 2 == 1)
				sum += tree[l++];
			if (r % 2 == 1)
				sum += tree[--r];
			
			l /= 2;
			r /= 2;
		}
		return sum;
	}

};

struct query
{
	int element_at_position;
	int position;
	int k;
	int query_position;
};

bool operator > (const query& lhs, const query& rhs)
{
	return lhs.element_at_position > rhs.element_at_position;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<pair<ll,int>> elements_original_pos(n);
	for (size_t i = 0; i < n; i++)
	{
		cin >> elements_original_pos[i].first;
		elements_original_pos[i].second = i;
	}

	int q; cin >> q;
	vector<query> queries(q);
	vector<bool> solutions(q);
	for (size_t i = 0; i < q; i++)
	{
		int day; 
		cin >> day;
		queries[i].element_at_position = elements_original_pos[day].first;
		queries[i].position = day;
		cin  >> queries[i].k;
		queries[i].query_position = i;
	}

	sort(elements_original_pos.begin(), elements_original_pos.end(), greater<pair<ll, int>>());
	sort(queries.begin(), queries.end(), greater<query>());

	auto tree = SegmentTree(vector<ll>(n, 0));
	ll previous_element = elements_original_pos[0].first;

	int query_index = 0;
	for (size_t i = 0; i < n; i++)
	{
		ll element = elements_original_pos[i].first;
		int original_position = elements_original_pos[i].second;
		while (query_index < q && queries[query_index].element_at_position > element)
		{
			ll sum = tree.SumRange(queries[query_index].position+1, n);
			solutions[queries[query_index].query_position] = (sum <= queries[query_index].k);
			query_index++;
		}
		tree.IncrementElement(original_position);
	}
	while (query_index < q)
	{
		ll sum = tree.SumRange(queries[query_index].position + 1, n);
		solutions[queries[query_index].query_position] = (sum <= queries[query_index].k);
		query_index++;
	}
	
	for (size_t i = 0; i < q; i++)
	{
		cout << (solutions[i] ? "da" : "ne");
		cout << "\n";
	}

	return 0;
}