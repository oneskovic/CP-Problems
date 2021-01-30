#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
using namespace std;
#define ll long long

vector<ll> elements;
int m;

ll element_at(int i, int j)
{
	return elements[i * m + j];
}

int main()
{
	int n, a, b;
	cin >> n >> m >> a >> b;
	elements = vector<ll>(n*m);
	cin >> elements[0];
	ll x, y, z;
	cin >> x >> y >> z;
	for (size_t i = 1; i < elements.size(); i++)
		elements[i] = (elements[i - 1] * x + y) % z;
	
	vector<vector<ll>> min_in_range(n, vector<ll>(m));
	for (size_t row = 0; row < n; row++)
	{
		deque<int> current_elements;
		int r = 0;
		while (r < m)
		{
			if (!current_elements.empty() && current_elements.front() == r - b)
				current_elements.pop_front();

			int current_element = element_at(row, r);
			while (!current_elements.empty() && element_at(row, current_elements.back()) > current_element)
				current_elements.pop_back();
			current_elements.push_back(r);

			min_in_range[row][r] = element_at(row, current_elements.front());
			r++;
		}
	}

	ll solution = 0;

	for (size_t col = b-1; col < m; col++)
	{
		deque<int> current_elements;
		int down = 0;
		while (down < n)
		{
			if (!current_elements.empty() && current_elements.front() == down - a)
				current_elements.pop_front();

			int current_element = min_in_range[down][col];
			while (!current_elements.empty() && min_in_range[current_elements.back()][col] > current_element)
				current_elements.pop_back();
			current_elements.push_back(down);

			if (down >= a-1)
				solution += min_in_range[current_elements.front()][col];
	
			down++;
		}
	}

	cout << solution;
	return 0;
}