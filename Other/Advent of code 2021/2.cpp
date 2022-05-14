#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int main()
{
	string input_path = "C:/Users/Ognjen/Desktop/Programiranje/Git Repos/CP-Problems/Other/Advent of code 2021/inputs/2.txt";
	ll current_depth = 0;
	ll current_horizontal = 0;
	ll current_aim = 0;
	ifstream input_file(input_path);
	string line;
	while (getline(input_file,line))
	{
		string type = line.substr(0,line.find(" "));
		ll x = stoll(line.substr(line.find(" ")+1));
		
		if (type == "forward")
		{
			current_horizontal += x;
			current_depth += x * current_aim;
		}
		else if (type == "up")
		{
			current_aim -= x;
		}
		else
		{
			current_aim += x;
		}
		cout << x << "\n";
	}
	cout << current_depth * current_horizontal << "\n";
	return 0;
}