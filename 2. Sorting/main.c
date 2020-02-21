#include <stdio.h>
#include <stdlib.h>

int mn(int a,int b)
{
    return a<b?a:b;
}

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

int fibs(int a[],int x, int n)
{
    int fib2=0,fib1=1,fib;
    fib=fib2+fib1;
    while(fib<n)
    {
        fib2=fib1;
        fib1=fib;
        fib=fib2+fib1;
    }
    int off=0;
    while(fib>=1)
    {
        int i=mn(fib2+off,n-1);
        if(a[i]<x)
        {
            fib=fib1;
            fib1=fib2;
            fib2=fib-fib1;
            off=i;
            printf("%d ",a[i]);//
        }
        else if(a[i]>x)
        {
            fib=fib2;
            fib1=fib1-fib2;
            fib2=fib-fib1;
            printf("%d ",a[i]);//
        }
        else return i;
    }
    if(fib1 && a[off]==x)
        return off;
    return -1;
}

int bsr(int a[],int l,int h,int x)
{
    int mid=(l+h)/2;
    if(h<l)
        return -1;
    if(a[mid]>x)
        h=mid-1;
    else if(a[mid]<x)
        l=mid+1;
    else
        return mid;
    return bsr(a,l,h,x);
}

void bubble(int a[],int n)
{
    int i,j;
    for(i=0;i<n-1;i+=1)
        for(j=0;j<n-1-i;j+=1)
            if(a[j]>a[j+1])
            {
                a[j]+=a[j+1];
                a[j+1]=a[j]-a[j+1];
                a[j]-=a[j+1];
            }
}

void select(int a[],int n)
{
    int i,j,mni;
    for(i=0;i<n-1;i+=1)
    {
        mni=i;
        for(j=i+1;j<n;j+=1)
            if(a[j]<a[mni])
                mni=j;
        swap(&a[i],&a[mni]);
    }
}

void ins(int a[],int n)
{
    int i,j,key;
    for(i=1;i<n;i+=1)
    {
        key=a[i];
        j=i-1;
        while(j>=0 && a[j]>key)
        {
            a[j+1]=a[j];
            j-=1;
        }
        a[j+1]=key;
    }
}

void maxheapify(int a[],int n,int i)
{
    int large=i;
    int l=2*i+1;
    int r=2*i+2;
    if(l<n && a[large]<a[l])
        large=l;
    if(r<n && a[large]<a[r])
        large=r;
    if(large!=i)
    {
        swap(&a[i],&a[large]);
        maxheapify(a,n,large);
    }
}

void heapsort(int a[],int n)
{
    int i;
    for(i=n/2-1;i>=0;i-=1)
        maxheapify(a,n,i);
    for(i=n-1;i>0;i-=1)
    {
        swap(&a[i],&a[0]);
        maxheapify(a,i,0);
    }
}

void qksort(int a[],int f,int l)
{
    if(f<l)
    {
        int pivot=f,i,j;
        i=f;
        j=l;
        while(i<j)
        {
            while(i<=l && a[i]<=a[pivot])
                i++;
            while(a[j]>a[pivot])
                j--;
            if(i<j)
                swap(&a[i],&a[j]);
        }
        swap(&a[j],&a[pivot]);
        qksort(a,f,j-1);
        qksort(a,j+1,l);
    }
}

void csort(int a[],int n)
{
    int k=a[0],i,j=0,*c;
    for(i=0;i<n;i+=1)
        if(k<a[i])
            k=a[i];
    c=(int*)calloc((k+1),sizeof(int));
    for(i=0;i<n;i+=1)
        c[a[i]]+=1;
    for(i=0;i<=k;i+=1)
        while(c[i]>0)
        {
            a[j++]=i;
            c[i]--;
        }
}

/*void merg(int a[],int l,int m,int r)
{
    int *a1,i,j,k=0;
    a1=(int*)malloc((r-l+1)*sizeof(int));
    i=l;
    j=m+1;
    while(i<=m && j<=r)
        if(a[i]<=a[j])
            a1[k++]=a[i++];
        else
            a1[k++]=a[j++];
    while(i<=m)
        a1[k++]=a[i++];
    while(j<=r)
        a1[k++]=a[j++];
    for(i=l;i<=r;i++)
        a[i]=a1[i-l];
}*/

void msort(int a[],int l,int r)
{
    if(l<r)
    {
        int m=(l+r)/2;

        msort(a,l,m);
        msort(a,m+1,r);

        int *a1,i,j,k=0;
        a1=(int*)malloc((r-l+1)*sizeof(int));
        i=l;
        j=m+1;
        while(i<=m && j<=r)
            if(a[i]<=a[j])
                a1[k++]=a[i++];
            else
                a1[k++]=a[j++];
        while(i<=m)
            a1[k++]=a[i++];
        while(j<=r)
            a1[k++]=a[j++];
        for(i=l;i<=r;i++)
            a[i]=a1[i-l];
    }
}

int main()
{
    int a[]={12, 2, 16, 30, 8, 28, 4, 10, 20, 6, 18},i;
    qksort(a,0,10);
    for(i=0;i<11;i++)
        printf("%d ",a[i]);
    return 0;
}
