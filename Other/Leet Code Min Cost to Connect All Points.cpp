#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;

class DSU
{
public:
    DSU(int max_elements);
    int find_set(int element);
    void join_sets(int element1, int element2);
private:
    vector<int> representative;
    vector<int> rank;
};

struct edge
{
    int node1, node2;
    ll weight;
};

bool operator<(const edge& lhs, const edge& rhs)
{
    return lhs.weight < rhs.weight;
}

class Solution {
public:
    static int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        DSU dsu = DSU(n * n);
        vector<edge> edges; edges.reserve(n * n);
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                ll dx = abs(points[i][0] - points[j][0]);
                ll dy = abs(points[i][1] - points[j][1]);
                ll weight = dx + dy;
                edges.push_back({ i,j, weight });
            }
        }

        sort(edges.begin(), edges.end());
        ll total_weight = 0;
        for (size_t i = 0; i < edges.size(); i++)
        {
            edge current_edge = edges[i];
            if (dsu.find_set(current_edge.node1) != dsu.find_set(current_edge.node2))
            {
                dsu.join_sets(current_edge.node1, current_edge.node2);
                total_weight += current_edge.weight;
            }
        }
        return total_weight;
    }
};

DSU::DSU(int max_elements)
{
    representative = vector<int>(max_elements);
    iota(representative.begin(), representative.end(), 0);
    rank = vector<int>(max_elements, 1);
}

int DSU::find_set(int element)
{
    if (representative[element] == element)
    {
        return element;
    }
    return representative[element] = find_set(representative[element]);
}

void DSU::join_sets(int element1, int element2)
{
    int set1 = find_set(element1);
    int set2 = find_set(element2);
    if (rank[set1] == rank[set2])
        rank[set1]++;
    
    if (rank[set2] > rank[set1])
        swap(set1, set2);
    
    // rank[set2] <= rank[set1]
    representative[set2] = set1;
}

int main()
{
    vector<vector<int>> v = { {0,0},{2,2},{3,10},{5,2},{7,0} };
    auto sol = Solution::minCostConnectPoints(v);
    return 0;
}