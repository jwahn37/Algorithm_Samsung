#include<iostream>
using namespace std;

typedef struct{ int x, y; }AXIS;

int main()
{
	AXIS dir = {1,2};
	cout<<dir.x<<dir.y<<endl;
	char a[10];
	for(int i=0; i<10; i++)
	{
		cin>>a[i];
	}
	for(int i=0; i<10; i++)
		cout<<a[i];
	cout<<endl;
}
