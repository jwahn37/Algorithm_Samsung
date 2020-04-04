#include <iostream>
#include <queue>
using namespace std;

#define MAX_N (101)
#define INF (999999999)

typedef struct{	int i, j; }AXIS;

/*
https://2youngjae.tistory.com/82
이 풀이가 맞은건지 틀린건지 확인

   */
int T;
int road[MAX_N][MAX_N];
int N;
AXIS dir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };//우측 아래쪽 왼쪽 좌측 (시계방향)
int dist[MAX_N][MAX_N];
//int visited[MAX_N][MAX_N];

int solve();
void init();
bool is_road(AXIS loc);

int main()
{
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N;
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=N; j++)
			{
		//		road[i][j]=0;
		//		if(i!=0 && j!=0 && i!=N+1 && j!=N+1)
				char input;
				cin>>input;
				road[i][j] = input-'0';
			}
		}
		cout<<"#"<<t<<" "<<solve()<<endl;
	}
}

int solve()
{
/*
   BFS를 이용해 풀어봄 (dijkstra 이용 안함)
   */
	init();
	queue<AXIS> q;
	AXIS cur, next;
	AXIS S = {1, 1};
//	AXIS G = {N ,N};

	//초기 distance 결
	dist[S.i][S.j] = 0;
	q.push(S);

	while(!q.empty())
	{
		cur = q.front();
		q.pop();
		//dist[cur.i][cur.j] = min_dist(cur);

		for(int d=0; d<4; d++)
		{
			//next = cur + dir[d];
			next.i = cur.i + dir[d].i;
			next.j = cur.j + dir[d].j;
			//현재까지 알려진 distance보다 더 낮은 distance가 보이면 push
			if(is_road(next) && dist[next.i][next.j] > dist[cur.i][cur.j] + road[cur.i][cur.j])
			{
				dist[next.i][next.j] = dist[cur.i][cur.j] + road[cur.i][cur.j];
				q.push(next);
			}
		}
	}
	return dist[N][N];
}

void init()
{
	for(int i=0; i<=N+1; i++)
	{
		for(int j=0; j<=N+1; j++)
		{
			dist[i][j] = INF;
	//		visited[i][j] = 0;
		}
	}

}

bool is_road(AXIS loc)
{
	if(loc.i <= 0 || loc.i >N)	return false;
	if(loc.j <= 0 || loc.j >N)	return false;
	else	return true;
}
