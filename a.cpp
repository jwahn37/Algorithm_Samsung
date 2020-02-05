#include<iostream>
using namespace std;

int main()
{
	int v=6;
	cout<<v<<endl;
	for(int i=0; i<4; i++)
		cout<< (((v>>(3-i)) & 1) == 1)<<endl;
}

