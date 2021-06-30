#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
typedef long long ll;
 
class Tree
{
public:
	Tree(vector<int> enabled);
	ll solution();
	void update(int pos, int enabled_value);
private:
	vector<int> fix_enabled_values(vector<int> enabled_values);
	vector<int> layer_size;
	vector<ll> values;
	vector<int> enabled;
};
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
 
	int k; cin >> k;
	string s; cin >> s;
	vector<int> enabled(s.size());
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '0')
			enabled[i] = 0;
		else if (s[i] == '1')
			enabled[i] = 1;
		else
			enabled[i] = 2;
	}
	Tree t = Tree(enabled);
	int query_count; cin >> query_count;
	for (int i = 0; i < query_count; i++)
	{
		int pos; cin >> pos;
		char c; cin >> c;
		int enabled_type = 2;
		if (c == '0')
			enabled_type = 0;
		else if (c == '1')
			enabled_type = 1;
 
		t.update(pos, enabled_type);
		cout << t.solution() << "\n";
	}
 
	return 0;
}
 
Tree::Tree(vector<int> enabled)
{
	int n = enabled.size()+1;
	for (int x = n; x > 0; x/=2)
		layer_size.push_back(x);
	
	enabled = fix_enabled_values(enabled);
	this->enabled = vector<int>(2*n);
	copy(enabled.begin(), enabled.end(), this->enabled.begin() + 1);
	values = vector<ll>(2*n,1);
	for (int i = n - 1; i > 0; i--)
	{
		if (this->enabled[i] == 0)
			values[i] = values[2 * i];
 
		else if (this->enabled[i] == 1)
			values[i] = values[2 * i + 1];
 
		else
			values[i] = values[2 * i] + values[2 * i + 1];
	}
}
 
ll Tree::solution()
{
	return values[1];
}
 
void Tree::update(int pos, int enabled_value)
{
	int base_pos = layer_size.back();
	for (int i = 1; i < layer_size.size(); i++)
	{
		if (pos - layer_size[i] <= 0)
		{
			base_pos = layer_size[i];
			break;
		}
		else
			pos -= layer_size[i];
	}
	pos--;
	enabled[base_pos + pos] = enabled_value;
 
	for (int i = base_pos + pos; i > 0; i/=2)
	{
		if (enabled[i] == 0)
			values[i] = values[2 * i];
 
		else if (enabled[i] == 1)
			values[i] = values[2 * i + 1];
 
		else
			values[i] = values[2 * i] + values[2 * i + 1];
	}
}
 
vector<int> Tree::fix_enabled_values(vector<int> enabled_values)
{
	int j = 0;
	for (int i = 1; i < layer_size.size(); i++)
	{
		reverse(enabled_values.begin() + j, enabled_values.begin() + j + layer_size[i]);
		j += layer_size[i];
	}
	reverse(enabled_values.begin(), enabled_values.end());
	return enabled_values;
}