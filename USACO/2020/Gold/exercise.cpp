#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<bool> is_prime;

void sieve(ll max_n)
{
    is_prime = vector<bool>(max_n+1, 1);
    for(int prime = 2; prime <= max_n; prime++)
    {
        if(is_prime[prime])
        {
            for(int i = 2*prime; i <= max_n; i += prime)
            {
                is_prime[i] = 0;
            }
        }
    }
}
vector<ll> get_primes()
{
    vector<ll> primes = {1};
    for(int i = 2; i < is_prime.size(); i++)
    {
        if(is_prime[i])
            primes.push_back(i);
    }
    return primes;
}

int main()
{
    freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n,m; cin>>n>>m;
    sieve(n);

    vector<ll> primes = get_primes();
    vector<vector<ll>> dp(primes.size(), vector<ll>(n+1));
    for(int i = 0; i <= n; i++)
        dp[0][i] = 1;

    // non 0/1 knapsack
    for(int prime_index = 1; prime_index < primes.size(); prime_index++)
    {
        for(int capacity = 0; capacity <= n; capacity++)
        {
            ll prime_pow = primes[prime_index];
            dp[prime_index][capacity] = dp[prime_index-1][capacity];
            while(prime_pow <= capacity)
            {
                dp[prime_index][capacity] += (prime_pow * dp[prime_index-1][capacity - prime_pow])%m;
                dp[prime_index][capacity] %= m;
                prime_pow *= primes[prime_index];
            }
        }
    }
    cout << dp.back().back() << "\n";

    return 0;
}
