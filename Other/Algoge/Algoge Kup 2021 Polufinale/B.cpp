#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<string> steps;

vector<ll> merge_sorted(const vector<ll>& left, const vector<ll>& right, bool ascending, int current_deque, int result_deque)
{
    int l = 0, r = right.size()-1;
    vector<ll> res;

    while(l < left.size() && r >= 0)
    {
        string side = "P";
        ll number_to_add;
        if((ascending && left.at(l) <= right.at(r)) || (!ascending && left.at(l) >= right.at(r)))
            number_to_add = left.at(l++);
        else
        {
            number_to_add = right.at(r--);
            side = "Z";
        }
        if(number_to_add != -1)
        {
            steps.push_back(to_string(current_deque) + " " + side + " " + to_string(result_deque) + " Z\n");
            res.push_back(number_to_add);
        }
    }
    while(l < left.size())
    {
        ll number_to_add = left.at(l++);
        if(number_to_add != -1)
        {
            res.push_back(number_to_add);
            steps.push_back(to_string(current_deque) +" P " + to_string(result_deque) + " Z\n");
        }
    }
    while(r >= 0)
    {
        ll number_to_add = right.at(r--);
        if(number_to_add != -1)
        {
            res.push_back(number_to_add);
            steps.push_back(to_string(current_deque) + " Z " + to_string(result_deque) + " Z\n");
        }
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin>>n;

    deque<vector<ll>> a,b;
    for(int i = 0; i < n; i++)
    {
        ll element; cin>>element;
        a.push_back({element});
    }

    int closest_pow_of_2 = 1;
    while(closest_pow_of_2 < n)
    {
        closest_pow_of_2 *= 2;
    }
    for(int i = 0; i < closest_pow_of_2 - n; i++)
        a.push_back({-1});

    bool res_deque_index = 1;
    while(1)
    {
        deque<vector<ll>>& res_deque = (res_deque_index == 0 ? a : b);
        deque<vector<ll>>& current_deque = (res_deque_index == 0 ? b : a);

        bool asc = 1;
        while(!current_deque.empty())
        {
            auto res = merge_sorted(current_deque.front(),current_deque.back(),asc,!res_deque_index,res_deque_index);
            current_deque.pop_front();
            current_deque.pop_back();
            res_deque.push_back(res);
            asc = !asc;
        }
        res_deque_index = !res_deque_index;
        if(res_deque.size() == 1)
            break;
    }


    if(res_deque_index == 0)
    {
        for(int i = 0; i < n; i++)
            steps.push_back(to_string(!res_deque_index) + " P " + to_string(res_deque_index) + " Z\n");
    }
    cout << steps.size() << "\n";
    for(string& s: steps)
        cout << s;
    return 0;
}
