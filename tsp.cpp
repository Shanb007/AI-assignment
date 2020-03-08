#include <bits/stdc++.h>
using namespace std;
#define lli long long int
#define V1 15

lli start;
priority_queue< pair<lli,pair<lli,pair<lli,pair<lli*,pair<lli,vector<lli>>>>>>, vector<pair<lli,pair<lli,pair<lli,pair<lli*,pair<lli,vector<lli>>>>>>>, greater<pair<lli,pair<lli,pair<lli,pair<lli*,pair<lli,vector<lli>>>>>>> >p1;

lli minKey(lli key[], bool mstSet[], lli V) 
{ 
 lli min = INT_MAX, min_index; 
 for (lli v = 0; v < V; v++) 
 if (mstSet[v] == false && key[v] < min) 
 min = key[v], min_index = v; 
 return min_index; 
} 

lli primMST(lli graph[V1][V1], lli V) 
{ 
 lli min1=0;
 lli parent[V]; 
  lli key[V]; 
 bool mstSet[V]; 
for (lli i = 0; i < V; i++) 
 key[i] = INT_MAX, mstSet[i] = false; 
  key[0] = 0; 
 parent[0] = -1; 
 for (lli count = 0; count < V - 1; count++) 
 { 
 lli u = minKey(key, mstSet, V); 
 mstSet[u] = true; 
for (lli v = 0; v < V; v++) 
 {
  if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
 parent[v] = u, key[v] = graph[u][v]; 
 }
 } 
 for (lli i = 1; i < V; i++) 
 min1+=graph[i][parent[i]]; 
 return min1;
} 

lli heuristic(lli node,lli visited[],lli graph[][V1])
{
 visited[node]=1;
 vector<lli>mst;
 lli min1=100000,min2=100000; 
 mst.push_back(node); 
 lli i,j,heuristic=0;
 for(i=1;i<=V1;i++)
 { 
 if(visited[i]==0)
 {
  mst.push_back(i);
 if(graph[node-1][i-1]<min1)
 min1=graph[node-1][i-1];
 if(graph[i-1][start-1]<min2)
 min2=graph[i-1][start-1];
 }
 } 
 if(mst.size()>1) 
 heuristic+=min1+min2;
 lli graph1[V1][V1]={0};
 for(i=0;i<mst.size();i++)
 {
  for(j=0;j<mst.size();j++)
 graph1[i][j]=graph[mst[i]-1][mst[j]-1];
 } 
 lli hmst = primMST(graph1,mst.size());
 heuristic+=hmst;
 return heuristic; 
}

void traversal(lli node,lli cost,lli visited[],vector<lli>path,lli graph[][V1])
{ 
lli mx=0;
 for(lli i=1;i<=V1;i++)
 {
  if(visited[i]>=mx)
 mx=visited[i];
 }
 visited[node]=mx+1;
 path.push_back(node); 
 lli z=0; 
 lli visited1[V1+1][V1+1]={0};
 lli visited2[V1+1][V1+1]={0}; 
 vector<lli>path1[V1+1]; 
 for(lli i=1;i<=V1;i++)
 { 
 if(visited[i]==0)
 { 
 for(lli j=1;j<=V1;j++)
 {visited1[i][j]=visited[j];
 if(visited[j]>=1)
 visited2[i][j]=1;
 else
 visited2[i][j]=0; 
 if(visited[j]>=1)
 path1[i].push_back(j);
 }
 lli heur=heuristic(i,visited2[i],graph);
 lli obj=heur+graph[node-1][i-1]+cost; 
 p1.push({obj,{i,{node,{visited1[i],{cost,path1[i]} } }}}); 
 z=z+1;
 }
 }
 if(z>=1) 
 {
 pair<lli,pair<lli,pair<lli,pair<lli*,pair<lli,vector<lli>>>>>> p2=p1.top();
 p1.pop();
 cost=p2.second.second.second.second.first + graph[p2.second.second.first-1][p2.second.first-1];
 lli* vis= p2.second.second.second.first;
 traversal(p2.second.first,cost,p2.second.second.second.first,p2.second.second.second.second.second,graph); 
 }
 else
 { 
 vector<pair<lli,lli>>finalpath;
 cout<<"Path: "; 
 for(lli i=1;i<=V1;i++)
 finalpath.push_back({visited[i],i});
 sort(finalpath.begin(),finalpath.end());
 for(lli i=0;i<finalpath.size();i++)
 cout<<finalpath[i].second<<" ";
 cout<<"1 "; 
 cout<<"\n";
  cout<<"Cost: "<<cost+graph[node-1][start-1];
 return;
 }
} 

int main()
{ 
 start=1;
lli visited[V1+1]={0};
 vector<lli>path; 
 lli graph[][V1] = 
 { 
{0, 29, 82, 46, 68, 52, 72, 42, 51, 55, 29, 74, 23, 72, 46,},
{29, 0, 55, 46, 42, 43, 43, 23, 23, 31, 41, 51, 11, 52, 21,}, 
{82, 55, 0, 68, 46, 55, 23, 43, 41, 29, 79, 21, 64, 31, 51,}, 
{46, 46, 68, 0, 82, 15, 72, 31, 62, 42, 21, 51, 51, 43, 64,}, 
{68, 42, 46, 82, 0, 74, 23, 52, 21, 46, 82, 58, 46, 65, 23,}, 
{52, 43, 55, 15, 74, 0, 61, 23, 55, 31, 33, 37, 51, 29, 59,}, 
{72, 43, 23, 72, 23, 61, 0, 42, 23, 31, 77, 37, 51, 46, 33,}, 
{42, 23, 43, 31, 52, 23, 42, 0, 33, 15, 37, 33, 33, 31, 37,}, 
{51, 23, 41, 62, 21, 55, 23, 33, 0, 29, 62, 46, 29, 51, 11,}, 
{55, 31, 29, 42, 46, 31, 31, 15, 29, 0, 51, 21, 41, 23, 37,}, 
{29, 41, 79, 21, 82, 33, 77, 37, 62, 51, 0, 65, 42, 59, 61,}, 
{74, 51, 21, 51, 58, 37, 37, 33, 46, 21, 65, 0, 61, 11, 55,}, 
{23, 11, 64, 51, 46, 51, 51, 33, 29, 41, 42, 61, 0, 62, 23,}, 
{72, 52, 31, 43, 65, 29, 46, 31, 51, 23, 59, 11, 62, 0, 59,}, 
{46, 21, 51, 64, 23, 59, 33, 37, 11, 37, 61, 55, 23, 59, 0,}
 }; 
 traversal(start,0,visited,path,graph);
 return 0; 
 }
