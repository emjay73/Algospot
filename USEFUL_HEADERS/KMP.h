#pragma once

#include <vector>
#include <string>

using namespace std;

vector<int> kmpPartialMatch(const string &N)
{
	vector<int> partial(N.size(), 0);
	
	auto sizeN = N.size();
	int matched = 0;	// pre index

	// start from 1 (not to find N itself)
	for (int iN = 1; iN < sizeN; ++iN) // post index
	{
		
		while ((N[matched] != N[iN]) && matched)
			matched = partial[matched - 1];


		if (N[matched] == N[iN])
		{
			++matched;			
			partial[iN] = matched;
		}	
	}

	return partial;
}

vector<int> kmpSearch(const string &H, const string &N) // Haystack & Needle
{
	vector<int> matched_pos;

	auto partial = kmpPartialMatch(N);
	auto sizeH = H.size();
	auto sizeN = N.size();
	int matched = 0;

	for (int iH = 0; iH < sizeH; ++iH)
	{
		
		while ((N[matched] != H[iH]) && matched)
			matched = partial[matched - 1];		

		if (N[matched] == H[iH])
		{			
			++matched;

			if (matched == sizeN)
			{
				matched_pos.emplace_back(iH - sizeN + 1);
				matched = partial[sizeN - 1];
			}			
		}
		/*else
		{
			while (matched)			
				matched = partial[matched - 1];
			
		}*/
	}

	return matched_pos;
}