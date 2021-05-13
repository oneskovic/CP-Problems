#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int broj_placeva, broj_brace, duzina_kuce;
	cin >> broj_placeva >> broj_brace >> duzina_kuce;

	int pocetno_praznih = broj_placeva - broj_brace * duzina_kuce;
	int pocetno_kuca = broj_brace;
	// dp[i][j] -> f(smesteno_kuca,smesteno_praznih)
	vector<vector<ll>> dp(2, vector<ll>(pocetno_praznih+1));

	vector<ll> vrednosti(broj_placeva);
	for (size_t i = 0; i < broj_placeva; i++)
		cin >> vrednosti[i];

	for (int smesteno_kuca = pocetno_kuca-1; smesteno_kuca >= 0; smesteno_kuca--)
	{
		for (int smesteno_praznih = pocetno_praznih; smesteno_praznih >= 0; smesteno_praznih--)
		{
			int pozicija = smesteno_praznih + smesteno_kuca * duzina_kuce;
			ll stavi_kucu = dp[1][smesteno_praznih] + vrednosti[pozicija];
			ll ne_stavljaj_kucu = 0;
			if (smesteno_praznih < pocetno_praznih) // preostalo je jos praznih mesta
				ne_stavljaj_kucu = dp[0][smesteno_praznih + 1];
			dp[0][smesteno_praznih] = max(stavi_kucu, ne_stavljaj_kucu);
		}
		dp[1] = dp[0];
	}
	cout << dp[0][0];
	
	return 0;
}
