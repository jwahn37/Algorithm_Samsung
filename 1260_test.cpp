#include<iostream>
#include<vector>

using namespace std;

#define MAX_N (100)
#define MAX_SM (20)
#define MAX_INF (987654321)

typedef struct ele{int r,c;}ELE;

int che_map[MAX_N][MAX_N];
int N;
vector<ELE> matrix;
vector<ELE> m[2][MAX_N][MAX_N];
//vector<ELE> m[MAX_SM+1][MAX_N][MAX_N];
vector<ELE> matrix_ordered;
int min_cnt;

void init();
int solve();
void find_matrix(int I, int J);
void order_matrix();
void min_mul(int N, int mul_cnt);

void print_1();
void print_2();

int main()
{
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N;
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
				cin>>che_map[i][j];
		}
		cout<<"#"<<t<<" "<<solve()<<endl;
	}
}

int solve()
{
	//초기화
	init();
	//1. 행렬 추출하기
	/*
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(che_map[i][j]!=0)
			{
				find_matrix(i,j);
			}
		}
	}
	*/
	ELE mat_new;
	for(int i=1; i<=MAX_SM; i++)
	{
		mat_new.r = i;
		mat_new.c = i+1;
		matrix.push_back(mat_new);
	}
	

	//print_1();
	//2. 행렬 ordering (금속막대문제)
	order_matrix();
	
	//print_2();
	//3. 최소 원소 곱셈 수 출력하기
	cout<<matrix_ordered.size()<<endl;
	min_mul(matrix_ordered.size(), 0); 

	return min_cnt;
}

void init()
{
	matrix.clear();
	for(int t=0; t<2; t++)
	{
		for(int r=0; r<MAX_N; r++)
		{
			for(int c=0; c<MAX_N; c++)
				m[t][r][c].clear();
		}
	}
	matrix_ordered.clear();
	min_cnt = MAX_INF;

}

void find_matrix(int I, int J)
{
	int i,j;
	ELE mat_new; 
	for(i=I; i<N; i++)
	{
		j=J;
		if(che_map[i][j]==0)	break;
		for(; j<N; j++)
		{
			if(che_map[i][j]==0)	break;
			che_map[i][j]=0;
		}
		mat_new.c = j-J;
	}
	mat_new.r = i-I;

	matrix.push_back(mat_new);
}

//Refer to 금속막대 문제
void order_matrix()
{
	//DP를 이용
//	vector<ELE> m[MAX_SM+1][MAX_N][MAX_N];
	ELE ele_new;
	//초기화 (t=1)
	for(int i=0; i<matrix.size(); i++)
	{
		ele_new.r = matrix[i].r;
		ele_new.c = matrix[i].c;
		m[1][ele_new.r][ele_new.c].push_back(ele_new);
	}
	
	
	//DP
	for(int t=2; t<=matrix.size(); t++)
	{
		for(int r=0; r<MAX_N; r++)
		{
			for(int c=0; c<MAX_N; c++)
			{
				unsigned int max_v;
				max_v = m[(t-1)%2][r][c].size();

				for(int k=0; k<MAX_N; k++)
				{
					if((m[(t-1)%2][r][k].size()>0) && (m[(t-1)%2][k][c].size()>0)&&(max_v < m[(t-1)%2][r][k].size() + m[(t-1)%2][k][c].size()))
					{
						max_v = m[(t-1)%2][r][k].size() + m[(t-1)%2][k][c].size();
						//cout<<r<<" "<<c<<" "<<k<<" "<<max_v<<endl;
						m[t%2][r][c] = m[(t-1)%2][r][k];
						m[t%2][r][c].insert(m[t%2][r][c].end(), m[(t-1)%2][k][c].begin(), m[(t-1)%2][k][c].end());
					}
				}
			}
		}
	}
	
	
	//최대값 추출
	for(int r=0; r<MAX_N; r++)
	{
		for(int c=0; c<MAX_N; c++)
		{
			int t = matrix.size();
			if(m[t%2][r][c].size() == matrix.size())
				matrix_ordered = m[t%2][r][c];
		}
	}
	
}

void min_mul(int N, int mul_cnt)
{
	if(N<=1)
	{
		if(min_cnt > mul_cnt)	min_cnt = mul_cnt;
		return;
	}
	else{
		for(int idx=0; idx<N-1; idx++)
		{
			vector<ELE> tp = matrix_ordered;
			ELE ele_new;

			mul_cnt += matrix_ordered[idx].r * matrix_ordered[idx].c * matrix_ordered[idx+1].c;
			ele_new.r = matrix_ordered[idx].r;
			ele_new.c = matrix_ordered[idx+1].c;
			
			matrix_ordered.erase(matrix_ordered.begin()+idx, matrix_ordered.begin()+idx+2);
			matrix_ordered.insert(matrix_ordered.begin()+idx, ele_new);

			min_mul(N-1, mul_cnt);

			matrix_ordered = tp;
		}
	}
	return;
}

void print_1()
{
	for(int i=0; i<matrix.size(); i++)
	{
		cout<<matrix[i].r<<" "<<matrix[i].c<<endl;
	}

}

void print_2()
{
	for(int i=0; i<matrix_ordered.size(); i++)
	{
		cout<<matrix_ordered[i].r<<" "<<matrix_ordered[i].c<<endl;
	}
}
