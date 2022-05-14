#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& v);
	ll sum_query(int l, int r);
	void update(int pos, ll new_value);
private:
	vector<ll> tree;
	int element_cnt;
};

class SegmentArray
{
public:
	SegmentArray(const vector<ll>& v);
	ll sum_query(int l, int r);
	void update(int pos, ll new_value);
private:
	vector<ll> elements;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand(time(0));

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int query_cnt = rand() % 1000;
		int n = rand() % 1000 + 1;
		vector<ll> v(n);
		for (int i = 0; i < n; i++)
			v[i] = rand() % 2000 - 1000;
		
		auto tree = SegmentTree(v);
		auto arr = SegmentArray(v);

		for (int q = 0; q < query_cnt; q++)
		{
			if (rand()%2)
			{
				int pos = rand() % n;
				int new_val = rand() % 2000 - 1000;
				tree.update(pos, new_val);
				arr.update(pos, new_val);
			}
			else
			{
				int l = rand() % n;
				int r = rand() % n;
				if (l > r)
					swap(l, r);
				r++;
				ll sol1 = tree.sum_query(l, r);
				ll sol2 = arr.sum_query(l, r);
				if (sol1 != sol2)
				{
					cout << "wa\n";
				}
			}
		}
	}

	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	tree = vector<ll>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt-1; i >= 0; i--)
	{
		tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
}

ll SegmentTree::sum_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	ll sum = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			sum += tree[l++];
		}
		if(r % 2 == 1)
		{
			sum += tree[--r];
		}
		l /= 2;
		r /= 2;
	}
	return sum;
}

void SegmentTree::update(int pos, ll new_value)
{
	pos += element_cnt;
	tree[pos] = new_value;
	pos /= 2;
	while (pos > 0)
	{
		tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
		pos /= 2;
	}
}

SegmentArray::SegmentArray(const vector<ll>& v)
{
	elements = v;
}

ll SegmentArray::sum_query(int l, int r)
{
	ll sum = 0;
	for (int i = l; i < r; i++)
		sum += elements[i];
	
	return sum;
}

void SegmentArray::update(int pos, ll new_value)
{
	elements[pos] = new_value;
}
