#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <chrono>
using namespace std;
#define ll long long
/// <summary>
/// A simple sum query segment tree
/// </summary>
class SegmentTree {
public:
	SegmentTree(const vector<int>& elements);
	void Modify(int position, int new_value);
	ll Query(int l, int r);
private:
	int element_count;
	vector<int> tree;
};

struct query_element
{
	int element;
	bool is_query;
	int l, r;
	int query_index;
	int element_position;
	bool operator < (const query_element& other) const
	{
		if (element == other.element)
		{
			if (is_query && !other.is_query)
				return true;
			else
				return false;
		}
		return element > other.element;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand(time(0));
	int n; cin >> n;
	vector<int> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	//auto elements = rand_vector(n, 100000);


	// We will, for each element remember the next position it appears (or MAX_INT if it doesnt appear again)
	// Eg. for elements [1,2,3,2,1] remember [4,3,MAX_INT,MAX_INT,MAX_INT]
	unordered_map<int, int> previous_position;
	vector<ll> next_position(n);
	// Start from the right and fill the next_position vector
	for (int i = n-1; i >= 0; i--)
	{
		int current_element = elements[i];
		if (previous_position.find(current_element) != previous_position.end())
			next_position[i] = previous_position[current_element];
		else
			next_position[i] = INT_MAX;
		previous_position[current_element] = i;
	}

	// Next, given a query for the number of unique elements in range [l,r] we can see that
	// a certain element i is unique in the range [l,r] if and only if the next_position[i] < r
	// so the query becomes a query for the number of elements larger than r in range [l,r]
	// This can be solved offline using a segment/fenwick tree
	// First combine all queries and next_position elements into a single vector (query_elements)
	// Sort according to the element value (in non-increasing order) - if the element is a query compare to r
	// The point of this is to process a query only once the larger elements have been added
	int no_queries;cin >> no_queries;
	vector<query_element> query_elements; query_elements.reserve(n + no_queries);
	// Add queries
	for (size_t i = 0; i < no_queries; i++)
	{
		query_element q;
		q.is_query = true;
		cin >> q.l >> q.r;
		q.l--; q.r--;
		q.element = q.r;
		q.query_index = i;
		query_elements.push_back(q);
	}

	// Add elements
	for (size_t i = 0; i < n; i++)
	{
		query_element q;
		q.is_query = false;
		q.element = next_position[i];
		q.element_position = i;
		query_elements.push_back(q);
	}
	sort(query_elements.begin(), query_elements.end());
	
	// Next, construct a simple sum segment tree, if a position in available_elements[i] == 1 then the
	// element has been added to position i, to get the number of elements added to range [l,r] query for sum
	vector<int> available_elements(n);
	int i = 0; 
	// First process a lot of non-query query_elements (to avoid O(log n) for update) - seems to speed up the code somewhat
	while (!query_elements[i].is_query)
		available_elements[query_elements[i++].element_position] = 1;
	
	auto available_elements_tree = SegmentTree(available_elements);
	vector<ll> resolved_queries(no_queries);
	
	for (; i < query_elements.size(); i++)
	{
		query_element current_element = query_elements[i];
		if (current_element.is_query)
		{
			resolved_queries[current_element.query_index] = 
				available_elements_tree.Query(current_element.l, current_element.r+1);
		}
		else
			available_elements_tree.Modify(current_element.element_position, 1);
	}
	
	for (auto resolved_query: resolved_queries)
		cout << resolved_query <<"\n";

	return 0;
}

SegmentTree::SegmentTree(const vector<int>& elements)
{
	element_count = elements.size();
	tree = vector<int>(element_count * 2);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);
	for (int i = element_count - 1; i > 0; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void SegmentTree::Modify(int position, int new_value)
{
	position += element_count;
	tree[position] = new_value;
	for (int i = position / 2; i > 0; i--)
		tree[i] = tree[i*2] + tree[i*2 + 1];
}

ll SegmentTree::Query(int l, int r)
{
	l += element_count; r += element_count;
	ll sum = 0;
	while (l < r)
	{
		if (l % 2 == 1)
			sum += tree[l++];
		if (r % 2 == 1)
			sum += tree[--r];

		l /= 2; r /= 2;
	}
	return sum;
}
