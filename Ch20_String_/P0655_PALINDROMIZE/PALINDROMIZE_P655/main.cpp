#include "KMP.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
int maxOverlap(const string & post, const string &pre)
{
	auto partial = kmpPartialMatch(pre);
	int matched = 0;
	int postSize = post.size();
	for (int ip = 0; ip < postSize; ++ip)
	{		
		while ((pre[matched] != post[ip]) && matched)
		{
			matched = partial[matched - 1];
		}		

		if (pre[matched] == post[ip])
		{
			++matched;
			if (ip == postSize-1)
				return matched;
		}		
	}

	return 0;
}

int main()
{
	string input, input2;
	

	int nCases;
	cin >> nCases;
	while (nCases--)
	{
		cin >> input;
		input2 = input;
		reverse(input2.begin(), input2.end());
		cout << input.size() * 2 - maxOverlap(input, input2) << endl;
	}

}
