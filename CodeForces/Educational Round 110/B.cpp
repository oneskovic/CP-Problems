#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    if(b == 0)
        return a;
    return gcd(b,a%b);
}

int count_good_pairs(const vector<int>& solution)
{
    int n = solution.size();
    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(gcd(solution[i],2*solution[j]) > 1)
                cnt++;
        }
    }
    return cnt;
}

int brute_force(const vector<int>& elements)
{
    auto elems_cpy = elements;
    sort(elems_cpy.begin(),elems_cpy.end());
    int max_res = 0;
    do
    {
        max_res = max(max_res, count_good_pairs(elems_cpy));
    }while(next_permutation(elems_cpy.begin(),elems_cpy.end()));
    return max_res;
}

int solve(const vector<int>& elements)
{
    int n = elements.size();
    vector<int> solution = vector<int>(n);
    int j = 0;
    vector<int> odd;
    for(int i = 0; i < n; i++)
    {
        if(elements[i] % 2 == 0)
            solution[j++] = elements[i];
        else
            odd.push_back(elements[i]);
    }
    for(int i = 0; i < odd.size(); i++)
        solution[j++] = odd[i];
    return count_good_pairs(solution);
}


void test()
{
    srand(time(0));
    int n = rand()%8 + 2;
    vector<int> elements = vector<int>(n);
    for(int i = 0; i < n; i++)
    {
        elements[i] = rand() % 100000 + 1;
    }
    int s1 = solve(elements);
    int s2 = brute_force(elements);
    if(s1 != s2)
    {
        cout << "WA\n";
        system("pause");
    }
    else
        cout << "OK\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        int n; cin>>n;
        vector<int> elements(n);
        for(int i = 0; i < n; i++)
        {
            cin>>elements[i];
        }
        cout << solve(elements) << "\n";
        //test();
    }
    return 0;
}
