#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

template <typename T>
class SegmentTree
{
public:
	SegmentTree(const vector<T>& elements,const function<T(T, T)>& associative_function);
	pair<T,int> query(int l, int r);
	void modify_element(int position, T new_value);
private:
	function<T(T, T)> associative_function;
	int element_count;
	vector<T> value_tree;
	vector<int> position_tree;
};

int translate_index(const vector<ll>& sorted_array, ll index)
{
	auto lb = lower_bound(sorted_array.begin(), sorted_array.end(), index);
	return lb - sorted_array.begin();
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<tuple<ll, ll, int>> position_height(n);
	for (size_t i = 0; i < n; i++)
	{
		ll x, h;
		cin >> x >> h;
		position_height[i] = { x,h,i };
	}
	sort(position_height.begin(), position_height.end());
	vector<ll> sorted_positions(n);
	for (int i = 0; i < n; i++)
		sorted_positions[i] = get<0>(position_height[i]);

	auto domino_count_tree = SegmentTree<ll>(vector<ll>(n), plus<ll>());
	auto temp = vector<ll>(n);
	for (int i = 0; i < n; i++)
	{
		temp[i] = get<0>(position_height[i]) + get<1>(position_height[i]);
	}
	function<ll(ll, ll)> greater_element = [](ll lhs, ll rhs) {
		return lhs > rhs ? lhs : rhs;
	};
	auto max_right_reach = SegmentTree<ll>(temp, greater_element);

	vector<ll> solution(n);

	for (int i = n-1; i >= 0; i--)
	{
		int right = translate_index(sorted_positions, get<0>(position_height[i]) + get<1>(position_height[i]));
		domino_count_tree.modify_element(i, 1);
		int max_right = i;
		ll sol = 1;
		if (i != right)
		{
			max_right = max_right_reach.query(i, right).second;
			ll domino_cnt = domino_count_tree.query(i, right).first;
			sol = domino_cnt + solution[get<2>(position_height[max_right])];
			if (max_right != i)
			{
				ll overlap = domino_count_tree.query(max_right, right).first;
				sol -= overlap;
			}
		}
		solution[get<2>(position_height[i])] = sol;
	}
	
	for (ll i : solution)
		cout << i << " ";
	return 0;
}

template<typename T>
SegmentTree<T>::SegmentTree(const vector<T>& elements, const function<T(T, T)>& associative_function)
{
	element_count = elements.size();
	this->associative_function = associative_function;
	value_tree = vector<T>(element_count * 2);
	position_tree = vector<int>(element_count * 2);

	copy(elements.begin(), elements.end(), value_tree.begin() + element_count);
	iota(position_tree.begin() + element_count, position_tree.end(), 0);
	for (int i = element_count - 1; i > 0; i--)
	{
		value_tree[i] = associative_function(value_tree[i * 2], value_tree[i * 2 + 1]);
		if (value_tree[i] == value_tree[i * 2])
			position_tree[i] = position_tree[i * 2];
		else
			position_tree[i] = position_tree[i * 2 + 1];
	}
}

template<typename T>
pair<T,int> SegmentTree<T>::query(int l, int r)
{
	l += element_count;
	r += element_count;

	T result;
	bool result_defined = false;
	int position = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			result = (result_defined ? associative_function(value_tree[l], result) : value_tree[l]);
			result_defined = true;
			if (result == value_tree[l])
			{
				position = position_tree[l];
			}
			l++;
		}
		if (r % 2 == 1)
		{
			r--;
			result = (result_defined ? associative_function(value_tree[r], result) : value_tree[r]);
			result_defined = true;
			if (result == value_tree[r])
			{
				position = position_tree[r];
			}
		}
		l /= 2;
		r /= 2;
	}
	return { result,position };
}

template<typename T>
void SegmentTree<T>::modify_element(int position, T new_value)
{
	position += element_count;
	value_tree[position] = new_value;
	for (int i = position / 2; i > 0; i /= 2)
	{
		value_tree[i] = associative_function(value_tree[i * 2], value_tree[i * 2 + 1]);
		if (value_tree[i] == value_tree[i * 2])
			position_tree[i] = position_tree[i * 2];
		else
			position_tree[i] = position_tree[i * 2 + 1];
	}
}
