// Fenwick tree == binary indexed tree
// compute range sum of arr
// every computation == log(n)
// compared to partial sum, it is advantegeous in updating value of arr

#pragma once
#include <vector>
using namespace std;

struct FenwickTree {
	// it's like.. root at the end..
	// this tree saves the range sum that ends at index position
	// starting position : erase last bit of position
	vector<int> tree; 

	FenwickTree(int n) : tree(n + 1, 0) {}

	// when val is added to arr[pos] ,
	// update tree value
	// positons to be updated == add last bit to the following position
	void add_val(int pos, int val)
	{
		// 0 based position --> 1 based position
		++pos;
		int ret = 0;
		while (pos < tree.size())
		{
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}

	// compute partial(accum) sum
	// from arr[0] to arr[pos]
	int partial_sum(int pos)
	{
		// 0 based position --> 1 based position
		++pos;
		int ret = 0;
		while (pos > 0)
		{
			ret += tree[pos];

			// find next range (ends at pos)
			pos &= (pos - 1);

		}
		return ret;

	}

	

};

