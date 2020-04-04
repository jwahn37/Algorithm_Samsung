#include<queue>
#include<vector>
#include<iostream>
using namespace std;

//priority_queue<int, greater<int> >pq;
priority_queue<int, vector<int>, greater<int> >pq;

int main()
{
	for(int i=0; i<10; i++)
		pq.push(i);
	cout<<pq.top()<<endl;
}
