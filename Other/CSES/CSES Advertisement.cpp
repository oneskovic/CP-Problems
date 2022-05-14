#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
typedef long long ll;

struct stack_element
{
	int left_span;
	ll height;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	stack<stack_element> s;
	ll solution = 0;
	for (int i = 0; i < n+1; i++)
	{
		ll element;
		if (i == n)
			element = 0;
		else
			cin >> element;

		int right_span = 0;
		while (!s.empty() && s.top().height > element)
		{
			ll area = (ll)(s.top().left_span + right_span) * s.top().height;
			solution = max(solution, area);

			right_span += s.top().left_span;
			s.pop();
		}
		s.push({ right_span + 1,element });
	}
	cout << solution << "\n";
	return 0;
}