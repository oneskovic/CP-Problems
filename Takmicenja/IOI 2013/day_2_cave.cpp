#include <bits/stdc++.h>
using namespace std;

int n;
map<int,int> switch_door_map, switch_position_map;
int tryCombination(int S[])
{
    vector<int> door_state(n);
    for(int i = 0; i < n; i++)
    {
        if(S[i] == switch_position_map[i])
        {
            door_state[switch_door_map[i]] = 1;
        }
    }
    for(int i = 0; i < n; i++)
    {
        if(door_state[i] == 0)
        {
            return i;
        }
    }
    return -1;
}
void answer(int S[],int D[])
{
    for(int i = 0; i < n; i++)
    {
        if(D[i] != switch_door_map[i] || S[i] != switch_position_map[i])
        {
            cout << "WA\n";
            system("pause");
        }
    }
}

void generate_random()
{
    srand(time(0));
    n = rand()%20 + 1;
    vector<int> switch_door(n);
    iota(switch_door.begin(),switch_door.end(),0);
    int swaps = rand()%10000;
    while(swaps--)
        swap(switch_door[rand()%n],switch_door[rand()%n]);
    for(int i = 0; i < n; i++)
        switch_door_map[i] = switch_door[i];
    for(int i = 0; i < n; i++)
        switch_position_map[i] = rand()%2;
}

vector<int> subtask1()
{
    map<int,int> switch_door_map, switch_position_map;

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    return 0;
}
