#include<iostream>
using namespace std;

int solve();

int main()
{
	int tc, tp;
	cin>>tc;
	for(int i=1; i<=tc; i++)
	{
		cin>>tp;
		cout<<"#"<<i<<" "<<solve()<<endl;
	}
}

int solve()
{
	int score[101];
	int i;
	
	//1. 초기화
	for(i=0; i<=100; i++)
		score[i]=0;
	//2. 학생 입력받기
	for(i=0; i<1000; i++)
	{
		int cur_score;
		cin>>cur_score;
		score[cur_score]++;
	}

	//3. 가장 높은 스코어 뽑기
	int max=-1;
	int max_score;
	for(i=100; i>=0; i--)
	{
		if(score[i]>max)
		{
			max=score[i];
			max_score=i;
		}
	}
	
	return max_score;
}
