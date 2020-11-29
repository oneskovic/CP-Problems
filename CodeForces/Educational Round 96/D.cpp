#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int t; cin >> t;
	for (size_t test_no = 0; test_no < t; test_no++)
	{
		int n; cin >> n;
		string s; cin >> s;
		list<char> elements;
		copy(s.begin(), s.end(), back_inserter(elements));
		bool min_two = true;
		auto delete_pos = elements.begin();
		int no_operations = 0;
		while (!elements.empty())
		{
			no_operations++;
			//Seek next segment of min 2 elements
			while (min_two && delete_pos != elements.end())
			{
				char current_chr = *delete_pos;
				delete_pos++;
				if (delete_pos == elements.end())
					break;
				char next_chr = *delete_pos;
				if (current_chr == next_chr)
					break;
			}
			if (delete_pos == elements.end())
			{
				min_two = false;
				delete_pos = elements.begin();
			}
			//Perform operation 1
			delete_pos = elements.erase(delete_pos);
			if (min_two)
				delete_pos--;

			//Perform operation 2
			if (elements.empty())
				break;
			
			char start_chr = elements.front();
			auto it = elements.begin();
			bool erased_delete_pos = false;
			while (it !=elements.end() && *it == start_chr)
			{
				if (it == delete_pos)
					erased_delete_pos = true;
				it++;
			}
			elements.erase(elements.begin(), it);
			if (erased_delete_pos)
				delete_pos = elements.begin();
		}
		cout << no_operations << "\n";
	}
	return 0;
}