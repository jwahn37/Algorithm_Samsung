#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<string>
using namespace std;


typedef struct axis{
	int begin, end;
}AXIS;

string substr(const string &s, const AXIS loc);

struct comp{
	string s;
	comp(string s):s(s){}
	bool operator() (AXIS c1, AXIS c2)
	{
		return strcmp(substr(s,c1).c_str(), substr(s,c2).c_str())<0; 
	}
};

string input;
int K;
vector<int> nCr_selected;

string solve();
void nCr(vector<AXIS>& substrs, int n, int r);
void make_substrs(vector<AXIS>& substrs);


int main()
{
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>K;
		cin>>input;
		cout<<"#"<<t<<" "<<solve()<<endl;
	}
}

string solve()
{
	vector<AXIS> substrs;
	make_substrs(substrs);

	//print
	sort(substrs.begin(), substrs.end(), comp(input));

//중복 제거
	for(int i=0; i<substrs.size()-1; i++)
	{
		if( strcmp(substr(input, substrs[i]).c_str(), substr(input, substrs[i+1]).c_str()) == 0)
		{
			substrs.erase(substrs.begin()+i);
			i--;
		}
	}

	if(substrs.size() < K)	return "none";

/*	
	for(int i=0; i<substrs.size(); i++)
	{
		cout<<i+1<<" "<<substr(input, substrs[i])<<endl;
	}
	*/
	return substr(input, substrs[K-1]);
}

void make_substrs(vector<AXIS>& substrs)
{
	//같은애 넣기
	AXIS cur;
	for(int i=0; i<input.length(); i++)
	{
		cur.begin=i, cur.end=i;
		substrs.push_back(cur);
	}
	nCr(substrs, 0, 0);

}

void nCr(vector<AXIS>& substrs, int n, int r)
{
	if(r>=2)
	{
		AXIS cur;
		cur.begin = nCr_selected[0];
		cur.end = nCr_selected[1];
		substrs.push_back(cur);

	//	cout<<cur.begin<<" "<<cur.end<<endl;
	}
	else{
		for(int i=n; i<input.length(); i++)
		{
			nCr_selected.push_back(i);
			nCr(substrs, i+1, r+1);
			nCr_selected.pop_back();
		}
	}
}

string substr(const string &s, AXIS loc)
{
	char res[400];
	string sres;
	strncpy(res, s.c_str()+loc.begin, loc.end - loc.begin + 1);
	sres = string(res);
	sres.resize(loc.end-loc.begin+1);
	return sres;
}
