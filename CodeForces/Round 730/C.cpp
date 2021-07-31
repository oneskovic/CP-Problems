#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;
const double eps = 1e-9;
const ll scale_factor = 1000000;

double probability_of_sequence(const vector<int>& sequence, vector<ll> probabilities, ll v)
{
	double solution = 1;
	for (int i = 0; i < sequence.size(); i++)
	{
		int choice = sequence[i];
		vector<int> temp = { 0,1,2 };
		temp.erase(find(temp.begin(), temp.end(), choice));

		int other1 = temp[0];
		int other2 = temp[1];
		
		if (choice == 2)
		{
			return (solution * probabilities[choice] * (i+1) / scale_factor);
		}

		if (probabilities[choice] == 0)
		{
			return 0;
		}
		else
		{
			solution *= probabilities[choice] / scale_factor;
			double to_distribute = 0;
			if (probabilities[choice] < v)
			{
				probabilities[choice] = 0;
				to_distribute = probabilities[choice];
			}
			else
			{
				probabilities[choice] -= v;
				to_distribute = v;
			}
			if (probabilities[other1] > 0 && probabilities[other2] > 0)
			{
				probabilities[other1] += to_distribute / 2.0;
				probabilities[other2] += to_distribute / 2.0;
			}
			else
			{
				int remaining = probabilities[other1] <= 0 ? other2: other1;
				probabilities[remaining] += to_distribute;
			}
		}
	}
	return solution;
}

double solve(vector<int>& sequence, int pos,const vector<ll>& probabilities, const double v)
{
	double p = 0;
	if (pos < sequence.size())
	{
		sequence[pos] = 2;
		double prob_of_seq = probability_of_sequence(sequence, probabilities, v);
		if (prob_of_seq < eps)
			return 0;
		p += prob_of_seq;
		sequence[pos] = 0;
		p += solve(sequence, pos + 1, probabilities, v);
		sequence[pos] = 1;
		p += solve(sequence, pos + 1, probabilities, v);
	}
	return p;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;

	while (test_cnt--)
	{
		vector<ll> probabilities(3);
		for (int i = 0; i < 3; i++)
		{
			double p; cin >> p;
			probabilities[i] = p*scale_factor;
		}
		double v; cin >> v;
		vector<int> sequence(23);
		cout << solve(sequence, 0, probabilities, v) << "\n";
	}
	return 0;
}