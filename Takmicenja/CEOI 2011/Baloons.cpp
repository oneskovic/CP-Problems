#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
using namespace std;
typedef long long ll;

struct stack_element
{
	double x, radius;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;

	stack<stack_element> s;
	for (int i = 0; i < n; i++)
	{
		double new_x, max_radius; cin >> new_x >> max_radius;
		while (!s.empty())
		{
			double prev_radius = s.top().radius;
			double prev_x = s.top().x;
			double dx = (prev_x - new_x);
			double radius_to_intersect = (dx*dx / (2.0 * prev_radius)) / 2.0;
			max_radius = min(max_radius, radius_to_intersect);
			if (max_radius >= prev_radius)
				s.pop();
			else
				break;
		}
		s.push({ new_x,max_radius });
		cout << fixed << setprecision(5);
		cout << max_radius << "\n";
	}
	return 0;
}