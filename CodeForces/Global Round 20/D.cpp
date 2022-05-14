#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

vector<ll> p1_pows(2 * 1e5 + 1);
vector<ll> p2_pows(2 * 1e5 + 1);

const ll m1 = 1e9 + 9;
const ll m2 = 1e9 + 123;
const ll p1 = 31;
const ll p2 = 53;

class StringHash
{
public:
	StringHash();
	void add_to_front(int val);
	void add_to_back(int val);
	ll h1, h2;
	int current_len;
};

bool operator == (const StringHash& lhs, const StringHash& rhs)
{
	return lhs.h1 == rhs.h1 && lhs.h2 == rhs.h2;
}

vector<int> rotate(vector<int> v, int l, int r)
{
	vector<int> result = v;
	for (int i = l; i < r; i++)
	{
		result[i] = v[i + 1];
	}
	result[r] = v[l];
	
	return result;
}

pair<vector<int>, vector<int>> generate_test(int n, int max_val=5)
{
	vector<int> start_vec(n);
	vector<vector<int>> position_map(max_val+ 1, vector<int>());
	for (int i = 0; i < n; i++)
	{
		start_vec[i] = rand() % max_val + 1;
		position_map[start_vec[i]].push_back(i);
	}
	vector<int> target_vec = start_vec;

	for (int i = 0; i < 500; i++)
	{
		int val_to_swap = rand() % max_val + 1;
		if (position_map[val_to_swap].size() > 1)
		{
			int cnt = position_map[val_to_swap].size();
			int i1 = rand() % cnt;
			int i2 = rand() % cnt;
			while (i2 == i1)
				i2 = rand() % cnt;
			int l = position_map[val_to_swap][i1], r = position_map[val_to_swap][i2];
			if (r < l)
			{
				swap(l, r);
				swap(i1, i2);
			}
			target_vec = rotate(target_vec, l, r);
			position_map = vector<vector<int>>(max_val+1, vector<int>());
			for (int j = 0; j < target_vec.size(); j++)
				position_map[target_vec[j]].push_back(j);
		}
	}
	return { start_vec,target_vec };
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	p1_pows[0] = 1;
	p2_pows[0] = 1;
	for (int i = 1; i <= 2*1e5; i++)
	{
		p1_pows[i] = p1_pows[i - 1] * p1;
		p1_pows[i] %= m1;

		p2_pows[i] = p2_pows[i - 1] * p2;
		p2_pows[i] %= m2;
	}

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> s(n), target(n);

		for (int i = 0; i < n; i++)
			cin >> s[i];

		for (int i = 0; i < n; i++)
			cin >> target[i];
		/*int n = 6;
		vector<int> s(n), target(n);
		auto t = generate_test(n);
		s = t.first;
		target = t.second;*/


		bool ok = 1;
		auto s_hash = StringHash();
		auto target_hash = StringHash();
		bool parity_add_to_back = 0;
		for (int i = 0; i < n; i++)
		{
			if (s[i] == target[i] && ok)
			{
				continue;
			}
			else if (s[i] != target[i] && ok)
			{
				int cnt_same = 0;
				int j = i;
				for (j; j < n && target[j] == target[i]; j++)
				{
					cnt_same++;
					s_hash.add_to_back(s[j]);
					target_hash.add_to_back(target[j]);
				}
				i = j - 1;
				parity_add_to_back = cnt_same % 2;
				ok = false;
			}
			else
			{
				s_hash.add_to_back(s[i]);
				if (target_hash.current_len % 2 == parity_add_to_back)
					target_hash.add_to_back(target[i]);
				else
					target_hash.add_to_front(target[i]);
				ok = (s_hash == target_hash);
				if (ok)
				{
					s_hash = StringHash();
					target_hash = StringHash();
				}
			}
		}


		/*if (ok)
			cout << "yes\n";
		else
			cout << "no\n";
			*/
		if (ok)
		{
			cout << "ok\n";
		}
		else
		{
			cout << "wa\n";
			for (int i: s)
				cout << i << " ";
			cout << "\n";
			for (int i : target)
				cout << i << " ";
			cout << "\n";
		}
	}

	return 0;
}

StringHash::StringHash()
{
	h1 = 0;
	h2 = 0;
	current_len = 0;
}

void StringHash::add_to_front(int val)
{
	h1 = (h1 * p1 + val) % m1;
	h2 = (h2 * p2 + val) % m2;
	current_len++;
}

void StringHash::add_to_back(int val)
{
	h1 += val * p1_pows[current_len];
	h1 %= m1;

	h2 += val * p2_pows[current_len];
	h2 %= m2;
	current_len++;
}
