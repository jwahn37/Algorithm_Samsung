#include<iostream>
#include<vector>
using namespace std;

#define MAX_W (30)
#define MAX_N (20)

typedef struct ms{ 
	int ws, wa;
}MS;

int N; //막대의 갯수
vector<MS> m[MAX_N+1][MAX_W+1][MAX_W+1];//[시도수][숫나사굵기][암나사굵기]

void init_m();
void solve(vector<MS> &ans);

int main()
{
	int T;
	MS ms;
	//int ws, wa;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		vector<MS> ans;
		cin>>N;
		init_m();
		for(int i=0; i<N; i++)
		{
			cin>>ms.ws>>ms.wa;
			m[1][ms.ws][ms.wa].push_back(ms);
		//	cout<<"print "<<ms.ws<<" "<<ms.wa<<" "<<m[1][ms.ws][ms.wa].size()<<endl;
		}
		solve(ans);
		cout<<"#"<<t<<" ";
		for(int i=0; i<ans.size(); i++)
		{
			cout<<ans[i].ws<<" "<<ans[i].wa<<" ";
		}
		cout<<endl;
	}
}


void solve(vector<MS>& ans)
{
	for(int t=2; t<=N; t++)
	{
		for(int ws=1; ws<=MAX_W; ws++)
		{
			for(int wa=1; wa<=MAX_W; wa++)
			{
				vector<MS> max_ms = m[t-1][ws][wa];
				for(int k=1; k<=MAX_W; k++)
				{	
					if((m[t-1][ws][k].size() > 0 )&& (m[t-1][k][wa].size() > 0) && (max_ms.size() < m[t-1][ws][k].size() + m[t-1][k][wa].size()))
					{
					max_ms = m[t-1][ws][k];
						max_ms.insert(max_ms.end(), m[t-1][k][wa].begin(), m[t-1][k][wa].end());
					}
				}
				m[t][ws][wa] = max_ms;
			//	if(t==N && m[N][ws][wa].size()>0)	cout<<"max_ms: "<<m[N][ws][wa].size()<<" "<<ws<<" "<<wa<<endl;
			}		
		}
	}
	
	//t==N이면 최대 사이즈를 뽑아서 리턴하라
	int max_ws, max_wa, max_v;
	max_v = -1;
	for(int ws=1; ws<=MAX_W; ws++)
	{
		for(int wa=1; wa<=MAX_W; wa++)
		{
			/*
			if(m[N][ws][wa].size()>0)	
			{
				cout<<"2max_ms: "<<m[N][ws][wa].size()<<" "<<ws<<" "<<wa<<endl;
				cout<<max_v<<" "<<m[N][ws][wa].size()<<endl;
			}
			*/
			if(max_v < (int)m[N][ws][wa].size()) //int끼리 비교해야됨... 중요,,
			{
				max_v = m[N][ws][wa].size();
				max_wa = wa;
				max_ws = ws;
				//cout<<max_v<<endl;
			}
		}
	}
	ans = m[N][max_ws][max_wa];
	//cout<<ans.size()<<endl;
	
}


void init_m()
{
	//m 초기화
	for(int t=0; t<=MAX_N; t++)
	{
		for(int ws=0; ws<=MAX_W; ws++)
		{
			for(int wa=0; wa<=MAX_W; wa++)
				//m[t][ws][wa] = 0;
				m[t][ws][wa].resize(0);
		}
	}

}
