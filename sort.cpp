#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

bool cmp(int a, int b) {return a>b;}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<int> a;
	for(int i=0; i<5; i++)	a.push_back(i);	//5, 4, 3, 2, 1

	sort(a.begin(), a.end());
	for(int i=0; i<5; i++)	cout<<a[i]<<" ";
	cout<<endl;


	sort(a.begin(), a.end(), cmp);
	for(int i=0; i<5; i++)	cout<<a[i]<<" ";
	cout<<endl;
}
