#pragma once
#include <vector>
#include <algorithm>

using namespace std;

struct Comparator {
	const vector<int> & group;
	int T;
	Comparator(const vector<int> & _group, int _T) : group(_group), T(_T) { }
	
	bool operator() (int a, int b) { 
		if (group[a] != group[b]) 
			return group[a] < group[b]; 
		return group[a + T] < group[b + T];
	}
};
// suffice in dictionary order
vector<int> getSuffixArray(const string &str)
{
	int strSize = str.size(), T = 1;
	vector<int> suffixArray(strSize);
	for (int i = 0; i < strSize; ++i) suffixArray[i] = i;

	vector<int> group(strSize + 1), newgroup(strSize + 1);
	for (int i = 0; i < strSize; ++i) group[i] = str[i]; 
	group[strSize] = -1; newgroup[strSize] = -1;
	

	

	while (T < strSize)
	{
		Comparator cmp(group, T);
		sort(suffixArray.begin(), suffixArray.end(), cmp);
		T *= 2;
		if (T >= strSize) break;

		//newgroup[strSize] = -1;
		newgroup[suffixArray[0]] = 0;

		for (int i = 1; i < strSize; ++i)
		{
			// dic order
			if (cmp(suffixArray[i - 1], suffixArray[i]))
				newgroup[suffixArray[i]] = newgroup[suffixArray[i - 1]] + 1;

			// same group
			else
				newgroup[suffixArray[i]] = newgroup[suffixArray[i - 1]];
		}
		group = newgroup;

		
	}
	return suffixArray;
}

// get max length of common prefix of
// s[i ...] and s[j ...]
int commonPrefix(const string & s, int i, int j)
{
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j])
	{
		++i, ++j, ++k;
	}
	return k;
}

int countSubstrings(const string&s)
{
	vector<int> sufarray = getSuffixArray(s);
	int cnt = 0;
	int n = s.size();

	for (int i = 0; i < sufarray.size(); ++i)
	{
		int cp = 0;
		if (i > 0) cp = commonPrefix(s, sufarray[i - 1], sufarray[i]);

		cnt += s.size() - sufarray[i]	// suffix length
				- cp;					//remove overlap
	}

	return cnt;
}
