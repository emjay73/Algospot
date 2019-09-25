#pragma once
// priority of parents should be higher than that of children

#include <random>
#include <utility>

using namespace std;

typedef int KeyType;
typedef struct Node Node;
typedef pair<Node*, Node*> NodePair;
Node* treap_insert(Node * root, Node* node);
NodePair treap_split(Node*root, KeyType key);
Node* treap_erase(Node* root, KeyType key);
Node* treap_merge(Node* rootL, Node* rootR);
Node * treap_kth(Node * root, int k);

struct Node {

	// constructor
	Node(const KeyType& _key) 
		: key(_key),
		  priority(rand()),
		  size(1),
		  left(NULL),
		  right(NULL){}
	
	// update size of tree
	void calcSize()
	{
		size = 1;
		if (left) size += left->size;
		if (right)size += right->size;
	}

	void setLeft(Node* newleft) { left = newleft; }
	void setRight(Node* newright) { right = newright; }

	// node value
	KeyType key;

	// random priority
	int priority;

	// size of subtree (root == this node)
	// number of nodes
	int size;

	// childrens
	Node *left, *right;

	

};

// return root node
Node* treap_insert(Node * root, Node* node)
{
	if (root == NULL) return node;

	if (root->priority < node->priority)
	{
		NodePair splitted = treap_split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);

		node->calcSize();
		return node;
	}
	else if (node->key < root->key)
		root->setLeft(treap_insert(root->left, node));
	else
		root->setRight(treap_insert(root->right, node));
	root->calcSize();
	return root;

}

// node with key has higher priority
// so, node is new root after splits
NodePair treap_split (Node*root, KeyType key)
{
	if (root == NULL) return NodePair(NULL, NULL);

	if (root->key < key) {
		NodePair rs = treap_split(root->right, key);
		root->setRight(rs.first);
		root->calcSize();
		return NodePair(root, rs.second);
	}
	else
	{
		NodePair ls = treap_split(root->left, key);
		root->setLeft(ls.second);
		root->calcSize();
		return NodePair(ls.first, root);
	}
}

// from tree(with root), erase key and return tree root
Node* treap_erase(Node* root, KeyType key)
{
	if (root == NULL) return root;

	// erase root
	if (root->key == key)
	{
		Node* ret = treap_merge(root->left, root->right);
		delete root;

		if(ret != NULL)	ret->calcSize();
		return ret;
	}
	
	else if (root->key < key)
	{
		root->setRight(treap_erase(root->right, key));
		root->calcSize();
		return root;
	}
	
	else
	{
		root->setLeft(treap_erase(root->left, key));
		root->calcSize();
		return root;
	}
}

// rootL : left subtree
// rootR : right subtree
Node* treap_merge(Node* rootL, Node* rootR)
{
	if (rootL == NULL) return rootR;
	if (rootR == NULL) return rootL;

	if (rootL->priority < rootR->priority)
	{
		rootR->setLeft(treap_merge(rootL, rootR->left));
		rootR->calcSize();
		return rootR;
	}
	else
	{
		rootL->setRight(treap_merge(rootL->right, rootR));
		rootL->calcSize();
		return rootL;
	}
}

// find node the kth key value
Node * treap_kth(Node * root, int k)
{
	int left_size = 0;
	if (root->left != NULL) left_size = root->left->size;

	if (k <= left_size) return treap_kth(root->left, k);
	else if (k == left_size + 1) return root;
	else return treap_kth(root->right, k - left_size - 1);
}

int count_less_than(Node *root, KeyType key)
{
	if (root == NULL) return 0;
	if (root->key >= key) return count_less_than(root->left, key);
	int ls = root->left ? root->left->size : 0;
	return ls + 1 + count_less_than(root->right, key);
}