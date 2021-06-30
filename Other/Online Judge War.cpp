#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <map>
using namespace std;

class DSU
{
public:
	DSU(int max_n);
	int find_set(int element);
	int join_sets(int element1, int element2);
private:
	vector<int> representative, size;
};

DSU dsu = DSU(1);
vector<int> enemy_set;

void set_friends(int element1, int element2)
{
	int set1 = dsu.find_set(element1), set2 = dsu.find_set(element2);
	if (enemy_set[set1] == set2)
	{
		cout << "-1\n";
	}
	else
	{
		int result_set = dsu.join_sets(set1, set2);
		int enemy1 = enemy_set[set1], enemy2 = enemy_set[set2];
		int result_enemy = dsu.join_sets(enemy1, enemy2);
		enemy_set[result_set] = result_enemy;
		if (result_enemy != -1)
			enemy_set[result_enemy] = result_set;
	}
}
void set_enemies(int element1, int element2)
{
	int set1 = dsu.find_set(element1), set2 = dsu.find_set(element2);
	if (set1 == set2)
	{
		cout << "-1\n";
	}
	else
	{
		int enemy1 = enemy_set[set1], enemy2 = enemy_set[set2];
		int res1 = dsu.join_sets(enemy1, set2);
		int res2 = dsu.join_sets(enemy2, set1);
		enemy_set[res1] = res2;
		enemy_set[res2] = res1;
	}
}
void are_friends(int element1, int element2)
{
	int set1 = dsu.find_set(element1), set2 = dsu.find_set(element2);
	if (set1 == set2)
		cout << "1\n";
	else
		cout << "0\n";
}
void are_enemies(int element1, int element2)
{
	int set1 = dsu.find_set(element1), set2 = dsu.find_set(element2);
	if (enemy_set[set1] == set2)
		cout << "1\n";
	else
		cout << "0\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	dsu = DSU(n);
	enemy_set = vector<int>(n, -1);
	while (true)
	{
		int op_code, arg1, arg2;
		cin >> op_code >> arg1 >> arg2;
		if (op_code == 0)
			break;
		else if (op_code == 1)
			set_friends(arg1, arg2);
		else if (op_code == 2)
			set_enemies(arg1, arg2);
		else if (op_code == 3)
			are_friends(arg1, arg2);
		else
			are_enemies(arg1, arg2);
	}
	return 0;
}

DSU::DSU(int max_n)
{
	representative = vector<int>(max_n);
	iota(representative.begin(), representative.end(), 0);
	size = vector<int>(max_n, 1);
}

int DSU::find_set(int element)
{
	if (representative[element] == element)
		return element;
	
	return representative[element] = find_set(representative[element]);
}

int DSU::join_sets(int element1, int element2)
{
	if (element1 == -1)
		return element2;
	if (element2 == -1)
		return element1;
	

	int set1 = find_set(element1), set2 = find_set(element2);
	if (set1 != set2)
	{
		if (size[set1] > size[set2])
			swap(set1, set2);
		// size[set1] <= size[set2]
		representative[set1] = set2;
		size[set2] += size[set1];
	}
	return set2;
}
