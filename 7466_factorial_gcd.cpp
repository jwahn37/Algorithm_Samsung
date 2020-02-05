#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int testcase;
int N, K;
vector<int> soinsu;

int solve();
int eratos_sieve();
void soinsu_div(int n);

typedef struct{
	int mit;
	int jisu;
}PRIME;

class Eratosthenes_sieve{
	public:
		int get_eratosthenes_sieve();
		Eratosthenes_sieve(int max_n);
	private:
		int idx;
		int max_n;
		//bool sieve[];
		vector<bool> sieve;
};

Eratosthenes_sieve::Eratosthenes_sieve(int n)
{
	sieve.resize(n+1);
	for(int i=2; i<=n; i++)
		sieve[i]=true;
	sieve[0]=sieve[1]=false; //접근안함
	idx = 2;
	max_n = n;
}

int Eratosthenes_sieve::get_eratosthenes_sieve()
{
	int i,j;
	for(i=idx; i<=max_n; i++)
	{
		if(sieve[i]==true)
		{
			for(j=i; j<=max_n; j+=i)
			{
				sieve[j]=false;
			}
			idx = i + 1;	//다음 녀석 2였으면 3으로

			return i;
		}
	}
	return 0;	//없으면 0 리
}	

int main()
{
	cin>>testcase;
	for(int i=1; i<=testcase; i++)
	{
		cin>>N>>K;
		cout<<"#"<<i<<" "<<solve()<<endl;
	}
}

int solve()
{
	vector<PRIME> n_prime, k_prime;
	vector<PRIME>::iterator iter;
	//1. N의 소인수 분해.
	
	PRIME cur, cur2;
	//int cur_mit, int cur_jisu;
	//int loot_n = int(sqrt(N));	//double제거. 이전 최대 int만 뽑기.
	//Eratosthenes_sieve ES_N(N);
	
	//2. K의 소인수 분해
	//int loot_k = int(sqrt(K));
	//Eratosthenes_sieve ES_K(loot_k);
	int k = K;
	soinsu.resize(0);
	soinsu_div(K);
	sort(soinsu.begin(), soinsu.end());
	vector<int>::iterator iter2;
	//:PRIME cur;

	cur.mit = soinsu[0];
	cur.jisu=1;
	
	for(iter2=soinsu.begin()+1; iter2!=soinsu.end(); iter2++)
	{
		if(cur.mit == *iter2)
		{
			cur.jisu++;
		}
		else{
			k_prime.push_back(cur);
			//cout<<cur.mit<<" "<<cur.jisu<<endl;
			cur.jisu=1;
			cur.mit=*iter2;
		}
	}
	if(cur.jisu)
	{
	//	cout<<cur.mit<<" "<<cur.jisu<<endl;
		k_prime.push_back(cur);
	}

	//cout<<"K"<<endl;
	/*
	   while((cur.mit = ES_K.get_eratosthenes_sieve()))
	{
		cur.jisu=0;
		cur2.jisu=0;
		cur2.mit = K/cur.mit;
		while(k%cur.mit==0)
		{
			k=k/cur.mit;
			cur.jisu++;
		}
		while(k%cur2.mit==0)
		{
			k=k/cur2.mit;
			cur2.jisu++;
		}

		if(cur.jisu>0)
		{
			cout<<cur.mit<<" "<<cur.jisu<<endl;
			cout<<cur2.mit<<" "<<cur2.jisu<<endl;
			k_prime.push_back(cur);
			k_prime.push_back(cur2);
		}
	}
	*/
	int gcd=1;
	int N_jisu;
	for(iter=k_prime.begin(); iter!=k_prime.end(); iter++)
	{
		N_jisu=0;
		//cout<<iter->mit<< " "<<iter->jisu<<endl;
		for(int i=iter->mit; i<=N; i*=iter->mit)
		{
			N_jisu += N/i;
		}

		for(int i=0; i<min(N_jisu, iter->jisu); i++)
		{
			gcd*=iter->mit;
		}
	}
	return gcd;
	//1.1 Sieve of Eratosthenes, sqrt(n)까지 체로 걸러낸다. 
	//cout<<"N"<<endl;

	//효율적으로 짜려다가 더 귀찮아진구현.
	/*
	while((cur.mit = ES_N.get_eratosthenes_sieve()))
	{
		//1.2 소인수를 밑으로, 지수를 구한다. 
		//int partial_sum=0;
		cur.jisu = 0;
		for(int i=cur.mit; i<=N; i*=cur.mit)
		{
			cur.jisu += N/i;
		}
		//cout<<cur.mit<<" "<<cur.jisu<<endl;
		n_prime.push_back(cur);
	}
	*/
	/*
		//3. iN, K의 최대공약수 구하기.
	int idx_n=0, idx_k=0;
	int gcd=1;
	//cout<<"size"<<n_prime.size()<<endl;
	while(idx_n<n_prime.size() && idx_k<k_prime.size())
	{
		//nncout<<idx_n<<" "<<idx_k<<endl;
		//cout<<k_prime[idx_k].mit<<" "<<n_prime[idx_n].mit<<endl;
		if(k_prime[idx_k].mit == n_prime[idx_n].mit)
		{
			for(int i=0; i<min(k_prime[idx_k].jisu, n_prime[idx_n].jisu); i++)
			{
				gcd *= k_prime[idx_k].mit;
			}
			idx_k++;
			idx_n++;
		}
		else if(k_prime[idx_k].mit < n_prime[idx_n].mit)
		{
			idx_k++;
		}
		else if(k_prime[idx_k].mit > n_prime[idx_n].mit)
		{
			idx_n++;
		}
	}
	*/
	//cout<<"FINSIH"<<gcd<<endl;
	return gcd;
}

void soinsu_div(int n)
{
	bool sis=true;
	//int loot_n = (sqrt(n)>(int)sqrt(n))? int(sqrt(n))+1 : int(sqrt(n));
	for(int i=2; i<=(int)sqrt(n); i++)
	{
		if(n%i==0)
		{
			soinsu.push_back(i);
			soinsu_div(n/i);
			sis=false;
			return;
		}
	}
	if(sis)
	{
		soinsu.push_back(n);
	}
}
