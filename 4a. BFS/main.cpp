#include <stdio.h>
#include <stdlib.h>

typedef struct Node//node for adjacency list
{
    int ver;
    struct Node *next;
}node;

typedef struct Graph
{
    int v;//no. of vertexes
    node **arr;//array of pointers for adjacency list
    int **mat;//adjacency matrix
    int *vertex;//array of vertexes
}graph;

void edgel(graph g,int s,int f)//add an edge in graph adjacency list
{
    if(s>g.v || f>g.v)
        return ;
    node *temp,*n=(node*)malloc(sizeof(node));
    n->ver=f;
    temp=g.arr[s];
    g.arr[s]=n;
    n->next=temp;

    n=(node*)malloc(sizeof(node));
    n->ver=s;
    temp=g.arr[f];
    g.arr[f]=n;
    n->next=temp;
}

void edgem(graph d,int s,int f)//add an edge in graph adjacency matrix
{
    d.mat[s][f]=1;
    d.mat[f][s]=1;
}

void bfsm(graph g,int s)//breadth first search adjacency matrix
{
    int *q,front,rear,*visited,i;
    q=(int*)malloc(g.v*sizeof(int));
    visited=(int*)calloc((g.v+1),sizeof(int));
    front=rear=0;
    q[rear]=s;
    visited[s]=1;
    while(front<=rear)
    {
        for(i=1;i<=g.v;i+=1)
            if(g.mat[q[front]][i]==1 && visited[i]==0)
            {
                q[++rear]=i;
                visited[i]=1;
            }
        printf("%d-",q[front]);
        front++;
    }
    printf("\n");
}

void bfsl(graph g,int s)//breadth first search adjacency list
{
    int *q,front,rear,*visited;
    q=(int*)malloc(g.v*sizeof(int));
    visited=(int*)calloc((g.v+1),sizeof(int));
    front=rear=0;
    q[0]=s;
    visited[s]=1;
    while(front<=rear)
    {
        node *p=g.arr[q[front]];
        while(p!=NULL)
        {
            if(visited[p->ver]==0)
            {
                q[++rear]=p->ver;
                visited[p->ver]=1;
            }
            p=p->next;
        }
        printf("%d-",q[front]);
        front++;
    }
    printf("\n");
}

void dfsm(graph g,int s,int *visited)//depth first search adjacency matrix
{
    int i;
    visited[s]=1;
    printf("%d-",s);
    for(i=1;i<=g.v;i+=1)
        if(g.mat[s][i]==1 && visited[i]==0)
            dfsm(g,i,visited);
}

void dfsl(graph g,int s,int *visited)//depth first search adjacency list
{
    visited[s]=1;
    printf("%d-",s);
    node *p=g.arr[s];
    while(p!=NULL)
    {
        if(visited[p->ver]==0)
            dfsl(g,p->ver,visited);
        p=p->next;
    }
}

void conm(graph g)//connected parts of a graph adjacency matrix
{
    int i,*visited;
    visited=(int*)calloc((g.v+1),sizeof(int));
    for(i=1;i<=g.v;i+=1)
        if(visited[i]==0)
        {
            dfsm(g,i,visited);//only difference
            printf("\n");
        }
}

void conl(graph g)//connected parts of a graph adjacency list
{
    int i,*visited;
    visited=(int*)calloc((g.v+1),sizeof(int));
    for(i=1;i<=g.v;i+=1)
        if(visited[i]==0)
        {
            dfsl(g,i,visited);//only difference
            printf("\n");
        }
}

int main()
{
    int nv=5,i,*visited;
    graph g;
    g.v=nv;
    g.arr=(node**)calloc((nv+1),sizeof(node*));
    g.vertex=(int*)calloc((nv+1),sizeof(int));
    g.mat=(int**)calloc((nv+1),sizeof(int*));
    for(i=0;i<=nv;i+=1)
        g.mat[i]=(int*)calloc((nv+1),sizeof(int));
    for(i=0;i<=nv;i+=1)
        g.vertex[i]=i;
    edgel(g,1,3);
    edgel(g,1,5);
    edgel(g,3,2);
    //edgel(g,4,5);
    edgel(g,3,5);

    edgem(g,1,2);
    //edgem(g,1,4);
    edgem(g,3,2);
    edgem(g,4,5);
    //edgem(g,3,4);
    bfsm(g,1);
    visited=(int*)calloc((nv+1),sizeof(int));
    //dfsm(g,1,visited);
    //conm(g);
    return 0;
}
