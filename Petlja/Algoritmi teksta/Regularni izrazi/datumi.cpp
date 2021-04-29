#include <bits/stdc++.h>
#include <regex>
using namespace std;

int main()
{
    /*ios::sync_with_stdio(false);
    cin.tie(0);*/

    string line;
    while(getline(cin,line))
    {
        smatch m = smatch();
        regex expr("\\d{1,2}\\.\\d{1,2}\\.\\d{4}\\.");
        if(regex_search(line,m,expr))
        {
            cout << m[0] << endl;
        }
        else
        {
            m = smatch();
            expr = regex("\\d{2}/\\d{2}/\\d{4}");
            if(regex_search(line,m,expr));
            {
                string s = m[0];
                string month = s.substr(0,2);
                string day = s.substr(3,2);
                string year = s.substr(6,4);
                cout << day << "." << month << "." << year << "." << endl;
            }
        }
    }
    return 0;
}
