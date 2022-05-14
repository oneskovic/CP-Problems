#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;
typedef long long ll;

struct stack_element
{
	ll value, added_element;
};

ll add_new_element(ll element, ll current_suffix_min, stack<stack_element>& max_stack, map<ll, int>& delay_cnt_map)
{
	while (!max_stack.empty() && max_stack.top().value <= element)
	{
		ll delay_to_erase = max_stack.top().added_element;
		max_stack.pop();
		delay_cnt_map[delay_to_erase]--;
		if (delay_cnt_map[delay_to_erase] == 0)
			delay_cnt_map.erase(delay_to_erase);
	}
	max_stack.push({ element, element - current_suffix_min });
	delay_cnt_map[element - current_suffix_min]++;
	return (--delay_cnt_map.end())->first;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<ll> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];
	
	vector<ll> prefix_max(n);
	prefix_max[0] = elements[0];
	for (int i = 1; i < n; i++)
		prefix_max[i] = max(prefix_max[i - 1], elements[i]);

	vector<ll> delays(n);
	for (int i = 0; i < n; i++)
		delays[i] = max(prefix_max[i] - elements[i],(ll)0);
	
	vector<ll> suffix_max_delays(n);
	suffix_max_delays.back() = delays.back();
	for (int i = n - 2; i >= 0; i--)
		suffix_max_delays[i] = max(delays[i], suffix_max_delays[i + 1]);
	
	stack<stack_element> max_stack;
	map<ll, int> delay_cnt_map;
	ll current_suffix_min = LLONG_MAX;
	ll solution = LLONG_MAX;
	for (int i = 0; i < n; i++)
	{
		current_suffix_min = min(current_suffix_min, elements[i]);
		ll new_delay = add_new_element(elements[i], current_suffix_min, max_stack, delay_cnt_map);
		ll remaining_delay = i + 1 < n ? suffix_max_delays[i + 1] : 0;
		ll new_solution = max(new_delay, remaining_delay);
		solution = min(solution, new_solution);
	}
	cout << solution << "\n";

	return 0;
}