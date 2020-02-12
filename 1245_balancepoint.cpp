#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

#define MAX_N (10)
#define MIN_DIFF (0.000000000001)

int d[MAX_N], m[MAX_N];
int N;
double x[MAX_N];

void init();
void  solve();
double binsearchX(double min, double max, int index);

int main()
{
	int T;
	scanf("%d", &T);
	for(int t=1; t<=T; t++)
	{
		init();
		scanf("%d", &N);
		for(int i=0; i<N; i++)
			scanf("%d", &d[i]);
		for(int i=0; i<N; i++)
			scanf("%d", &m[i]);

		solve();
		printf("#%d ", t);
		for(int i=0; i<N-1; i++)
			printf("%.10lf ", x[i]);
		printf("\n");
	}

}

void init()
{
	for(int i=0; i<MAX_N; i++)
		x[i] = d[i] = m[i] = 0;
}

void solve()
{
	for(int i=0; i<N-1; i++)
	{
		x[i] = binsearchX(d[i], d[i+1], i);	
	}
}

double binsearchX(double min, double max, int index)
{
	if(max-min <= MIN_DIFF)	return min;
	double ans;
	double f_l = 0.0;
	double f_r = 0.0;
	double mid = (min + max) / 2.0;
	for(int i=0; i<=index; i++)
	{
		f_l += (double)m[i] / ((mid-(double)d[i]) * (mid-(double)d[i]));
	}
	for(int i=index+1; i<N; i++)
	{
		f_r += (double)m[i] / ((mid-(double)d[i]) * (mid-(double)d[i]));
	}
	
	if(f_l < f_r)		ans=binsearchX(min, mid, index);
	else if(f_l > f_r)	ans=binsearchX(mid, max, index);
	else				ans=binsearchX(mid, mid, index);
	return ans;
}

