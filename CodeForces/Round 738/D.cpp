include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;

class DSU
{
public:
	DSU(int max_element);
	void join_sets(int element1, int element2);
	int find_set(int element);
private:
	vector<int> representative;
	vector<int> rank;
};

bool can_add(DSU& dsu, int a, int b)
{
	if (dsu.find_set(a) != dsu.find_set(b))
	{
		return true;
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);


	int n; cin >> n;
	int m1, m2; cin >> m1 >> m2;
	DSU dsu1(n), dsu2(n);
	for (int i = 0; i < m1; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		dsu1.join_sets(a, b);
	}
	for (int i = 0; i < m2; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		dsu2.join_sets(a, b);
	}

	int cnt = 0;
	vector<int> s1, s2;
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			if (can_add(dsu1,i,j) && can_add(dsu2,i,j))
			{
				dsu1.join_sets(i, j);
				dsu2.join_sets(i, j);
				cnt++;
				s1.push_back(i + 1);
				s2.push_back(j + 1);
			}
		}
	}
	cout << cnt << "\n";
	for (int i = 0; i < cnt; i++)
	{
		cout << s1[i] << " " << s2[i] << "\n";
	}

	return 0;
}


DSU::DSU(int element_cnt)
{
	representative = vector<int>(element_cnt);
	rank = vector<int>(element_cnt, 1);
	iota(representative.begin(), representative.end(), 0);
}

void DSU::join_sets(int element1, int element2)
{
	int set1 = find_set(element1);
	int set2 = find_set(element2);
	if (rank[set1] > rank[set2])
		swap(set1, set2);

	// rank[set1] <= rank[set2]
	representative[set1] = set2;
	if (rank[set1] == rank[set2])
		rank[set1]++;
}

int DSU::find_set(int element)
{
	if (representative[element] == element)
		return element;
	return representative[element] = find_set(representative[element]);
}
