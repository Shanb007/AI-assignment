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

class TSP
{
	/*This Class defines the Basic functions for the TSP Problem, like taking the Input and calculating the distance matrix for the cities*/
	public:

		char node[3];
		int points[40][2],numCities;
		//TSP(int i,int j) : x(i),y(j){}

		void inputData()
		{

			scanf("%d",&numCities);
			int i=0;
			getc_unlocked(stdin);
			//double distance
			while(i<numCities)
			{
				scanf("%s%d%d ",node,&points[i][0],&points[i][1]);
				i++;
			}

		}

		int CalculateDistance(int x1,int y1,int x2,int y2)
		{
			return int(sqrt(pow(x1-x2,2)+pow(y1-y2,2)) + 0.5 );
		}
		void createOriginalDistanceGraph()
		{
			int i,j;
			for(i=0;i<numCities;i++)
			{
				originalGraph[i][i]=0;
				adjacencyMatrixForMinimumSpanningTree[i][i]=0;
				for(j=i+1;j<numCities;j++)
				{
					originalGraph[i][j]=CalculateDistance(points[i][0],points[i][1],points[j][0],points[j][1]);
					originalGraph[j][i]=originalGraph[i][j];
					// This is a Symmetric TSP
					adjacencyMatrixForMinimumSpanningTree[i][j]=0;
					adjacencyMatrixForMinimumSpanningTree[j][i]=0;
					minimumSpanningTree[i][j]=INT_MAX;
					minimumSpanningTree[j][i]=INT_MAX;
				}
			}
		}
};

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


int optimumCost=INT_MAX;

Node createNode(int citynum,string pathSoFar,int citiesNotVisited,char name,int hCost,int aCost,int totalCost,string state,vector<int> citiesLeft)
{
	/*This function Creates a new City to be explored*/
	Node temp( citynum, pathSoFar, citiesNotVisited, name, hCost,aCost,totalCost,state, citiesLeft);
	return temp;
}

int numExpanded=1,totalNumofNodes=1;
string startSearch()
{
	/*This is the main ASTAR Search Function where the nodes are generated and put on the Priority Queue*/
	Node current;
	int hn,tCost,aCost;
	char name;
	vector<int> vertices;
	vector<int>::iterator it,it3;
	vector<int> nextUnvisitedCities;
	vector<char> namesOfCitiesYettoVisit,namesOfCitiesYettoVisit2;
	vector<char>::iterator it2;
	string pathSoFar,state,npathSoFar,nstate;
	string res;
	while(!astar.empty() and astar.top().totalCost < optimumCost)
	{
		current=astar.top();
		astar.pop();

		pathSoFar=current.pathSoFar;
		state=current.state;


		vertices=current.citiesLeft;
		for(it=vertices.begin();it!=vertices.end();it++)
		{
			int next=*it;

		}

		if(current.citiesNotVisited==0)
		{

			int tcost=current.actualCost + distance(current.citynum,0);

			if(tcost< optimumCost )
			{
				optimumCost=tcost;
				res=current.pathSoFar;

			}

			continue;
		}
		if(closedList.find(state)!=closedList.end() and closedList[state] < current.totalCost)
		{

			continue;
		}
		if(closedList.find(state)!=closedList.end() and closedList[state] > current.totalCost)
		{

			closedList[state]=current.totalCost;
		}
		else if(closedList.find(state)==closedList.end())
		{
			closedList[state]=current.totalCost;
		}
		numExpanded++;
		for(it=vertices.begin();it!=vertices.end();it++)
		{
			int next=*it;
			nextUnvisitedCities.clear();
			namesOfCitiesYettoVisit.clear();
			vector<int>:: iterator it4;

			for(it3=vertices.begin();it3!=vertices.end();it3++)
			{
				int x=*it3;

				if(x==next)
				{
					continue;
				}

				nextUnvisitedCities.push_back(x);
			}

			for(it4=vertices.begin();it4!=vertices.end();it4++)
			{
				int city3=*it4;
				if(city3==next) continue;
				if( city3>25)
				{
					namesOfCitiesYettoVisit.push_back('a'+ city3-26);
				}
				else
				{
					namesOfCitiesYettoVisit.push_back('A'+city3);
				}
			}
			hn=calculateHeuristic(nextUnvisitedCities,namesOfCitiesYettoVisit,next);

			aCost=current.actualCost + distance(current.citynum,next);
			tCost=hn+ aCost;

			if( next>25)
			{
				name='a'+ next-26;
			}
			else
			{
				name='A'+next;
			}
			npathSoFar=pathSoFar+name;

			string temps=npathSoFar;
			sort(temps.begin(),temps.end());
			nstate=temps+name;


			totalNumofNodes++;
			astar.push(createNode(next,npathSoFar,current.citiesNotVisited-1,name,hn,aCost,tCost,nstate,nextUnvisitedCities));


		}

	}
	return res;
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

