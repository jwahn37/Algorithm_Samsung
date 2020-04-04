#include<iostream>
#include<vector>
using namespace std;

void nCr(int n, int r);
vector<int> selected;
int N=5, R=2;

int main()
{
	nCr(0, 0);	
}

void nCr(int idx, int r)
{
	if(r>=R){
		for(int i=0; i<selected.size(); i++)
			cout<<selected[i]<<" ";
		cout<<endl;
	}
	else{
		for(int i=idx; i<N; i++)
		{
			selected.push_back(i);
			nCr(i+1, r+1);
			selected.pop_back();
		}
	}
}	
