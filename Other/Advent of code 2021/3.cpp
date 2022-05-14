#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

vector<int> find_elements_with_bit(const vector<int>& v, int position, bool bit)
{
	vector<int> solution;
	int mask = 1 << position;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] & mask)
		{
			if (bit)
			{
				solution.push_back(v[i]);
			}
		}
		else
		{
			if (!bit)
			{
				solution.push_back(v[i]);
			}
		}
	}
	return solution;
}

bool find_most_common_bit(const vector<int>& v, int position)
{
	int cnt_ones = 0;
	int mask = 1 << position;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] & mask)
		{
			cnt_ones++;
		}
	}
	if (2*cnt_ones >= v.size())
	{
		return 1;
	}
	else
		return 0;
}

int main()
{
	string input_path = "C:/Users/Ognjen/Desktop/Programiranje/Git Repos/CP-Problems/Other/Advent of code 2021/inputs/3.txt";
	ifstream input_file(input_path);
	string line;
	int n = 0;
	int k = 12;
	vector<int> count_ones(k);
	vector<int> elements;
	
	while (getline(input_file, line))
	{
		int element_value = 0;
		for (int i = 0; i < k; i++)
		{
			element_value <<= 1;
			if (line[i] == '1')
			{
				count_ones[i]++;
				element_value |= 1;
			}
		}

		elements.push_back(element_value);
		n++;
	}
	
	auto temp = elements;
	for (int i = 0; i < k && temp.size() > 1; i++)
	{
		bool most_common_bit = find_most_common_bit(temp, k - i - 1);
		temp = find_elements_with_bit(temp, k-i-1, most_common_bit);
	}
	int x = temp[0];

	temp = elements;
	for (int i = 0; i < k && temp.size() > 1; i++)
	{
		bool most_common_bit = find_most_common_bit(temp, k - i - 1);
		temp = find_elements_with_bit(temp, k-i-1, !most_common_bit);
	}
	int y = temp[0];
	cout << x * y << "\n";
	return 0;
}