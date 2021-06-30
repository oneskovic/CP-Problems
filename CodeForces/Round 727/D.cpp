#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
typedef long long ll;
using namespace std;

struct item
{
	ll ammount_needed, ammount_for_discount;
};

ll check(vector<item> items, ll ammount_to_buy_price_2)
{
	ll bought = 0;
	int j = items.size() - 1;
	while (bought < ammount_to_buy_price_2)
	{
		ll b = min(ammount_to_buy_price_2 - bought, items[j].ammount_needed);
		bought += b;
		items[j].ammount_needed -= b;
		j--;
	}
	ll price = 2 * ammount_to_buy_price_2;
	for (int i = 0; i < items.size() && items[i].ammount_needed > 0; i++)
	{
		if (items[i].ammount_for_discount > bought)
		{
			ll diff = items[i].ammount_for_discount - bought;
			bought += diff;
			price += diff;
		}
		price += items[i].ammount_needed;
		bought += items[i].ammount_needed;
	}
	return price;

}

bool operator < (const item& lhs, const item& rhs)
{
	return lhs.ammount_for_discount < rhs.ammount_for_discount;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<item> items(n);
	ll total_item_count = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> items[i].ammount_needed >> items[i].ammount_for_discount;
		total_item_count += items[i].ammount_needed;
	}
	sort(items.begin(), items.end());
	ll l = min(items[0].ammount_for_discount,total_item_count), r = max(items[0].ammount_for_discount,total_item_count);

	cout << check(items, l);

	return 0;
}