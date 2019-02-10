#include <iostream>
#include <vector>
#include "karatsuba_mod.h"
#include <string>

using namespace std;

int hugs(const string& members, const string & fans)
{
	
	int N = members.size(), M = fans.size();

	vector<int> A(N), B(M);

	for(int a = 0; a<N; ++a) 
	{		
		A[a] = (members[a] == 'M');
	}

	for(int b = 0; b<M; ++b) 
	{
		B[M-b-1] = (fans[b] == 'M');
	}

	vector<int> C = karatsuba(A, B);

	int cntHug = 0;
	for(int i=N-1; i<M; ++i)
	{
		if(C[i] == 0) ++cntHug;
	}
	return cntHug;

}
int main ()
{
	int C;
	cin >> C;
	cin.ignore();

	while(C--)
	{
		string M, F;
		getline(cin, M);
		getline(cin, F);

		cout << hugs(M, F) << endl;
	}
	
}
