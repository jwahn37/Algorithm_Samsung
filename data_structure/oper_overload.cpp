#include<iostream>
#include<vector>
#include<queue>
#include <functional>
using namespace std;

typedef struct opov{
	int a;
	int b;
	bool operator>(const struct opov t)const
	{
		return (a>t.a)? true : false;
	}
	bool operator<(const struct opov t)const
	{
		return (a<t.a)? false : true;
	}
}OPOV;

int main()
{
	OPOV x, y;
	x.a = 10, x.b = 20;
	y.a = 20, y.b = 10;
	
	cout<<(x<y)<<endl;

	priority_queue<OPOV, vector<OPOV>, greater <OPOV> > q;
	q.push(x);
	q.push(y);

	cout<<q.top().a<<" "<<q.top().b<<endl;

	return 0;
}	
