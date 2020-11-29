#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <string>
#include <fstream>
using namespace std;
#define ll long long

void preprocess(const vector<ll>& elements, vector<ll>& longest_solution_from)
{
	int n = elements.size();
	int left = 0, right = 1;
	int length = 1;
	int peak = -1;
	while (right < n)
	{
		if (elements[right] >= elements[right - 1])
		{
			if (peak == -1)
			{
				length++;
			}
			else
			{
				while (left < right - 1)
				{
					longest_solution_from[left] = length;
					length--; left++;
				}
				length = 2;
				peak = -1;
			}
		}
		else
		{
			if (peak == -1)
			{
				peak = right - 1;
			}
			length++;
		}
		right++;
	}
	length++;
	while (left < right - 1)
	{
		longest_solution_from[left] = length;
		length--; left++;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int n, query_count; cin >> n >> query_count;
	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	
	vector<ll> longest_solution_from(n, 1);
	preprocess(elements, longest_solution_from);

	for (size_t query_no = 0; query_no < query_count; query_no++)
	{
		int query_left, query_right; cin >> query_left >> query_right;
		if (longest_solution_from[query_left - 1] + query_left - 1 >= query_right)
			cout << "Yes\n";
		else
			cout << "No\n";
	}
	return 0;
}