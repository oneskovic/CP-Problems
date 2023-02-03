#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

class IntegerRange
{
public:
	IntegerRange(ll low, ll high) {
		this->low = low;
		this->high = high+1;
	};
	class Iterator
	{
	public:
		using iterator_category = random_access_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = ll;
		using pointer = ll*;
		using reference = ll&;

		Iterator(pointer ptr) {
			m_ptr = new ll;
			*m_ptr = *ptr;
		}
		Iterator(const Iterator& it)
		{
			m_ptr = new ll;
			*m_ptr = *it;
		}

		reference operator*() const { return *m_ptr; }

		friend bool operator== (const Iterator& a, const Iterator& b) { 
			return *a.m_ptr == *b.m_ptr; 
		};

		friend bool operator!= (const Iterator& a, const Iterator& b) { 
			return *a.m_ptr != *b.m_ptr; 
		};

		Iterator& operator++() {
			*m_ptr += 1;
			return *this; 
		}

		Iterator operator+(const difference_type delta) { 
			return Iterator(m_ptr + delta); 
		}

		Iterator& operator+=(const difference_type delta) { 
			*m_ptr+=delta; 
			return *this; 
		}

		Iterator operator-(const difference_type delta) { 
			return Iterator(m_ptr - delta); 
		}

		difference_type operator-(const Iterator& other) { 
			return *m_ptr - *other.m_ptr; 
		}

		reference operator[](size_t index) const { 
			ll x = *m_ptr + index;
			return x; 
		}
	private:
		pointer m_ptr;
	};
	Iterator begin() { return Iterator(&low); }
	Iterator end() { return Iterator(&high); }
private:
	ll low, high;
};

struct point
{
	int x, y;
};

bool are_connected(point transmiter, point reciever, ll power)
{
	ll dx = transmiter.x - reciever.x;
	ll dy = transmiter.y - reciever.y;
	return dx * dx + dy * dy <= power;
}

int count_reachable_nodes(int node, vector<bool>& visited, const vector<vector<int>>& graph)
{
	int res = 1;
	visited[node] = 1;
	for (int neighbor: graph[node])
		if (!visited[neighbor])
			res += count_reachable_nodes(neighbor, visited, graph);	
	return res;
}

int check(ll x, const vector<point>& points)
{
	int n = points.size();
	vector<vector<int>> graph(n, vector<int>());

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				continue;
			if (are_connected(points[i], points[j], x))
				graph[i].push_back(j);
		}
	}

	int max_reachable_nodes = 0;
	for (int start_node = 0; start_node < n; start_node++)
	{
		vector<bool> visited(n);
		max_reachable_nodes = max(max_reachable_nodes, count_reachable_nodes(start_node, visited, graph));
		if (max_reachable_nodes == n)
			return 1;
	}
	return 0;
}

int main()
{
	freopen("moocast.in", "r", stdin);
	freopen("moocast.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<point> points(n);
	for (int i = 0; i < n; i++)
		cin >> points[i].x >> points[i].y;
	
	auto possible_x_values = IntegerRange(0, 2500000000);
	int sol = *lower_bound(possible_x_values.begin(), possible_x_values.end(), 1,
		[points](ll lhs, ll val) {
			return check(lhs, points) < val;
		});
	cout << sol;
	return 0;
}