#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<int>& v);
	int sum(int l, int r);
	void increment(int position);
private:
	vector<int> tree;
	int element_cnt;
};

vector<int> count_inversions(const vector<int>& elements)
{
	int max_el = *max_element(elements.begin(), elements.end());
	vector<int> elements_count(max_el + 1);
	SegmentTree tree(elements_count);
	int n = elements.size();

	vector<int> solution(n);
	for (int i = 0; i < n; i++)
	{
		int element_value = elements[i];
		int inversions = tree.sum(element_value + 1, max_el + 1);
		tree.increment(element_value);
		solution[i] = inversions;
	}
	tree = SegmentTree(elements_count);
	for (int i = n - 1; i >= 0; i--)
	{
		int element_value = elements[i];
		int inversions = tree.sum(0, element_value);
		tree.increment(element_value);
		solution[i] += inversions;
	}
	return solution;
}

bool bruteforce_recursive(set<pair<vector<int>,vector<bool>>>& visited_states, vector<int> current_state, vector<bool> current_orientations)
{
	if (is_sorted(current_state.begin(),current_state.end()))
	{
		if (find(current_orientations.begin(), current_orientations.end(), 1) == current_orientations.end())
			return true;
	}
	bool b = false;
	for (int i = 0; i < current_state.size()-1; i++)
	{
		if (visited_states.find({ current_state,current_orientations }) == visited_states.end())
		{
			visited_states.insert({ current_state,current_orientations });
			b |= bruteforce_recursive(visited_states, current_state, current_orientations);
		}
		swap(current_state[i], current_state[i + 1]);
		current_orientations[i] = !current_orientations[i];
		current_orientations[i + 1] = !current_orientations[i + 1];

		if (visited_states.find({ current_state,current_orientations }) == visited_states.end())
		{
			visited_states.insert({ current_state,current_orientations });
			b |= bruteforce_recursive(visited_states, current_state, current_orientations);
		}
		swap(current_state[i], current_state[i + 1]);
		current_orientations[i] = !current_orientations[i];
		current_orientations[i + 1] = !current_orientations[i + 1];
	}
	return b;
}

bool bruteforce(vector<int> elements)
{
	set<pair<vector<int>, vector<bool>>> visited_states;
	vector<bool> orientations(elements.size(), 0);
	return bruteforce_recursive(visited_states, elements, orientations);
}

bool solve(const vector<int>& elements)
{
	int n = elements.size();
	auto inversion_count = count_inversions(elements);
	vector<vector<bool>> element_inv_parity(*max_element(elements.begin(), elements.end()) + 1, vector<bool>());
	for (int i = 0; i < n; i++)
	{
		int element_val = elements[i];
		element_inv_parity[element_val].push_back(inversion_count[i] % 2);
	}
	bool possible = true;
	for (int i = 0; i < element_inv_parity.size() && possible; i++)
	{
		for (int j = 1; j < element_inv_parity[i].size(); j++)
		{
			if (element_inv_parity[i][j-1] == 0 && element_inv_parity[i][j] == 0)
			{
				element_inv_parity[i][j] = 1;
				element_inv_parity[i][j - 1] = 1;
			}
		}

		int block_size = 0;
		if (!element_inv_parity[i].empty() && element_inv_parity[i][0] == 1)
			block_size = 1;
		for (int j = 1; j < element_inv_parity[i].size() && possible; j++)
		{
			if (element_inv_parity[i][j] == 1)
			{
				if (element_inv_parity[i][j - 1] == 1)
					block_size++;
				else
					block_size = 1;
			}
			else
			{
				if (block_size % 2 == 1)
				{
					possible = false;
				}
				block_size = 0;
			}
		}
		if (block_size % 2 == 1)
		{
			possible = false;
		}
	}
	return possible;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];
		cout << (bruteforce(elements) ?  "YES\n" : "NO\n");
	}

	return 0;
}

SegmentTree::SegmentTree(const vector<int>& v)
{
	element_cnt = v.size();
	tree = vector<int>(element_cnt * 2);
	copy(v.begin(), v.end(), tree.begin() + element_cnt);
	for (int i = element_cnt- 1; i > 0; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

int SegmentTree::sum(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	int result = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			result += tree[l++];
		}
		if (r % 2 == 1)
		{
			result += tree[--r];
		}
		l /= 2;
		r /= 2;
	}
	return result;
}

void SegmentTree::increment(int position)
{
	position += element_cnt;
	tree[position]++;
	for (int i = position/2; i > 0; i/=2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}
