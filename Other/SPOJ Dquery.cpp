#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<int>& elements);
	void update(int position, int new_value);
	int sum_query(int l, int r);
private:
	int element_cnt;
	vector<int> tree;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];
	int query_cnt; cin >> query_cnt;
	vector<pair<int, int>> queries(query_cnt);
	vector<pair<int, int>> right_end_query(query_cnt);
	for (int i = 0; i < query_cnt; i++)
	{
		cin >> queries[i].first >> queries[i].second;
		queries[i].first--; queries[i].second--;
		right_end_query[i] = { queries[i].second, i };
	}

	vector<int> rightmost_position(*max_element(elements.begin(), elements.end()) + 1, -1);
	auto tree = SegmentTree(vector<int>(n));
	sort(right_end_query.begin(), right_end_query.end());
	vector<int> solution(query_cnt);

	int elements_index = 0;
	for (int queries_index = 0; queries_index < query_cnt; queries_index++)
	{
		int current_right = right_end_query[queries_index].first;
		while (elements_index <= current_right)
		{
			int current_element = elements[elements_index];
			int prev_pos = rightmost_position[current_element];
			if (prev_pos != -1)
				tree.update(prev_pos, 0);
			tree.update(elements_index, 1);
			rightmost_position[current_element] = elements_index;
			elements_index++;
		}
		int idx = right_end_query[queries_index].second;
		int current_left = queries[idx].first;
		solution[idx] = tree.sum_query(current_left, current_right + 1);
	}
	for (int i : solution)
	{
		cout << i << "\n";
	}

	return 0;
}

SegmentTree::SegmentTree(const vector<int>& elements)
{
	element_cnt = elements.size();
	tree = vector<int>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

void SegmentTree::update(int position, int new_value)
{
	position += element_cnt;
	tree[position] = new_value;
	for (int i = position / 2; i > 0; i /= 2)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

int SegmentTree::sum_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	int sum = 0;
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
