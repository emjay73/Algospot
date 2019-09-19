#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct TreeNode {
	string label;
	TreeNode* parent;
	vector<TreeNode*> children;
};


void print_tree_preorder(TreeNode* root) 
{
	cout << root->label << endl;
	for (int c = 0; c < root->children.size(); ++c)
		print_tree_preorder(root->children[c]);	
}

int height(TreeNode* root)
{
	int h = 0; 

	for (int c = 0; c < root->children.size(); ++c)
	{
		h = max(h, 1+height(root->children[c]));
	}
	return h;
}