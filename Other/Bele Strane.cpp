#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
#define ll long long

class Trie
{
public:
	Trie();
	Trie(const Trie& other);
	void insert_string(const string& str);
	ll count_prefix(const string& prefix);
private:
	class TrieNode
	{
	public:
		ll subtree_size;
		map<char, TrieNode*> children;
		TrieNode();
	};
	TrieNode* root;
};

int main()
{
	int n; cin >> n;
	Trie trie;
	for (size_t i = 0; i < n; i++)
	{
		string query_type; cin >> query_type;
		string s; cin >> s;
		if (query_type == "Dodaj")
		{
			trie.insert_string(s);
		}
		else
		{
			cout << trie.count_prefix(s) << "\n";
		}
	}
	return 0;
}

Trie::Trie()
{
	root = new TrieNode();
}

void Trie::insert_string(const string& str)
{
	auto current_node = root;
	for (size_t i = 0; i < str.size(); i++)
	{
		current_node->subtree_size++;
		if (current_node->children.find(str[i]) != current_node->children.end())
		{
			current_node = current_node->children[str[i]];
		}
		else
		{
			TrieNode* new_node = new TrieNode();
			current_node->children[str[i]] = new_node;
			current_node = new_node;
		}
	}
}

ll Trie::count_prefix(const string& prefix)
{
	auto current_node = root;
	for (size_t i = 0; i < prefix.size(); i++)
	{
		if (current_node->children.find(prefix[i]) != current_node->children.end())
		{
			current_node = current_node->children[prefix[i]];
		}
		else
		{
			return 0;
		}
	}
	return current_node->subtree_size;
}

Trie::TrieNode::TrieNode()
{
	subtree_size = 0;
}
