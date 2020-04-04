#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

struct comp{
	string s;
	comp(const string& sin):s(sin){}
	bool operator() (int i, int j)
	{
		return strcmp(s.c_str()+i, s.c_str()+j) <0 ;
	}
};

int order;
string str;

string solve();

int main()
{
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>order;
		cin>>str;
		cout<<"#"<<t<<" "<<solve()<<endl;
	}
}

string solve()
{
	vector<int> pfs;
	for(int i=0; i<str.length(); i++)
	{
		pfs.push_back(i);
	}

	sort(pfs.begin(), pfs.end(), comp(str));
/*	
	for(int i=0; i<pfs.size(); i++)
	{
		string prt = string(str.c_str() + pfs[i]);
		cout<< prt<<endl;
	}
*/

	string res = string(str.c_str()+pfs[order-1]);
	return res;
}
