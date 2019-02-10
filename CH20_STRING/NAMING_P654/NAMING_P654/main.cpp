#include "KMP.h"

#include <iostream>
#include <algorithm>

vector<int> getPrefixSuffix(const string &s)
{
	auto partial = kmpPartialMatch(s);
	vector<int> output;

	int k = s.size();	

	while (k)
	{
		output.emplace_back(k);
		k = partial[k-1];		
	}

	return output;
}

int main()
{
	string father, mother, input;
	
	cin >> father >> mother;
	input = father + mother;
	
	auto cases = getPrefixSuffix(input);
	sort(cases.begin(), cases.end());
	for (auto c : cases)
	{
		cout << c << " ";
	}
}