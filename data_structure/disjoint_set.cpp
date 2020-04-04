#include<iostream>
using namespace std;

//tree based disjoint set

/*
최적화: rank도입, 루트 갱신
rank: 대표자 노드가 포함된 서브트리의 높
   */
const int N = 10;
int parent[N];
int rank[N];

void make_set(int ele)
{
	parent[ele] = ele;
	rank[ele] = 0;
}

void union(int ele1, int ele2)
{
	int rep1 = find_set[ele1];
	int rep2 = find_set[ele2];

	if(rank[rep1] < rank[rep2])	//rep2의 트리가 더 레벨이 높다.
		parent[rep1] = rep2;
	else if (rank[rep1] > rank[rep2])
		parent[rep2] = rep1;
	//rank가 같으면 아무녀석이나 고름
	else if (rank[rep1] == rank[rep2])
	{
		parent[rep2] = rep1;
		rank[rep1]++;
	}
}

int find_set(int ele)
{
	if(ele == parent[ele])	return ele;
	//대표자는 루트에 있음
	//대표자를 바로 가리키도록 갱신한다.
	return parent[ele] = find_set(parent[ele]);
}
