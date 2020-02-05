#include<iostream>

using namespace std;

//1.1 자료구조 
#define MAX_ROW 20
#define MAX_COL 20
enum{RT, DW, LT, UP };

//int dir[4][2] = { {0,1}, {1,0}, {0, -1}, {-1, 0} };//오하좌
char HS[MAX_ROW][MAX_COL];
int path[MAX_ROW][MAX_COL][16][4];
int testcase;
int R, C;

bool solve();
bool exec_hs(int i, int j, int val, int cdir);

int main()
{
	cin>>testcase;
	for(int tc=1; tc<=testcase; tc++)
	{
		cin>>R>>C;
		for(int i=0; i<R; i++)
		{
			for(int j=0; j<C; j++)
				cin>>HS[i][j];
		}
		bool res = solve();
		if(res)	cout<<"#"<<tc<<" "<<"YES"<<endl;
		if(!res)	cout<<"#"<<tc<<" "<<"NO"<<endl;
	}
}

bool solve()
{
	int val = 0;
	int cdir = RT;
	//초기화
	for(int r=0; r<MAX_ROW; r++)
	{
		for (int c=0; c<MAX_COL; c++)
		{
			for(int v=0; v<16; v++)
			{
				for(int d=0; d<4; d++)
					path[r][c][v][d]=0;
			}
		}
	}

	return exec_hs(0, 0, val, cdir);
}	

bool exec_hs(int i, int j, int val, int cdir)
{
	while(1)
	{
		//같은 조건이 반복되면, 희망이 없다는 의미.
		if(path[i][j][val][cdir]==1)	return false;

		path[i][j][val][cdir]=1;

		switch(HS[i][j])
		{
			case '>' :	cdir = RT;	break;
			case '<' :	cdir = LT;	break;
			case '^' :	cdir = UP;	break;
			case 'v' :	cdir = DW;	break;
	
			case '_' :	cdir = (val == 0 )? RT : LT;	break;
			case '|' :  cdir = (val == 0 )? DW : UP;	break;

			case '?' :	
						return exec_hs(i, (j+1)%C, val, RT) | \
								exec_hs(i, (j+C-1)%C, val, LT) | \
								exec_hs((i+1)%R, j, val, DW) | \
								exec_hs((i+R-1)%R, j, val, UP);

			case '.' :	break;
			case '@' :	return true;
			case '0' : val = 0;	break;
			case '1' : val = 1;	break;
			case '2' : val = 2; break;
			case '3' : val = 3; break;
			case '4' : val = 4; break;
			case '5' : val = 5; break;
			case '6' : val = 6; break;
			case '7' : val = 7; break;
			case '8' : val = 8; break;
			case '9' : val = 9; break;

			case '+' : val = (val+1)%16;	break;
			case '-' : val = (val+15)%16;	break;
		}
		
		switch (cdir){
			case RT : j=(j+1)%C; break;
			case LT : j=(j+C-1)%C; break;
			case UP : i=(i+R-1)%R; break;
			case DW : i=(i+1)%R; break;
		}
		//이동한다.
	/*	i += dir[cdir][0];
		j += dir[cdir][1];
		//범위 체크
		if (i<0)	i=C-1;
		if (i>=R)	i=0;
		if (j<0)	j=R-1;
		if (j>=C)	j=0;
*/
	}
}
