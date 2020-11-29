#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
unordered_map<string, long long> DPpPP;
string a, result_string;
long long min_moves_to_reverse(int last_reversed_pos, long long move_count)
{
	if (a == result_string)
	{
		DPpPP[a] = 0;
		return 0;
	}
	long long min_moves = INT_MAX;
	for (size_t i = 0; i < a.size()-1; i++)
	{
		if (i != last_reversed_pos)
		{
			swap(a[i], a[i + 1]);
			if (DPpPP.find(a) == DPpPP.end())
			{
				DPpPP[a] = -420;
				min_moves = min(min_moves, min_moves_to_reverse(i, move_count+1) + 1);
				DPpPP[a] = min_moves;
			}
			else if (DPpPP[a] != -420)
			{
				DPpPP[a] = min(DPpPP[a], move_count+1);
				min_moves = min(min_moves, DPpPP[a] + 1);
			}
			swap(a[i], a[i + 1]);
		}
	}
	DPpPP[a] = min_moves;
	return min_moves;
}

int main()
{
	a = "icpcsguru";
	DPpPP[a] = 0;
	result_string = a;
	reverse(result_string.begin(), result_string.end());
	cout << min_moves_to_reverse(-1,0);
	return 0;
}