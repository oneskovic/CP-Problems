#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <chrono>
#include <random>
using namespace std;
#define ll long long

void generate_test(ofstream& stream, int length, int min_el, int max_el)
{
	stream << length << "\n";
	for (size_t i = 0; i < length; i++)
	{
		stream << min_el + rand() % (max_el - min_el) << " ";
	}
	stream << "\n";
}

int main()
{
	int test_files; cin >> test_files;
	int tests_per_file; cin >> tests_per_file;
	int length; cin >> length;
	int min_el, max_el; cin >> min_el >> max_el;
	srand(time(0));
	for (size_t test_no = 0; test_no < test_files; test_no++)
	{
		ofstream in_file(to_string(test_no) + ".in");
		in_file << tests_per_file << "\n";
		for (size_t i = 0; i < tests_per_file; i++)
		{
			generate_test(in_file, length, min_el, max_el);
		}
	}
	return 0;
}