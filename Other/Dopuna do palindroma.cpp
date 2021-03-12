#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef long long ll;

class TrieNode
{
public:
	TrieNode();
	ll subtree_size;
	map<char, TrieNode*> children;
};

class Trie
{
public:
	Trie();
	void insert_string(const string& str);
	TrieNode* root;
};

int main()
{
	int n; cin >> n;
	Trie trie;
	for (size_t i = 0; i < n; i++)
	{
		string s; cin >> s;
		trie.insert_string(s);
	}
	
	int m; cin >> m;
	for (size_t i = 0; i < m; i++)
	{
		string s; cin >> s;
		string from_trie = "";
		
		TrieNode* current_node = trie.root;
		int r = s.size() - 1;
		while (s[r] != s[0])
		{
			current_node = current_node->children[s[r]];
			from_trie += s[r];
			r--;
		}
		cout << from_trie + s << "\n";
	}
	return 0;
}

Trie::Trie()
{
	root = new TrieNode();
}

void Trie::insert_string(const string& str)
{
	TrieNode* current_node = root;
	for (size_t i = 0; i < str.size(); i++)
	{
		current_node->subtree_size++;
		if (current_node->children.find(str[i]) == current_node->children.end())
		{
			current_node->children[str[i]] = new TrieNode();
		}
		current_node = current_node->children[str[i]];

	}
}

TrieNode::TrieNode()
{
	subtree_size = 0;
}
