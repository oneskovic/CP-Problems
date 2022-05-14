#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef long long ll;

struct operation
{
	int x, y, z;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];

		bool ok = (elements[n - 1] >= elements[n - 2]);
		int positive_element_pos = -1;
		if (elements[n-1] >= 0)
		{
			positive_element_pos = n - 1;
		}
		vector<operation> ops; ops.reserve(n);
		for (int i = n-3; i >= 0 && ok; i--)
		{
			if (elements[i] > elements[i+1])
			{
				if (positive_element_pos == -1)
				{
					ok = false;
					break;
				}
				else
				{
					elements[i] = elements[i + 1] - elements[positive_element_pos];
					ops.push_back({ i,i + 1,positive_element_pos });
				}
			}
		}
		if (ok)
		{
			cout << ops.size() << "\n";
			for (auto op: ops)
			{
				cout << op.x+1 << " " << op.y+1 << " " << op.z+1 << "\n";
			}
		}
		else
		{
			cout << "-1\n";
		}
	}

	return 0;
}
