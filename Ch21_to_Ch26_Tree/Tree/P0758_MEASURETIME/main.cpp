#define _CRT_SECURE_NO_WARNINGS
#define MAX_ARR_SIZE 50000
#define MAX_ARR_ELEM 1000000

#include <iostream>
#include <vector>
#include "../FenwickTree/FenwickTree.h"
using namespace std;


vector<int> A;

long long count_moves()
{
	// for each element,
	// init arr is zeros
	FenwickTree ftree(MAX_ARR_ELEM);

	long long ret = 0;

	// considering arr[0~i],
	for (int i = 0; i < A.size(); ++i)
	{
		// cnt elements bigger than A[i]
		ret += ftree.partial_sum(MAX_ARR_ELEM - 1) - ftree.partial_sum(A[i]);

		// count element A[i]
		ftree.add_val(A[i], 1);
	}

	return ret;
}

int main()
{
	int C, N;
	scanf("%d\n", &C);

	while (C--)
	{

		scanf("%d\n", &N);
		A.clear();
		A.resize(N);
		for (int n = 0; n < N; ++n)
			scanf("%d", &(A[n]));

		printf("%lld\n", count_moves());


	}
}