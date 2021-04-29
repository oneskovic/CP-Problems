#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	vector<int> leftmost_color_position(51, INT_MAX);
	int element_count, query_count; 
	cin >> element_count >> query_count;
	for (int i = 0; i < element_count; i++)
	{
		int element; cin >> element;
		leftmost_color_position[element] = min(leftmost_color_position[element], i+1);
	}

	for (size_t i = 0; i < query_count; i++)
	{
		int color; cin >> color;
		cout << leftmost_color_position[color] << " ";
		for (int other_color = 1; other_color <= 50; other_color++)
		{
			if (other_color == color)
				continue;
			if (leftmost_color_position[other_color] < leftmost_color_position[color])
			{
				leftmost_color_position[other_color]++;
			}
		}
		leftmost_color_position[color] = 1;
	}
	
	return 0;
}