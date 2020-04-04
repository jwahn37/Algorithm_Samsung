#include<iostream>
using namespace std;

int nCr(int n, int r);

int main()
{
	cout<<nCr(5,2)<<endl;
}

int nCr(int n, int r)
{
	if(r==0)	return 1;
	if(n==r)	return 1;
	else
		return nCr(n-1, r) + nCr(n-1, r-1);
}
