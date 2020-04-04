#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;

#define MAX_N (500)

int N;
string s1, s2;
int m[MAX_N][MAX_N];

double solve();
void init();

int main()
{
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N;
		cin>>s1>>s2;
		//cout<<"#"<<t<<" "<<solve()<<endl;
		printf("#%d %.2lf\n", t, solve());
	}
}

double solve()
{
	double res;
	init();

	//DP init
	for(int i=0; i<N; i++)
	{
		if(s1[i] == s2[0])
		{
			for(int j=i; j<N; j++)
				m[j][0] = 1;
			break;
		}
	}
	for(int i=0; i<N; i++)
	{
		if(s2[i] == s1[0])
		{
			for(int j=i; j<N; j++)
				m[0][j] = 1;
			break;
		}
	}
/*
   for(int i=0; i<N; i++)
		cout<<m[i][0]<<" ";
	cout<<endl;
	for(int i=0; i<N; i++)
		cout<<m[0][i]<<" ";
	cout<<endl;
*/
	//DP
	for(int i=1; i<N; i++)
	{
		for(int j=1; j<N; j++)
		{
			if(s1[i] == s2[j])	m[i][j] = m[i-1][j-1]+1;
			else				m[i][j] = max(m[i-1][j], m[i][j-1]);
		}
	}
//	cout<<m[N-1][N-1]<<endl;
	res = ((double)m[N-1][N-1] / (double)N )* 100;
	return res;

}

void init()
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
			m[i][j] = 0;
	}
}
