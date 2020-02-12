#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

string numbers;
int tn;

void solve();
//int searchMaxIndex(int index);
vector<int> searchMaxIndex(int index);
int isDuplicated();
void swap(int i, int j);

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>numbers;
		cin>>tn;

		solve();
		cout<<"#"<<t<<" "<<numbers<<endl;
	}
}

void solve()
{
	int i,j;
	vector<int> indexes;
	int cnt=0;
	int flag_dup=0;
	int e;
	i=0;
	while(i<numbers.size())
	{
		indexes = searchMaxIndex(i);
		
		if(indexes.size()>0)
		{
			e = (indexes.size()+cnt <= tn)?i+indexes.size() : i+(tn-cnt);
		//	cout<<"DEBUG "<<i<<" "<<e<<endl;
			sort(numbers.begin()+i, numbers.begin()+e);//오름차순 정렬
		//	cout<<"DEBUG "<<numbers<<endl;
			for(int j=i; j<i+indexes.size() && cnt<=tn; j++)
			{
				//swap(j, indexes.pop_back());
				swap(j, indexes.back());
				indexes.pop_back();
				cnt++;
				i++;
			}
		}
		else i++;

		if(cnt>=tn)	return;
	}

	//중복 여부 확인
	if(isDuplicated())	return;

	//중복 안되면, 가장 작은 마지막자릿수끼리만 스왑한다.
	while(cnt<tn)
	{
		swap(numbers.size()-2, numbers.size()-1);
		cnt++;
	}
}

//int searchMaxIndex(int index)
/*
index 이후의 값들 중 가장 큰 값을 보이는 인덱스를 오름차순으로 벡터에 넣어서 리턴한다.
주의* index의 값보다 더 커야한다.
*/
vector<int> searchMaxIndex(int index)
{
	int max_v=numbers[index];
//	int max_idex=index;
	vector<int> indexes;
	///for(int j=numbers.size()-1; j>=index+1; j--)
	for(int j=index+1; j<numbers.size(); j++)
	{
		if(numbers[j] > max_v)
		{
			indexes.clear();
			indexes.push_back(j);
			max_v = numbers[j];
		//	max_idex = j;
		}
		else if(max_v != numbers[index] && max_v == numbers[j])
		{
			indexes.push_back(j);
		}
	}
	//return max_idex;

	/*
	   cout<<"DEBUG: ";
	for(int i=0; i<indexes.size(); i++)	cout<<indexes[i]<<" ";
	cout<<endl;
	*/
	return indexes;;
}

void swap(int i, int j)
{
	int tp = numbers[i];
	numbers[i] = numbers[j];
	numbers[j] = tp;
}

int isDuplicated()
{
	for(int i=0; i<numbers.size()-1; i++)
	{
		if(numbers[i] == numbers[i+1])	return 1;
		/*
		for(int j=i+1; j<numbers_size(); j++)
		{
			if(numbers[i] == numbers[j])	return 1;
		}
		*/
	}
	return 0;
}
