#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, instruction_count;
	cin >> n >> instruction_count;
	vector<int> instructions(n + 1);
	for (size_t i = 0; i < instruction_count; i++)
	{
		int l, r; cin >> l >> r;
		l--; r--;
		instructions[l] += 1;
		instructions[r+1] -= 1;
	}
	vector<int> result(n);
	int to_add = 0;
	for (size_t i = 0; i < n; i++)
	{
		to_add += instructions[i];
		result[i] = to_add;
	}
	nth_element(result.begin(), result.begin() + n / 2, result.end());
	cout << result[n / 2];

	return 0;
}