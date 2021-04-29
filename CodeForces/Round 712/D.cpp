#include <bits/stdc++.h>
#include <string>
using namespace std;

set<int> get_available()
{
    int choice; cin>>choice;
    set<int> available = {1,2,3};
    available.erase(choice);
    return available;
}


vector<int> positions_for_first, positions_for_second;
set<int> colors_for_first, colors_for_second;
int pos_first = 0, pos_second = 0;
int n;

bool first_done()
{
    return pos_first >= positions_for_first.size();
}
bool second_done()
{
    return pos_second >= positions_for_second.size();
}

bool can_play_first(set<int> available)
{
    for(int c: colors_for_first)
    {
        if (available.find(c) != available.end())
        {
            return true;
        }
    }

    return false;
}
bool can_play_second(set<int> available)
{
    for(int c: colors_for_second)
    {
        if (available.find(c) != available.end())
        {
            return true;
        }
    }

    return false;
}

void play_first(set<int> available)
{
    int pos = positions_for_first[pos_first++];
    int color_to_use = 0;
    for(int c: colors_for_first)
    {
        if (available.find(c) != available.end())
        {
            color_to_use = c;
            break;
        }
    }

    cout << color_to_use << " " << pos/n + 1 << " " << pos%n + 1 << "\n";
    cout.flush();
}
void play_second(set<int> available)
{
    int pos = positions_for_second[pos_second++];
    int color_to_use = 0;
    for(int c: colors_for_second)
    {
        if (available.find(c) != available.end())
        {
            color_to_use = c;
            break;
        }
    }

    cout << color_to_use << " " << pos/n + 1<< " " << pos%n + 1 << "\n";
    cout.flush();
}

void print_vec(vector<int> v)
{
    for (int i: v)
    {
        cout << i<<" ";
    }
    cout << "\n";
}

int main()
{
    cin>>n;

    for(int row = 0; row < n; row++)
    {
        int mod_first = row%2 == 0 ? 0 : 1;
        int mod_second = !mod_first;
        for(int col = 0; col < n; col++)
        {
            if(col % 2 == mod_first)
            {
                positions_for_first.push_back(n*row+col);
            }
            else
                positions_for_second.push_back(n*row+col);
        }
    }
    //print_vec(positions_for_first);
    //print_vec(positions_for_second);

    auto available = get_available();
    colors_for_first = {*available.begin()};
    play_first(available);

    available = get_available();
    for(int c: available)
    {
        if(colors_for_first.find(c) == colors_for_first.end())
        {
            colors_for_second = {c};
            break;
        }
    }
    play_second(available);

    int turn_num = 2;


    while(turn_num <  n*n)
    {
        available = get_available();
        bool c1 = can_play_first(available);
        bool c2 = can_play_second(available);
        if(c1 && !first_done())
        {
            play_first(available);
            if(first_done())
            {
                int c1 = *colors_for_first.begin();
                int c2 = *colors_for_second.begin();
                int c3 = (1+2+3)-c1-c2;
                colors_for_second.insert(c3);
            }
        }
        else
        {
            play_second(available);
            if(second_done())
            {
                int c1 = *colors_for_first.begin();
                int c2 = *colors_for_second.begin();
                int c3 = (1+2+3)-c1-c2;
                colors_for_first.insert(c3);
            }
        }
        turn_num++;
    }
    return 0;
}
