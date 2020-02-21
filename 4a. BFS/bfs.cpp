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

void gen_graph(graph g,double x){
    int nv=g.nv;
    int i,j;
    double r;
    srand(time(0));

    for(i=0;i<nv;i++){
        for(j=i;j<nv;j++){
            r=(double)rand()/RAND_MAX;
            if(r<=x)
                edge(g,i,j);
        }
    }
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
    int front,rear,i;
    bool flag = false;
    front=rear=0;
    queue[rear]=u;
    visited[u]=1;

    cout<<"Order: ";
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
        cout<<queue[front]<<"->";
        front++;
    }

    if(flag)
        cout<<v<<endl;
    else
        cout<<"\nEnd Vertex not found";

}

int main(){
    int nv,i,j,u,v;
    double x;
    cout<<"Enter number of vertices: ";
    cin>>nv;
    cout<<"Enter edge probability: ";
    cin>>x;

    graph g;
    g.nv=nv;
    g.matrix=(int**)calloc(nv,sizeof(int*));
    for(i=0;i<nv;i++)
        g.matrix[i]=(int*)calloc(nv,sizeof(int*));

    gen_graph(g,x);

    for(i=0;i<nv;i++){
        for(j=0;j<nv;j++)
            cout<<g.matrix[i][j];
        cout<<"\n";
    }

    cout<<"Enter Start Vertex: ";
    cin>>u;
    cout<<"Enter End Vertex: ";
    cin>>v;
    bfsm(g,u,v);

    return 0;
}