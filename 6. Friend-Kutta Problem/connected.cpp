#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

typedef struct Graph{
    int **matrix;
    int nv;//no. of vertex
}graph;

void edge(graph g,int s,int f){
    g.matrix[s][f]=1;
    g.matrix[f][s]=1;
}


void bfsm(graph g,int u,int v){
    int nv=g.nv;

    if(u>=nv || v>=nv){
        cout<<"Incorrect Vertices";
        return;
    } else if(u==v){
        cout<<"Order: "<<u<<"\n";
    }

    int *queue = (int*)malloc(nv*sizeof(int));
    int *visited = (int*)calloc(nv,sizeof(int));
    int *order = (int*)calloc(nv,sizeof(int));
    int front,rear,i,j=0;
    bool flag = false;
    front=rear=0;
    queue[rear]=u;
    visited[u]=1;

    //cout<<"Order: ";
    while(front<=rear && !flag){
        for(i=0;i<nv;i++)
            if(g.matrix[queue[front]][i]==1 && visited[i]==0){
                queue[++rear]=i;
                visited[i]=1;
                if(i==v){
                    flag=true;
                    break;
                }  
            }
        //cout<<queue[front]<<"->";
        order[j++]=queue[front];
        front++;
    }

    if(flag)
    {
        cout<<"Pair Connected"<<endl;
        for(i=0;i<j;i++)
            cout<<order[i]<<" -> ";
        cout<<"end"<<endl;
    }
    else
        cout<<"\nPair Not Connected";

}

int dfsm(graph g,int s,int v,int *visited)//depth first search adjacency matrix
{
    int i;
    static int flag = 0,j=0;
    visited[s]=1;
    cout<<s<<" -> ";

    for(i=1;i<=g.nv;i+=1)
        if(g.matrix[s][i]==1 && visited[i]==0 && flag==0)
        {
            if(i==v)
                flag=1;
            dfsm(g,i,v,visited);
        }
    return flag;
}

int main(){
    int nv,i,j,u,v;
    double x;
    cout<<"Enter number of vertices: ";
    cin>>nv;

    graph g;
    g.nv=nv;
    g.matrix=(int**)calloc(nv,sizeof(int*));
    int *visited=(int*)calloc((nv+1),sizeof(int));
    int *order=(int*)calloc((nv+1),sizeof(int));
    for(i=0;i<nv;i++)
        g.matrix[i]=(int*)calloc(nv,sizeof(int*));

    cout<<"Enter Start & End Vertices:\n";
    for(i=0;i<nv;i++)
    {
        cin>>u>>v;
        edge(g,u,v);
    }

    for(i=0;i<nv;i++){
        for(j=0;j<nv;j++)
            cout<<g.matrix[i][j];
        cout<<"\n";
    }

    cout<<"Enter Test Pair:\n";
    cin>>u>>v;
    if(dfsm(g,u,v,visited)==1)
        cout<<"\nPair Connected\n";
    else 
        cout<<"\nNot Connected\n";

    return 0;
}