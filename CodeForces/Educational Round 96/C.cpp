#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int t; cin >> t;
	for (size_t test_no = 0; test_no < t; test_no++)
	{
		int n; cin >> n;
		cout << "2\n";
		stack<int> numbers;
		for (int i = 1; i <= n; i++)
			numbers.push(i);
		
		while (numbers.size() > 1)
		{
			int num1 = numbers.top();
			numbers.pop();
			int num2 = numbers.top();
			numbers.pop();
			cout << num1 << " " << num2 << "\n";
			numbers.push(ceil((1.0 * num1 + num2) / 2));
		}
	}
	return 0;
}