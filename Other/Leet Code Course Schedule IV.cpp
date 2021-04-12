#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    static vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {

		vector<vector<bool>> relation(n, vector<bool>(n));
		for (auto p: prerequisites)
			relation[p[0]][p[1]] = 1;

		for (int k = 0; k < n; k++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (relation[i][k] && relation[k][j])
					{
						relation[i][j] = 1;
					}
				}
			}
		}

		vector<bool> solution; solution.reserve(n);
		for (auto q: queries)
			solution.push_back(relation[q[0]][q[1]]);
		return solution;
    }
};

int main()
{
	vector<vector<int>> prerequisites = { {0,1},{1,2},{2,3},{3,4} };
	vector<vector<int>> queries = { {0,4},{4,0},{1,3},{3,0} };
	auto sol = Solution::checkIfPrerequisite(5, prerequisites, queries);
	return 0;
}