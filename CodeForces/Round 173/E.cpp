#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define ll long long

class TrieNode
{
public:
	TrieNode();
	int subtree_size;
	vector<TrieNode*> children;
};

class Trie
{
public:
	Trie();
	void insert_number(ll number);
	void erase_number(ll number);
	ll largest_xor(ll number);	
private:
	TrieNode* root;
	bool erase_recursive(ll number, ll mask, TrieNode* current_node);
	void insert_recursive(ll number, ll mask, TrieNode* current_node);
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];

	vector<ll> suffix(n+1);
	suffix[n] = 0;
	for (int i = n-1; i >= 0; i--)
		suffix[i] = suffix[i + 1] ^ elements[i];
	
	Trie suffix_trie;
	for (ll s: suffix)
		suffix_trie.insert_number(s);
	
	ll current_max = -1;
	ll current_prefix = 0;
	for (int i = 0; i < n; i++)
	{
		current_max = max(current_max, suffix_trie.largest_xor(current_prefix));
		current_prefix ^= elements[i];
		suffix_trie.erase_number(suffix[i]);
	}
	current_max = max(current_max, suffix_trie.largest_xor(current_prefix));
	cout << current_max << "\n";
	return 0;
}

TrieNode::TrieNode()
{
	subtree_size = 0;
	children = vector<TrieNode*>(2, nullptr);
}

Trie::Trie()
{
	root = new TrieNode();
}

void Trie::insert_number(ll number)
{
	insert_recursive(number, (ll)1 << 40, root);
}

void Trie::erase_number(ll number)
{
	erase_recursive(number, (ll)1 << 40, root);
}

ll Trie::largest_xor(ll number)
{
	ll number_to_xor = 0;
	TrieNode* current_node = root;
	ll mask;
	for (mask = (ll)1 << 40; mask > 1; mask >>= 1)
	{
		bool current_bit = mask & number;
		if (current_node->children[!current_bit] != nullptr)
		{
			current_node = current_node->children[!current_bit];
			number_to_xor |= (!current_bit);
		}
		else
		{
			current_node = current_node->children[current_bit];
			number_to_xor |= current_bit;
		}
		number_to_xor <<= 1;
	}
	bool current_bit = mask & number;
	if (current_node->children[!current_bit] != nullptr)
	{
		number_to_xor |= (!current_bit);
	}
	else
	{
		number_to_xor |= current_bit;
	}
	return number ^ number_to_xor;
}

bool Trie::erase_recursive(ll number, ll mask, TrieNode* current_node)
{
	current_node->subtree_size--;
	if (mask >= 1)
	{
		bool current_bit = number & mask;
		if (erase_recursive(number, mask >> 1,current_node->children[current_bit]))
		{
			current_node->children[current_bit] = nullptr;
		}
	}
	return current_node->subtree_size == 0;
}

void Trie::insert_recursive(ll number, ll mask, TrieNode* current_node)
{
	current_node->subtree_size++;
	if (mask >= 1)
	{
		bool current_bit = number & mask;
		if (current_node->children[current_bit] == nullptr)
		{
			current_node->children[current_bit] = new TrieNode();
		}
		insert_recursive(number, mask >> 1, current_node->children[current_bit]);
	}
}
