#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int test_cnt; cin>>test_cnt;
    while(test_cnt--)
    {
        int n; cin>>n;
        n*= 2;
        set<int> elements;
        vector<int> solution(n);
        for(int i = 0; i < n; i++)
        {
            int element;
            cin>>element;
            elements.insert(element);
        }
        solution[0] = *elements.begin();
        elements.erase(elements.begin());
        for(int i = 1; i < n; i++)
        {
            if(i == 1)
            {
                solution[i] = *elements.begin();
                elements.erase(elements.begin());
            }
            else
            {
                int e = *elements.begin();
                if(solution[i-1] == (solution[i-2]+e)/2 && elements.size() > 1)
                {
                    e = *(++elements.begin());
                }
                solution[i] = e;
                elements.erase(e);
            }
        }
        if(n > 2)
        {
            if(solution[n-2] == (solution[n-3] + solution[n-1])/2 ||
               solution[n-1] == (solution[n-2]+solution[0])/2 ||
               solution[0] == (solution[n-1] + solution[1])/2)
            {
                swap(solution[0],solution[n-1]);
            }
        }
        for(auto i : solution)
            cout << i << " ";
        cout << "\n";
    }
    return 0;
}
