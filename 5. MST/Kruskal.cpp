#include <iostream>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#define INF 99999.00
using namespace std;

class Graph
{
    private:
        vector < pair<double, pair<int,int> > > E;//list of all edges
        vector < pair<double, pair<int,int> > > T;//list of edges in mst Kruskal
        vector < pair<double, pair<int,int> > > P;
        double **adjMat;//stores squared distances
        int *parent;
        int V;//no. of nodes/vertices
        double cost;//cost of MST Kruskal
        double costP;//cost of mst Prim

    public:
        Graph(int v)
        {
            V=v;
            parent = new int[v];

            for(int i=0;i<v;i++)
                parent[i]=i;

            E.clear();
            T.clear();
        }

        void setMatrix(double **mat)
        {
            adjMat=mat;
        }

        void addEdge(int u,int v,double w)
        {
            pair<int,int> p;
            p=make_pair(u,v);
            E.push_back(make_pair(w,make_pair(u,v)));

        }

        int findSet(int i)
        {
            if(parent[i]==i)
                return i;
            else
                return findSet(parent[i]);
        }

        void unionSet(int u,int v)
        {
            parent[u]=parent[v];
        }

        void Kruskal()
        {
            int i,u,v;
            cost=0;
            sort(E.begin(),E.end());

            for(i=0;i<E.size();i++)
            {
                u=findSet(E[i].second.first);
                v=findSet(E[i].second.second);
                if(u!=v)
                {
                    T.push_back(E[i]);
                    unionSet(u,v);
                    cost+=sqrt(E[i].first);
                    cout<<sqrt(E[i].first)<<" " ;
                }
            }
        }

        void Prim()
        {

            int no_edge=0,x,y,i,j;
            bool selected[V]={false};
            selected[0]=true;
            costP=0;

            while(no_edge<V-1)
            {
                double min=INF;

                for(i=0;i<V;i++)
                {
                    if(selected[i])
                    {
                        for(j=0;j<V;j++)
                        {
                            if(!selected[j])
                            {
                                if(min>adjMat[i][j]){
                                    x=i;
                                    y=j;
                                    min=adjMat[i][j];
                                }
                            }
                        }
                    }
                }

                P.push_back(make_pair(min,make_pair(x,y)));
                costP+=sqrt(min);
                selected[y]=true;
                no_edge++;

            }
        }

        void print() 
        {
            cout << "Edge :" << " Weight" << endl;
            for (int i = 0; i < T.size(); i++)
                cout << T[i].second.first << " - " << T[i].second.second << " : "<< T[i].first;
            cout << endl;
        }

        double getCostKruskal()
        {

            return cost;
        }

        double getCostPrim()
        {
            return costP;
        }
};

int main()
{
    int size,i,j;
    double **mat,**xy;
    clock_t start, end;
    ifstream fin;

    fin.open("5. MST\\euc1000.txt");

    fin>>size;
    mat  = new double* [size];
    xy = new double* [size];
    for(i=0;i<size;i++)
    {
        mat[i] = new double[size];
        xy[i] = new double[2];
    }
    for(i=0;i<size;i++)
        fin>>xy[i][0]>>xy[i][1];

    fin.close();

    for(i=0;i<size;i++)
        for(j=i+1;j<size;j++)
        {
            mat[i][j]=pow((xy[i][0]-xy[j][0]),2)+pow((xy[i][1]-xy[j][1]),2);
            mat[j][i]=mat[i][j];
            //cout<<mat[i][j]<<" ";
        }

    
    Graph g(size);
    g.setMatrix(mat);

    for(i=0;i<size;i++)
        for(j=i+1;j<size;j++)
            g.addEdge(i,j,mat[i][j]);
    
    start=clock();
    g.Kruskal();
    end=clock();
    
    cout<<"\nKruskal:\nCost = "<<g.getCostKruskal()<<endl;
    cout<<"Time(ms) = "<<end-start<<endl;

    /*
    start=clock();
    g.Prim();
    end=clock();
    
    cout<<"\nPrim:\nCost = "<<g.getCostPrim()<<endl;
    cout<<"Time(ms) = "<<end-start<<endl;
    */
    
    return 0;
}
