#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class TrieNode
{
public:
	TrieNode(int min_word_length);
	int min_word_length; // The minimal length of a word that can be added to this node
	vector<TrieNode*> children;
};

class Trie
{
public:
	Trie();
	string add_string_of_length(int length);
private:
	void add_string_dfs(TrieNode* current_node, string& current_str, int length_to_add, int current_len);
	TrieNode* root;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int word_count; cin >> word_count;
	
	vector<pair<int,int>> lengths(word_count);
	for (size_t i = 0; i < word_count; i++)
	{
		cin >> lengths[i].first;
		lengths[i].second = i;
	}
	sort(lengths.begin(), lengths.end());

	vector<string> solution(word_count);
	Trie trie;
	for (auto t : lengths)
	{
		int len = t.first;
		string s = trie.add_string_of_length(len);
		if (s == "")
		{
			cout << "NO\n";
			return 0;
		}
		int original_index = t.second;
		solution[original_index] = s;
	}
	cout << "YES\n";
	for (const string& s: solution)
	{
		cout << s << "\n";
	}

	return 0;
}

TrieNode::TrieNode(int min_word_length)
{
	this->min_word_length = min_word_length;
	children = vector<TrieNode*>(2, nullptr);
}

Trie::Trie()
{
	root = new TrieNode(1);
	root->children[0] = new TrieNode(1);
	root->children[1] = new TrieNode(1);
}

string Trie::add_string_of_length(int length)
{
	if (root->min_word_length > length)
		return "";

	string s = "";
	add_string_dfs(root, s, length, 0);
	return s;
}

void Trie::add_string_dfs(TrieNode* current_node, string& current_str, int length_to_add, int current_len)
{
	if (current_len == length_to_add)
	{
		current_node->min_word_length = INT_MAX;
	}
	else
	{
		if (current_node->children[0] == nullptr)
		{
			current_node->children[0] = new TrieNode(current_len + 1);
			current_node->children[1] = new TrieNode(current_len + 1);
			current_str += "0";
			add_string_dfs(current_node->children[0], current_str, length_to_add, current_len + 1);
		}
		else
		{
			TrieNode* min_child = nullptr;
			int min_len = INT_MAX;
			char c = '0';
			for (int child = 0; child <= 1; child++)
			{
				if (current_node->children[child]->min_word_length <= length_to_add)
				{
					if (min_len > current_node->children[child]->min_word_length)
					{
						min_len = current_node->children[child]->min_word_length;
						min_child = current_node->children[child];
						c = '0' + child;
					}
				}
			}
			current_str += c;
			add_string_dfs(min_child, current_str, length_to_add, current_len + 1);
		}
		current_node->min_word_length = min(current_node->children[0]->min_word_length, current_node->children[1]->min_word_length);
	}
}
