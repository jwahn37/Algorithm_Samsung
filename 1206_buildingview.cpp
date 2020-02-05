#include<iostream>
using namespace std;

#define MAX_BD (1000+4)
#define MAX_HT 255
#define GAP 2

int buildings[MAX_BD][MAX_HT];
int N;

int main()
{
	int testcase = 10;	
	int tc, i, j;
	int height;

	for(tc=1; tc<=10; tc++)
	{
		//1. 초기화
		for(i=0; i<MAX_BD; i++)
		{
			for(j=0; j<MAX_HT; j++)
				buildings[i][j]=0;
		}

		//2. 입력받아서 전처리
		cin>>N;
		for(i=GAP; i<N+GAP; i++)
		{
			cin>>height;
			for(j=0; j<height; j++)
				buildings[i][j]=1;
		}
	
		//3. 조망권 세대 세기
		int jomang=0;
		for(i=GAP; i<N+GAP; i++)
		{
			for(j=0; j<MAX_HT; j++)
			{
				if(buildings[i][j]==1 &&\
						buildings[i-1][j] == 0 &&\
						buildings[i-2][j] == 0 &&\
						buildings[i+1][j] == 0 &&\
						buildings[i+2][j] == 0 )
					jomang++;
			}
		}

		//4. 출력
		cout<<"#"<<tc<<" "<<jomang<<endl;
	}
}
