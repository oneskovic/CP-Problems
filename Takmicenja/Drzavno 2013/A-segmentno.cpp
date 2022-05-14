#include <algorithm>
#include <iostream>
#include <limits.h>
#include <numeric>
#include <vector>
#include <chrono>
#include <string>
#include <set>
#include <map>
using namespace std;
typedef long long ll;

struct SegmentTreeElement
{
	bool val;
	int row, col;
};
bool operator < (const SegmentTreeElement& lhs, const SegmentTreeElement& rhs)
{
	return lhs.val < rhs.val;
}

bool operator > (const SegmentTreeElement& lhs, const SegmentTreeElement& rhs)
{
	return lhs.val > rhs.val;
}

bool operator >= (const SegmentTreeElement& lhs, const SegmentTreeElement& rhs)
{
	return lhs.val >= rhs.val;
}

class SegmentTree
{
public:
	SegmentTree(const vector<bool>& elements, int row = -1);
	SegmentTree(vector<SegmentTreeElement>& elements);
	SegmentTreeElement max_query(int l, int r);
	void update(int pos, int new_value);
	void update(int pos, SegmentTreeElement new_value);
	vector<SegmentTreeElement> tree;
	int element_cnt;
};

class SegmentTree2d
{
public:
	SegmentTree2d(vector<vector<bool>>& elements);
	SegmentTreeElement max_query(int row_top_left, int col_top_left, int w, int h);
	void update(int row, int col, int new_value);
	vector<SegmentTree> tree2d_rows, tree2d_cols;
	int tree_cnt;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n, m; cin >> n >> m;
	vector<vector<bool>> mat = vector<vector<bool>>(n, vector<bool>(m));
	SegmentTree2d tree = SegmentTree2d(mat);
	for (int i = 0; i < n; i++)
	{
		string s; cin >> s;
		for (int j = 0; j < m; j++)
		{
			if (s[j] == '1')
			{
				tree.update(i, j, 1);
			}
		}
	}
	int query_cnt; cin >> query_cnt;
	for (int i = 0; i < query_cnt; i++)
	{
		int type, row, col;
		cin >> type >> row >> col;
		row--; col--;
		if (type == 1)
		{
			tree.update(row, col, 1);
		}
		else if (type == 2)
		{
			tree.update(row, col, 0);
		}
		else
		{
			int l = -1, r = n;
			if (tree.max_query(row-r,col-r,2*r+1,2*r+1).val == 0)
			{
				cout << "-1\n";
				continue;
			}
			while (r-l > 1)
			{
				int d = (l + r) / 2;
				if (tree.max_query(row - d, col - d, 2 * d + 1, 2 * d + 1).val != 0)
					r = d;
				else
					l = d;
			}
			auto sol = tree.max_query(row - r, col - r, 2 * r + 1, 2 * r + 1);
			cout << sol.row+1 << " " << sol.col+1 << "\n";

		}
	}
	
	return 0;
}

SegmentTree::SegmentTree(const vector<bool>& elements, int row)
{
	element_cnt = elements.size();
	tree = vector<SegmentTreeElement>(2 * element_cnt);
	for (int i = element_cnt; i < 2*element_cnt; i++)
	{
		tree[i] = { elements[i - element_cnt],row, i - element_cnt };
	}
	for (int i = element_cnt-1; i > 0; i--)
	{
		if (tree[i*2] > tree[i*2+1])
		{
			tree[i] = tree[i * 2];
		}
		else
		{
			tree[i] = tree[i * 2 + 1];
		}
	}
}
SegmentTree::SegmentTree(vector<SegmentTreeElement>& elements)
{
	element_cnt = elements.size();
	tree = vector<SegmentTreeElement>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
	{
		if (tree[i * 2] > tree[i * 2 + 1])
		{
			tree[i] = tree[i * 2];
		}
		else
		{
			tree[i] = tree[i * 2 + 1];
		}
	}
}

SegmentTreeElement SegmentTree::max_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	SegmentTreeElement max_el = { 0,-1,-1 };
	while (l < r)
	{
		if (l % 2 == 1)
		{
			if (tree[l] >= max_el)
			{
				max_el = tree[l];
			}
			l++;
		}
		if (r % 2 == 1)
		{
			if (tree[--r] >= max_el)
			{
				max_el = tree[r];
			}
		}
		l /= 2;
		r /= 2;
	}
	return max_el;
}

void SegmentTree::update(int pos, int new_value)
{
	pos += element_cnt;
	tree[pos].val = new_value;
	for (int i = pos/2; i > 0; i/=2)
	{
		if (tree[i * 2] > tree[i * 2 + 1])
		{
			tree[i] = tree[i * 2];
		}
		else
		{
			tree[i] = tree[i * 2 + 1];
		}
	}
}

void SegmentTree::update(int pos, SegmentTreeElement new_value)
{
	pos += element_cnt;
	tree[pos] = new_value;
	for (int i = pos / 2; i > 0; i /= 2)
	{
		if (tree[i * 2] > tree[i * 2 + 1])
		{
			tree[i] = tree[i * 2];
		}
		else
		{
			tree[i] = tree[i * 2 + 1];
		}
	}
}

SegmentTree2d::SegmentTree2d(vector<vector<bool>>& elements)
{
	int n = elements.size();
	int m = elements[0].size();
	tree_cnt = n;
	tree2d_rows = vector<SegmentTree>();
	for (int i = 0; i < n; i++)
	{
		tree2d_rows.push_back(SegmentTree(elements[i], i));
	}
	
	tree2d_cols = vector<SegmentTree>();
	for (int i = 0; i < 2*m; i++)
	{
		vector<SegmentTreeElement> col_tree(n);
		for (int row = 0; row < n; row++)
		{
			col_tree[row] = tree2d_rows[row].tree[i];
		}
		tree2d_cols.push_back(SegmentTree(col_tree));
	}
}

SegmentTreeElement SegmentTree2d::max_query(int row_top_left, int col_top_left, int w, int h)
{
	int n = tree2d_rows.size();
	int m = tree2d_cols.size() / 2;
	int l = max(col_top_left,0);
	int r = min(col_top_left + w, m);
	int u = max(row_top_left, 0);
	int d = min(row_top_left + h, n);
	l += tree2d_rows[0].element_cnt;
	r += tree2d_rows[0].element_cnt;
	SegmentTreeElement max_el = { 0,-1,-1 };
	while (l < r)
	{
		if (l%2 == 1)
		{
			auto el = tree2d_cols[l].max_query(u, d);
			if (el >= max_el)
			{
				max_el = el;
			}
			l++;
		}
		if (r%2 == 1)
		{
			r--;
			auto el = tree2d_cols[r].max_query(u, d);
			if (el >= max_el)
			{
				max_el = el;
			}
		}
		l /= 2;
		r /= 2;
	}
	return max_el;
}

void SegmentTree2d::update(int row, int col, int new_value)
{
	tree2d_rows[row].update(col, new_value);
	int pos = col + tree2d_rows[row].element_cnt;
	for (int i = pos; i > 0; i/=2)
	{
		tree2d_cols[i].update(row, tree2d_rows[row].tree[i]);
	}
}
