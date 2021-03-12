#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define ll unsigned long long
class TrieNode
{
public:
	TrieNode();
	vector<TrieNode*> children;
	int count;
};

class Trie
{
public:
	Trie();
	void insert_number(ll number);
	void erase_number(ll number);
	ll find_largest_xor(ll number);
private:
	bool erase_recursive(ll number, ll mask, TrieNode* current_node);
	TrieNode* root;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int query_count; cin >> query_count;
	Trie trie = Trie();
	trie.insert_number(0);
	for (ll i = 0; i < query_count; i++)
	{
		char query_type; cin >> query_type;
		ll number; cin >> number;
		if (query_type == '+')
		{
			trie.insert_number(number);
		}
		else if (query_type == '-')
		{
			trie.erase_number(number);
		}
		else
		{
			cout << trie.find_largest_xor(number) << "\n";
		}
	}
	return 0;
}

TrieNode::TrieNode()
{
	children = vector<TrieNode*>(2, nullptr);
	count = 0;
}

Trie::Trie()
{
	root = new TrieNode();
}

void Trie::insert_number(ll number)
{
	TrieNode* current_node = root;
	ll mask = ((ll)1) << 31;
	while (mask >= 1)
	{
		current_node->count++;
		if (number & mask)
		{
			if (current_node->children[1] == nullptr)
			{
				current_node->children[1] = new TrieNode();
			}
			current_node = current_node->children[1];
		}
		else
		{
			if (current_node->children[0] == nullptr)
			{
				current_node->children[0] = new TrieNode();
			}
			current_node = current_node->children[0];
		}
		mask >>= 1;
	}
	current_node->count++;
}

void Trie::erase_number(ll number)
{
	erase_recursive(number, ((ll)1) << 31, root);
}

ll Trie::find_largest_xor(ll number)
{
	ll solution = 0;
	TrieNode* current_node = root;
	ll mask = ((ll)1) << 31;
	while (mask > 1)
	{
		bool current_bit = number & mask;
		if (current_node->children[0] == nullptr && current_node->children[1] == nullptr)
		{
			break;
		}
		if (current_node->children[!current_bit] != nullptr)
		{
			current_node = current_node->children[!current_bit];
			solution |= (!current_bit);
		}
		else
		{
			current_node = current_node->children[current_bit];
			solution |= current_bit;
		}
		solution <<= 1;
		mask >>= 1;
	}
	bool current_bit = number & mask;
	if (current_node->children[!current_bit] != nullptr)
	{
		current_node = current_node->children[!current_bit];
		solution |= (!current_bit);
	}
	else
	{
		current_node = current_node->children[current_bit];
		solution |= current_bit;
	}
	return solution ^ number;
}

bool Trie::erase_recursive(ll number, ll mask, TrieNode* current_node)
{
	current_node->count--;
	if (mask == 0)
	{
		return current_node->count == 0;
	}
	bool current_bit = number & mask;

	if (erase_recursive(number,mask>>1,current_node->children[current_bit]))
	{
		current_node->children[current_bit] = nullptr;
	}
	
	return current_node->count == 0;
}
