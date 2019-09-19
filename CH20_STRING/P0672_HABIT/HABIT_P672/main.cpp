#include <iostream>
#include <string>
#include "SuffixArray.h"
using namespace std;

int longestHabit(int k, const string &state)
{
	auto sufarray = getSuffixArray(state);

	int ret = 0;

	for (int i = 0; i+k <= state.size(); ++i)
	{
		ret = max(ret, commonPrefix(state, sufarray[i], sufarray[i + k - 1]));		
	}
	return ret;
}

int main()
{
	int nCases, k;
	string state;
	cin >> nCases;

	while (nCases--)
	{
		cin >> k;
		cin >> state;
		
		cout << longestHabit(k, state) << endl;

	
	}
}