#include<iostream>

using namespace std;

int T;
int N, M;
char code_map[50][100];
const char code_bin[10][7]= { {'0','0','0','1','1','0','1'}, //0
						{'0','0','1','1','0','0','1'}, //1
						{'0','0','1','0','0','1','1'}, //2
						{'0','1','1','1','1','0','1'}, //3
						{'0','1','0','0','0','1','1'}, //4
						{'0','1','1','0','0','0','1'}, //5
						{'0','1','0','1','1','1','1'}, //6
						{'0','1','1','1','0','1','1'}, //7
						{'0','1','1','0','1','1','1'}, //8
						{'0','0','0','1','0','1','1'} };

int code_val[10];

void init_codemap();
void init_codeval();
int solve();
char can_be_code(const int h, const int w);
int extract_code(const int h, int w);

//1. 코드는 모듈화시켜서 보기 좋게 -> 검토할때 효율적

int main()
{
	int t;
	int h,w;
	cin>>T;
	for(t=1; t<=T; t++)
	{
		//초기화
		init_codemap();

		cin>>N>>M;
		for(h=0; h<N; h++)
		{
			for(w=0; w<M; w++)
			{
				cin>>code_map[h][w];
			//	cout<<code_map[h][w];
			}
		}
/*
		for(h=0; h<N; h++)
		{
			for(w=0; w<M; w++)
			{
				//cin>>code_map[h][w];
				cout<<code_map[h][w];
			}
			cout<<endl;
		}
		*/
		cout<<"#"<<t<<" "<<solve()<<endl;
	}
}

int solve()
{
	int h,w;
	int res;

	//0. 초기화
	//code_val
	init_codeval();

	//1. 전탐색
	for(h=0; h<N; h++)
	{
		for(w=0; w<M; w++)
		{
		//	cout<<"("<<h<<","<<w<<")"<<endl;
			res=0;
			//2.암호코드가 존재할 가능성 여부 체크
			if(can_be_code(h, w))
			{

				//cout<<"("<<h<<","<<w<<")"<<endl;
				//3. 코드 탐색하며 암호코드 추출하기
				res=extract_code(h, w);
				if(res != 0)	return res;
			}
		}
	}
	return 0;
}

char can_be_code(const int h, const int w)
{
	if(w+7*8>=M)	return 0;
	if(code_map[h][w+1]=='1')	return 1;
	if(code_map[h][w+2]=='1')	return 1;
	if(code_map[h][w+3]=='1')	return 1;
	
	return 0;
}

int extract_code(const int h, int w)
{
	int code_idx;
	int v,i;
	int matched;
	int not_code=0;
	int check_val=0;
	int res=0;

	for(code_idx=0; code_idx<8; w+=7, code_idx++)
	{
		not_code=1;
		for(v=0; v<=9; v++)
		{
			matched=1;
			for(i=0; i<7; i++)
			{
				if(code_bin[v][i]!=code_map[h][w+i])
				{
					matched=0;
					break;
				}
			}
			if(matched)
			{
				not_code=0;
				code_val[code_idx]=v;
				break;
			}
		}
		if(not_code)
		{
			return 0;
		}	
	}
	
	for(code_idx=0; code_idx<8; code_idx++)
	{
		//cout<<"DEBUG: "<<code_val[code_idx]<<endl;
		if(((code_idx+1)&1)==1)
		{
			check_val += code_val[code_idx]*3;
			res += code_val[code_idx];
		}
		else if(((code_idx+1)&1)==0)
		{
			check_val += code_val[code_idx];
			res += code_val[code_idx];
		}
	}

	if(check_val%10==0)
		return res;
	
	return 0;	
}

void init_codemap()
{
	int h,w;
	for(h=0; h<50; h++)
	{
		for(w=0; w<100; w++)
		{
			code_map[h][w]=0;
		}
	}
}

void init_codeval()
{
	int i;
	for(i=0; i<10; i++)
		code_val[i]=0;
}
