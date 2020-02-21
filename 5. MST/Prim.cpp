#include <iostream>
#include <vector>
#include <list>
#include <utility>          
#include <iomanip>          
#include <time.h>
#include <fstream>
#include <algorithm>
#include <cmath>            
using namespace std;

struct HeapNode{
    int key, element;
    HeapNode():key(0),element(0){};
    HeapNode(int key, int element):key(key),element(element){};
};

class BinaryHeap{
    private:
        vector<HeapNode> heap;
        void swap(struct HeapNode &p1, struct HeapNode &p2);
        int FindPosition(int node);
        int GetParentNode(int node)
        {
            return floor(node/2);
        };

    public:
        BinaryHeap(){heap.resize(1);};
        BinaryHeap(int n)
        {
            heap.resize(n + 1);          
        }
        
        void MinHeapify(int node, int length);
        void BuildMinHeap( vector<double> array);
        void DecreaseKey(int node, int newKey);
        void MinHeapInsert(int node, int key);
        int ExtractMin();                               
        int Minimum()
        {
            return heap[1].element;
        };         

        bool IsHeapEmpty()
        {
            return (heap.size()<=1);
        };

};

int BinaryHeap::FindPosition(int node){

    int idx = 0;
    for (int i = 1; i < heap.size(); i++) {
        if (heap[i].element == node) {
            idx = i;
        }
    }
    return idx;
}
void BinaryHeap::MinHeapInsert(int node, int key){

    heap.push_back(HeapNode(node,key));
    DecreaseKey(node, key);
}
void BinaryHeap::DecreaseKey(int node, int newKey){

    int index_node = FindPosition(node);      

    if (newKey >= heap[index_node].key) {      
        return;
    }
    heap[index_node].key = newKey;            
                                              
    while (index_node > 1 && heap[GetParentNode(index_node)].key > heap[index_node].key) {
        swap(heap[index_node], heap[GetParentNode(index_node)]);
        index_node = GetParentNode(index_node);
    }
}
void BinaryHeap::swap(struct HeapNode &p1, struct HeapNode &p2){

    struct HeapNode temp = p1;
    p1 = p2;
    p2 = temp;
}
int BinaryHeap::ExtractMin(){

    if (IsHeapEmpty()) {
        exit(-1);
    }
    int min = heap[1].element;    
    
    
    heap[1] = heap[heap.size()-1];            
    heap.erase(heap.begin()+heap.size()-1);   
    MinHeapify(1, (int)heap.size());          

    return min;       
}
void BinaryHeap::BuildMinHeap( vector<double> array){

    
    for (int i = 0; i < array.size(); i++) {
        heap[i + 1].element = i;                 
        heap[i + 1].key = array[i];              
    }
    for (int i = (int)heap.size()/2; i >= 1 ; i--) {
        MinHeapify(i, (int)heap.size()-1);     
    }
}
void BinaryHeap::MinHeapify(int node, int length){

    int left = 2*node,          
        right = 2*node + 1,     
        smallest;               

    if (left <= length && heap[left].key < heap[node].key)
        smallest = left;
    else
        smallest = node;

    if (right <= length && heap[right].key < heap[smallest].key)
        smallest = right;

    if (smallest != node) {                 
        swap(heap[smallest], heap[node]);   
        MinHeapify(smallest, length);       
    }
}


static const double maxDistance = 100;


class Graph_MST{
    private:
        int num_vertex;
        vector< list< pair<int,double> > > AdjList;
        vector<int> predecessor;
        vector<double> distance;
        vector<bool> visited;
        double cost;
        void InitializeSingleSource(int Start);       
        void PrintDataArray(vector<int> array);

    public:
        Graph_MST():num_vertex(0){};
        Graph_MST(int n):num_vertex(n)
        {
            AdjList.resize(num_vertex);
        }
        void AddEdge(int from, int to, double weight);
        void Prim_MinQueue(int Start);
        double GetCost();
        friend class BinaryHeap;
};

void Graph_MST::InitializeSingleSource(int Start)
{

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        distance[i] = maxDistance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;      
}

void Graph_MST::Prim_MinQueue(int Start)
{
    cost=0;
    InitializeSingleSource(Start);

    BinaryHeap minQueue(num_vertex);
    minQueue.BuildMinHeap(distance);      

    visited.resize(num_vertex, false);    

    while (!minQueue.IsHeapEmpty()) {
        int u = minQueue.ExtractMin();
        visited[u] = true;
        for ( list< pair<int, double> >::iterator itr = AdjList[u].begin();
             itr != AdjList[u].end(); itr++) {
            if (visited[(*itr).first] == false && (*itr).second < distance[(*itr).first]) {
                distance[(*itr).first] = (*itr).second;
                predecessor[(*itr).first] = u;
                minQueue.DecreaseKey((*itr).first, distance[(*itr).first]);
            }
        }
    }

    /*cout << "print predecessor[]:\n";
    PrintDataArray(predecessor);
    cout << "print distance[]:\n";
    PrintDataArray(distance);

    cout <<  setw(3) << "v1" << " - " <<  setw(3) << "v2"<< " : weight\n";
    int i = (Start+1)%num_vertex;   
    while (i != Start) {
        cout <<  setw(3) << predecessor[i] << " - " <<  setw(3) << i
        << " : " <<  setw(3) << distance[i] <<"\n";
        i = (++i)%num_vertex;       
    }*/
}

void Graph_MST::AddEdge(int u, int v, double weight){

    AdjList[u].push_back( make_pair(v,weight));
}

double Graph_MST::GetCost()
{
    cost=0;
    for (int i = 0; i < num_vertex; i++){
        //cout<<sqrt(distance[i])<<" ";
        cost+=sqrt(distance[i]);
    }
    return cost;
}

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

    Graph_MST g(size);

    for(i=0;i<size;i++)
        for(j=0;j<size;j++)
            if(j!=i)
                g.AddEdge(i,j,mat[i][j]);

    cout << "Prim:\n";
    g.Prim_MinQueue(0);
    cout<<g.GetCost()<<endl;

    return 0;
}