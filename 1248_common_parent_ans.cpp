#include<iostream>
#include<vector>
#include<queue>
using namespace std;
 
int get_depth(vector<int>& parent, int v)
{
    int ret = 0;
    int cur = v;
    while (cur != 1)
    {
        ret++;
        cur = parent[cur];
    }
 
    return ret;
}
 
int get_answer(vector<int>& parent, int n1, int n1_d, int n2, int n2_d)
{
    if (n1_d > n2_d)
    {
        while (n1_d != n2_d)
        {
            n1_d--;
            n1 = parent[n1];
        }
    }
 
    if (n1_d < n2_d)
    {
        while (n1_d != n2_d)
        {
            n2_d--;
            n2 = parent[n2];
        }
    }
 
    while (n1 != n2)
    {
        n1 = parent[n1];
        n2 = parent[n2];
    }
 
 
    return n1;
}
 
int get_size(vector<vector<int>>& child, int cur)
{
    int ret = 1;
 
    if (child[cur].size() == 0)
        return 1;
 
    for (int i = 0; i < child[cur].size(); i++)
    {
        ret += get_size(child, child[cur][i]);
    }
 
    return ret;
}
int main()
{
    int tc;
    cin >> tc;
 
    for (int t = 1; t <= tc; t++)
    {
        int V, E, node1, node2;
        int node1_depth, node2_depth;
        cin >> V >> E >> node1 >> node2;
 
        vector<int> parent(V + 1);
        vector<vector<int>> child(V + 1);
 
        for (int i = 0; i < E; i++)
        {
            int from, to;
            cin >> from >> to;
            parent[to] = from;
            child[from].push_back(to);
        }
 
        node1_depth = get_depth(parent, node1);
        node2_depth = get_depth(parent, node2);
 
        int ancess = get_answer(parent, node1, node1_depth, node2, node2_depth);
        int size = get_size(child, ancess);
 
        cout << "#" << t << " " << ancess << " " << size << endl;
 
    }
 
    return 0;
}

