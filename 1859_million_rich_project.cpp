#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//#define MAX_DAY 1000000

typedef struct{
	int day;
	long long int price;
	long long int amount_before;
}DAY_PRICE;

bool comp(DAY_PRICE a, DAY_PRICE b) {return a.price > b.price;}

int N;
int testcase;
//DAY_PREICE day_price[MAX_DAY];
vector<DAY_PRICE> day_price;

long long int solve();

int main()
{
	cin>>testcase;
	for(int tc=1; tc<=testcase; tc++)
	{
		long long int amount_before=0;
		day_price.resize(0);

		cin>>N;

		for(int i=1; i<=N; i++)
		{
			DAY_PRICE dp;
			dp.day=i;
			cin>>dp.price;
			dp.amount_before = amount_before;
			day_price.push_back(dp);
	
			//전날까지 합한 모든 가격
			amount_before += dp.price;
	
		}
		cout<<"#"<<tc<<" "<<solve()<<endl;
	}
}

/*
	sorting한 녀석에서 가장 비싼놈 기준으로 돌아야함.
	그런데 last day의 index를 기억하지 않으면 곤란스..
	왜냐면 last day로 접근해야하니까..
*/

long long int solve()
{
	int last_day=0;
	int last_day_i=0;
	
	sort(day_price.begin(), day_price.end(), comp);

	//test
/*
	cout<<day_price.size()<<endl;
	for(int i=0; i<day_price.size(); i++)
	{
		cout<<day_price[i].price<<" ";
	}
	cout<<endl;
*/
	long long int profit=0;
	long long int tp;
	for(int i=0; i<day_price.size(); i++)
	{
		if(day_price[i].day > last_day)
		{
			tp = day_price[i].price * ( day_price[i].day - last_day -1 );
			if(i==0) //첫번째 indexing떄는... 수식이다름. 이전걸 신경쓸 필요가 없다.
				tp -= day_price[i].amount_before;
			else
				tp -= day_price[i].amount_before - day_price[last_day_i].amount_before - day_price[last_day_i].price;
			profit += tp;
			last_day = day_price[i].day;
			last_day_i = i;
		}
	}
	return profit;
}
