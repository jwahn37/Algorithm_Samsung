#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N (100)
typedef struct ele{
	int row, col;
}ELE;

bool comp(ELE a, ELE b)
{
	if(a.row*a.col < b.row*b.col)	return true;
	else if((a.row*a.col == b.row*b.col) && (a.row <= b.row))	return true;
	else	return false;
}

int N;
int matrix[MAX_N][MAX_N];
vector<ELE> ans;

void solve();
void init();
void find_ans(const ELE m);

int main()
{
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N;
		for(int r=0; r<N; r++)
		{
			for(int c=0; c<N; c++)
				cin>>matrix[r][c];
		}
		solve();
		cout<<"#"<<t<<" "<<ans.size()<<" ";
		for(int i=0; i<ans.size(); i++)
		{
			cout<<ans[i].row<<" "<<ans[i].col<<" ";
		}
		cout<<endl;
	}
}

void solve()
{
	ELE cur;

	init();
	
	for(int r=0; r<N; r++)
	{
		for(int c=0; c<N; c++)
		{
			if(matrix[r][c]==0)	continue;
			else{
				cur.row = r, cur.col = c;
				find_ans(cur);
			}
		}
	}
	sort(ans.begin(), ans.end(), comp);

}

void init()
{
	ans.resize(0);
}

void find_ans(const ELE m)
{
	int r, c;
	ELE ans_node;
	ans_node.row = 0;
	ans_node.col = 0;

	for(r=m.row; r<N; r++)
	{
		if(matrix[r][m.col]==0)	break;

		for(c=m.col; c<N; c++)
		{
			if(matrix[r][c]!=0)
			{
				matrix[r][c]=0;
			}
			else{
				break;
			}
		}
	}
	ans_node.row = r - m.row;
	ans_node.col = c - m.col;
	ans.push_back(ans_node);
}
