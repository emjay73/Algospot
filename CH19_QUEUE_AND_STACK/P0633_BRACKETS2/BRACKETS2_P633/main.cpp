#include <iostream>
#include <string>
#include <stack>

int C;
using namespace std;

void MatchingSet(string input);

int main()
{
	
	string input;

	cin >> C;
	cin.ignore(100, '\n');
	while (C--)
	{
		
		getline(cin, input);

		MatchingSet(input);		
	}
}
void MatchingSet(string input)
{
	const string open_set("({[");
	const string close_set(")}]");

	stack<char> open_stack;
	char o;
	for (auto b : input)
	{		
		auto close_idx = close_set.find(b);

		if (close_idx == -1)
			open_stack.push(b);
		else
		{		
			if (open_stack.empty())
			{
				cout << "NO" << endl;
				return;
			}
				
			o = open_stack.top();
			open_stack.pop();
			if (open_set.find(o) != close_idx)
			{
				cout << "NO" << endl;
				return;
			}


		}
	}
	if (open_stack.empty())
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return;
	
}