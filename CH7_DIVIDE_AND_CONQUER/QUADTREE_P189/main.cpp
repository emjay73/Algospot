#include <iostream>
#include <string>

using namespace std;

string instr;

string rev(string::iterator &it)
{
	char c = *it;

	if(c != 'x')
		return string(1, c);
	
	string tl = rev(++it);
	string tr = rev(++it);
	string bl = rev(++it);
	string br = rev(++it);


	return string("x") + bl + br + tl + tr;

}

int main ()
{
	int C;
	cin >> C;

	while(C--)
	{
		cin >> instr;
		string::iterator it = instr.begin();
		cout << rev(it) << endl;
	}
}
