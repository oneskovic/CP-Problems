#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

ll div_ceil(ll a, ll b)
{
	return (a + b - 1) / b;
}

bool check(vector<ll> charges, const vector<ll>& usages, ll charger_power, ll k)
{
	int n = charges.size();
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> time_of_discharge;
	for (int i = 0; i < n; i++)
	{
		ll t = div_ceil(charges[i], usages[i]);
		time_of_discharge.push({ t, i });
	}

	ll current_time = 0;
	bool possible = 1;
	while (time_of_discharge.top().first < k)
	{
		if (time_of_discharge.top().first <= current_time)
		{
			possible = 0;
			break;
		}
		else
		{
			int index = time_of_discharge.top().second;
			time_of_discharge.pop();
			charges[index] += charger_power;
			ll new_t = div_ceil(charges[index], usages[index]);
			time_of_discharge.push({ new_t,index });
			current_time++;
		}
	}
	return possible;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k; cin >> n >> k;
	
	vector<ll> charges(n), usages(n);
	for (int i = 0; i < n; i++)
		cin >> charges[i];
	
	for (int i = 0; i < n; i++)
		cin >> usages[i];
	
	for (int power = 0; power < 1000; power++)
	{
		if (check(charges, usages, power, k))
		{
			cout << power << "\n";
			break;
		}
	}
	
	return 0;
}