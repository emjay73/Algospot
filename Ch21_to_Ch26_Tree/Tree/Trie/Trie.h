#pragma once

#include <cstring>
// number of upper case alphabet
const int ALPHABETS = 26;

int inchar_2_number(char ch) { return ch - 'A' };

// single node of trie
struct TrieNode {

	TrieNode() : terminal(false)
	{
		memset(children, 0, sizeof(children));
	}

	~TrieNode() 
	{
		for (int i = 0; i < ALPHABETS; ++i)
			if (children[i])
				delete children[i];
	}

	//insert key to this node 
	void insert(const char * key)
	{
		// end of string
		if (*key == 0)
			terminal = true;
		else
		{
			int child_idx = inchar_2_number(*key);

			// if it's first, generate it
			if (children[child_idx] == NULL)
				children[child_idx] = new TrieNode();

			children[child_idx]->insert(key + 1);
		}

	}

	// find node with key
	// if it does not exist, return NULL
	TrieNode * find(const char *key)
	{
		if (*key == 0) return this;
		int child_idx = inchar_2_number(*key);
		if (children[child_idx] == NULL) return NULL;
		return children[child_idx]->find(key + 1);
	}

	TrieNode* children[ALPHABETS];

	// terminal node?
	bool terminal;

	
};