#include <bits/stdc++.h>

using namespace std;


void fitness(int a[],int n, int arr[4])
{
    int j,p,b,c,fit = 0;
      for(j=0;j<n;j++)
      {
          p =  abs(a[j]-arr[0]);
          b =  abs(a[j]-arr[1]);
          c =  abs(a[j]-arr[2]);

          p>b?(b>c?fit+=c:fit+=b):(p>c?fit+=c:fit+=p);
      }
      arr[3]=fit;
}

void sel_cross_mut(int a[],int n,int arr[][4],int m)
{
    srand(time(0));
    int i,t,k,j,w;
    int arr1[m][4];
    for(i=0;i<m/2;i++)
    {
        int mini=9999999;
        for(t=0;t<20;t++)
           { w = rand()%m;
             if(arr[w][3]<mini)
             {   mini = arr[w][3];
                 k=w;}
           }
        mini =9999999;
        for(t=0;t<20;t++)
           { w = rand()%m;
             if(arr[w][3]<mini)
             {   mini = arr[w][3];
                 j=w;}
           }

         int c = rand()%3;

         for(t=0;t<=c;t++)
         {
             arr1[i][t] = arr[k][t];
             arr1[m-i-1][t] = arr[j][t];
         }
         for(t=c+1;t<=2;t++)
         {
             arr1[i][t] = arr[j][t];
             arr1[m-i-1][t] = arr[k][t];
         }
    }

    int y = rand()%m;
    for(i=0;i<y;i++)
    {
        int g,h,r;
        g = rand()%m;
        h = rand()%3;
        r = rand()%n;
        arr1[g][h] = a[r];
    }
    for(i=0;i<m;i++)
     {
         fitness(a,n,arr1[i]);
     }

     for(i=0;i<m;i++)
     {
          for(t=0;t<4;t++)
          {
              arr[i][t]=arr1[i][t];
          }
     }

}


void chrom(int a[],int n,int arr[][4],int m)
{
    srand(time(0));
    int i,j,k;
    for(i=0;i<m;i++)
    {
        for(j=0;j<3;j++)
        {
            k = rand()%n;
            arr[i][j] = a[k];
        }
    }
     for(i=0;i<m;i++)
     {
         fitness(a,n,arr[i]);
     }

}

int main()
{
    srand(time(0));
    cout<<"Enter no. of students: "<<endl;
    int i,j,n;
    cin>>n;
    int a[n];
    for(i=0;i<n;i++)
     {
         a[i] = rand()%101+1;              
     }
    int pop[50][4];                   
    chrom(a,n,pop,50);
    int gmi = 99999999;
    int gmin[4];
    int itr = 2000;
    int mi = 99999999;
    while(itr-- || ((mi-gmi)>0) )
    {
    int min[4];
    for(i=0;i<50;i++)
    {
        if(pop[i][3] < mi)
        {
            mi = pop[i][3];
            min[0] = pop[i][0];
            min[1] = pop[i][1];
            min[2] = pop[i][2];
            min[3] = pop[i][3];
        }
    }
    if(mi<gmi)
    {
        gmi = mi;
        gmin[0] = min[0];
        gmin[1]=min[1];
        gmin[2]=min[2];
        gmin[3]=min[3];
    }
     sel_cross_mut(a,n,pop,50);
    }
    vector <pair<int,int>> g1,g2,g3;
     int p,b,c;
      for(j=0;j<n;j++)
      {
          p =  abs(a[j]-gmin[0]);
          b =  abs(a[j]-gmin[1]);
          c =  abs(a[j]-gmin[2]);
          p>b?(b>c?(g3.push_back(make_pair(a[j],j))):(g2.push_back(make_pair(a[j],j)))):(p>c?(g3.push_back(make_pair(a[j],j))):(g1.push_back(make_pair(a[j],j))));
      }
    cout<<"group 1:"<<gmin[0]<<" group 2:"<<gmin[1]<<" group 3 : "<<gmin[2]<<" fitness : "<<gmin[3]<<" "<<endl;
    cout<<"GROUP-1"<<endl;
    for(j=0;j<g1.size();j++)
    {
        cout<<"student  "<<g1[j].second<<" : "<<g1[j].first<<endl;
    }
    cout<<"*GROUP-2"<<endl;
    for(j=0;j<g2.size();j++)
    {
        cout<<"student  "<<g2[j].second<<" : "<<g2[j].first<<endl;
    }
    cout<<"GROUP-3"<<endl;
    for(j=0;j<g3.size();j++)
    {
        cout<<"student  "<<g3[j].second<<" : "<<g3[j].first<<endl;
    }
    return 0;
}
