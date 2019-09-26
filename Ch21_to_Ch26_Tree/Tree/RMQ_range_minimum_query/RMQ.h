#pragma once
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// range minimum query
struct RMQ {

	// input arr length
	int n;

	// min value of specific range
	// index : 1 2 3 4 5 6 => min => root
	// index : 1 2 3|4 5 6 => min min => child
	// index : 1|2 3|4|5 6 => min min min min => child
	// index :   2|3   5|6 => min min min min => child
	vector<int> range_min_tree;

	RMQ(const vector<int> & arr)
	{
		n = arr.size();
		range_min_tree.resize(4 * n, -1); // size upper limit.. why?
		init_range_min(arr, 0, n - 1, 1);
	}
		
	// O(log n)
	int query(int left, int right)
	{
		return query(left, right, 1, 0, n - 1);
	}

	// update range_min_tree when
	// arr[index] is updated with new_value
	int update(int index, int new_value)
	{
		return update(index, new_value, 1, 0, n-1);
	}

	// inner functions -------------------------------------------------------------------------------
	// find min([left, right]) and save it to range_min_tree[node_idx]
	// O(n)
	int init_range_min(const vector<int> & arr, int left, int right, int node_idx)
	{
		if (left == right)
			return range_min_tree[node_idx] = arr[left];
		int mid = (left + right) / 2;

		int left_min = init_range_min(arr, left, mid, node_idx * 2);		// left child
		int right_min = init_range_min(arr, mid + 1, right, node_idx * 2 + 1);	// right child

		return range_min_tree[node_idx] = min(left_min, right_min);
	}

	// find min of intersection between range1 and range2(represented by node_idx)
	int query(int target_range_left, int target_range_right, int node_idx, int node_range_left, int node_range_right)
	{
		//if there's no overlap, return MAX  (ignore)
		if (target_range_right < node_range_left || 
			target_range_left > node_range_right) return INT_MAX;
		
		// range1 includes range2 or
		// ranges are same
		if (target_range_right >= node_range_right && 
			target_range_left <= node_range_left) 
			return range_min_tree[node_idx];

		// split the range & solve & merge
		int mid = (node_range_left + node_range_right) / 2;
		return min(	query(target_range_left, target_range_right, node_idx * 2, node_range_left, mid),
					query(target_range_left, target_range_right, node_idx * 2 + 1, mid + 1, node_range_right));
	}

	// update range_min_tree[node_idx] 
	// if the range is related to index
	// and return range_min_tree[node_idx] 
	int update(int index, int new_value, int node_idx, int node_rangeL, int node_rangeR)
	{
		// index is not in [node_rangeL, node_rangeR]
		if (index < node_rangeL || index > node_rangeR) return range_min_tree[node_idx];

		// found leaf
		if (node_rangeL == node_rangeR) return range_min_tree[node_rangeL] = new_value;

		int mid = (node_rangeL + node_rangeR) / 2;

		return range_min_tree[index] = min(
			update(index, new_value, node_idx * 2, node_rangeL, mid),
			update(index, new_value, node_idx * 2 + 1, mid + 1, node_rangeR));

	}
};