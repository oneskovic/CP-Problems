#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

ll pow2_geq(ll x)
{
	ll pow = 1;
	while (pow < x)
	{
		pow *= 2;
	}
	return pow;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<ll> weights(n);
		for (int i = 0; i < n; i++)
		{
			cin >> weights[i];
		}
		sort(weights.begin(), weights.end());
		vector<pair<ll, ll>> compressed_weights; compressed_weights.reserve(n);
		
		ll current_cnt = 1;
		for (int i = 1; i < n; i++)
		{
			if (weights[i] == weights[i-1])
			{
				current_cnt++;
			}
			else
			{
				compressed_weights.push_back({ weights[i - 1],current_cnt });
				current_cnt = 1;
			}
		}
		compressed_weights.push_back({ weights.back(), current_cnt});

		int n_compressed = compressed_weights.size();
		vector<ll> prefix_sums(n_compressed);
		prefix_sums[0] = compressed_weights[0].second;
		for (int i = 1; i < n_compressed; i++)
		{
			prefix_sums[i] = prefix_sums[i - 1] + compressed_weights[i].second;
		}

		pair<int, int> best_sol;
		ll best_score = LLONG_MAX;
		ll search_bound = pow2_geq(n);
		for (int left_section_size = 1; left_section_size <= search_bound; left_section_size*=2)
		{
			auto lb_left = upper_bound(prefix_sums.begin(), prefix_sums.end(), left_section_size);
			if (lb_left == prefix_sums.begin())
				continue;
			lb_left--;
			int left_taken = *lb_left;
			
			for (int middle_section_size = 1; middle_section_size <= search_bound; middle_section_size *= 2)
			{
				int middle_taken = 0;
				if (left_taken < n)
				{
					auto lb_middle = upper_bound(lb_left, prefix_sums.end(), middle_section_size + left_taken);
					if (lb_middle == lb_left)
						continue;
					lb_middle--;
					middle_taken = *lb_middle - left_taken;
				}

				int remaining = n - left_taken - middle_taken;
				
				ll score = left_section_size - left_taken + middle_section_size - middle_taken + pow2_geq(remaining) - remaining;
				if (score < best_score)
				{
					best_score = score;
					best_sol = { left_taken, middle_taken };
				}
			}
		}

		/*ll left_taken = best_sol.first;
		ll middle_taken = best_sol.second;
		ll first_boundary = weights[left_taken];
		ll second_boundary = weights[middle_taken + left_taken];
		cout << first_boundary << " " << second_boundary << "\n";*/
		cout << best_score << "\n";
	}

	return 0;
}