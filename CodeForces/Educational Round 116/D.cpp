#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int counter = 0;
void solve(int n, int s, int max_val, vector<int>& solution)
{
	if (n == 0)
	{
		if (s == 0)
		{
			for (int i: solution)
				cout << i << " ";
			cout << "\n";
			counter++;
		}
	}
	else
	{
		for (int i = 0; i <= max_val; i++)
		{
			if (s - i >= 0)
			{
				solution[n - 1] = i;
				solve(n - 1, s - i, max_val, solution);
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	vector<int> solution(4);
	solve(4, 3, 3, solution);
	cout << counter;
	return 0;
}