#include <iostream>
#include <algorithm>
using namespace std;
  
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

int quicksort(int a[],int b[],int f,int l)
{
    int pivot,i,j;
    if(f<l)
    {
        pivot=f;
        i=f;
        j=l;
        while(i<j)
        {
            while(i<=l and a[i]<=a[pivot])
                i+=1;
            while(a[j]>a[pivot])
                j-=1;
            if(i<j)
            {
                swap(a+i,a+j);
                swap(b+i,b+j);
            }
        }
        swap(a+j,a+pivot);
        swap(b+j,b+pivot);
        quicksort(a,b,f,j-1);
        quicksort(a,b,j+1,l);  
    }
}

void greedyKnapSack(int W, int wt[], int val[], int n)
{
    int i,j,*items=new int[n],tval=0;

    quicksort(val,wt,0,n-1);

    cout<<"\nGreedy Total Value = ";
    for(i=n-1;i>=0;i--)
        if(wt[i]<=W)
        {
            items[i]=1;
            W-=wt[i];
            tval+=val[i];
        }
    cout<<tval<<endl;

    cout<<"Item Values: ";
    for(i=n-1;i>0;i--)
        if(items[i]==1)
            cout<<val[i]<<" ";
    cout<<endl;           
    
} 

void dynamicKnapSack(int W, int wt[], int val[], int n) 
{ 
    int i, w; 
    int K[n + 1][W + 1]; 
  
    for (i = 0; i <= n; i++) { 
        for (w = 0; w <= W; w++) { 
            if (i == 0 || w == 0) 
                K[i][w] = 0; 
            else if (wt[i - 1] <= w) 
                K[i][w] = max(val[i - 1] +  
                    K[i - 1][w - wt[i - 1]], K[i - 1][w]); 
            else
                K[i][w] = K[i - 1][w]; 
        } 
    } 
  
    int res = K[n][W];     
    cout<<"\nBest Total Value = "<<res<<endl;
    
    cout<<"Item Values: ";
    w = W; 
    for (i = n; i > 0 && res > 0; i--) { 

        if (res == K[i - 1][w])  
            continue;         
        else { 
            cout<< val[i - 1]<<" ";
            res = res - val[i - 1]; 
            w = w - wt[i - 1]; 
        } 
    } 
} 
  
int main() 
{ 
    int val[]= {981,980, 979, 978, 977, 976, 487, 974, 970, 485, 485, 970, 970, 484, 484, 976, 974, 482, 962, 961, 959, 958, 857},
    wt[]={983,982, 981, 980, 979, 978, 488, 976, 972, 486, 486, 972, 972, 485, 485, 969, 966, 483, 964, 963, 961, 958, 959},
    n=23,
    w=10000,
    i;
    /*cout<<"Enter number of items: ";
    cin>>n;
    val=new int[n];
    wt=new int[n];
    cout<<"Enter values:\n";
    for(i=0;i<n;i++)
        cin>>val[i];

    cout<<"Enter Weights:\n";
    for(i=0;i<n;i++)
        cin>>wt[i];
    
    cout<<"Enter Max Weight: ";
    cin>>w;*/

    greedyKnapSack(w,wt,val,n);
    dynamicKnapSack(w, wt, val, n);
    return 0; 
}