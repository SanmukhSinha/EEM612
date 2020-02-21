import random
import time
from matplotlib import pyplot as plt


n=[100,500,1000,3000,5000]

def init(a,n):
    for i in range(n):
        a[i]=random.randint(1,1000)

def bubblesort(a,n):
    t = time.time_ns()

    for i in range(n-1):
        for j in range(n-1-i):
            if a[j]>a[j+1]:
                temp=a[j]
                a[j]=a[j+1]
                a[j+1]=temp
    
    t=time.time_ns()-t
    return t

def selectionsort(a,n):
    t = time.time_ns()

    for i in range(n-1):
        min=i
        for j in range(i+1,n):
            if a[j]<a[min]:
                min=j

        temp=a[i]
        a[i]=a[min]
        a[min]=temp
    
    t=time.time_ns()-t
    return t
    
def insertionsort(a,n):
    t = time.time_ns()

    for i in range(1,n):
        key=a[i]
        j=i-1
        while j>=0 and a[j]>key:
            a[j+1]=a[j]
            j-=1
        a[j+1]=key
    
    t=time.time_ns()-t
    return t

tbsort=[]
tssort=[]
tisort=[]
for s in n:
    A=[None]*s

    init(A,s)
    tbsort.append(bubblesort(A,s)/1000)
    init(A,s)
    tssort.append(selectionsort(A,s)/1000)
    init(A,s)
    tisort.append(insertionsort(A,s)/1000)
    print(s)
print(tbsort,tssort,tisort)

rplot=plt.figure(1)
bplot,=plt.plot(n,tbsort,label='Bubble Sort')
splot,=plt.plot(n,tssort,label='Selection Sort')
iplot,=plt.plot(n,tisort,label='Insertion Sort')
plt.legend(handles=[bplot,splot,iplot])
plt.xlabel('Size')
plt.ylabel('Time(ms)')
plt.title('Random')


tbsort=[]
tssort=[]
tisort=[]
for s in n:
    A=[None]*s

    init(A,s)
    A.sort()
    tbsort.append(bubblesort(A,s)/1000)
    init(A,s)
    A.sort()
    tssort.append(selectionsort(A,s)/1000)
    init(A,s)
    A.sort()
    tisort.append(insertionsort(A,s)/1000)
    print(s)
print(tbsort,tssort,tisort)

aplot=plt.figure(2)
bplot,=plt.plot(n,tbsort,label='Bubble Sort')
splot,=plt.plot(n,tssort,label='Selection Sort')
iplot,=plt.plot(n,tisort,label='Insertion Sort')
plt.legend(handles=[bplot,splot,iplot])
plt.xlabel('Size')
plt.ylabel('Time(ms)')
plt.title('Sorted(Ascending)')


tbsort=[]
tssort=[]
tisort=[]
for s in n:
    A=[None]*s

    init(A,s)
    A.sort(reverse=True)
    tbsort.append(bubblesort(A,s)/1000)
    init(A,s)
    A.sort(reverse=True)
    tssort.append(selectionsort(A,s)/1000)
    init(A,s)
    A.sort(reverse=True)
    tisort.append(insertionsort(A,s)/1000)
    print(s)
print(tbsort,tssort,tisort)

dplot=plt.figure(3)
bplot,=plt.plot(n,tbsort,label='Bubble Sort')
splot,=plt.plot(n,tssort,label='Selection Sort')
iplot,=plt.plot(n,tisort,label='Insertion Sort')
plt.legend(handles=[bplot,splot,iplot])
plt.xlabel('Size')
plt.ylabel('Time(ms)')
plt.title('Sorted(Descending)')

rplot.show()
aplot.show()
dplot.show()

#input()

def maxheapify(a,n,i):
    large=i
    l=2*i+1
    r=2*i+2
    if(l<n and a[large]<a[l]):
        large=l
    if(r<n and a[large]<a[r]):
        large=r
    if(large!=i):
        a[i],a[large]=a[large],a[i]
        maxheapify(a,n,large);

def heapsort(a,n):
    for i in range(n//2-1,-1,-1):
        maxheapify(a,n,i)
    for i in range(n-1,0,-1):
        a[i],a[0]=a[0],a[i]
        maxheapify(a,i,0)


def quicksort(a,f,l):
    if(f<l):
        pivot=f
        i=f
        j=l
        while(i<j):
            while(i<=l and a[i]<=a[pivot]):
                i+=1
            while(a[j]>a[pivot]):
                j-=1
            if(i<j):
                a[i],a[j]=a[j],a[i]
        a[j],a[pivot]=a[pivot],a[j]
        quicksort(a,f,j-1)
        quicksort(a,j+1,l)

def mergesort(a,l,r):
    if(l<r):
        m=(l+r)//2

        mergesort(a,l,m)
        mergesort(a,m+1,r)

        a1=[None]*(r-l+1)
        i=l
        j=m+1
        k=0
        while(i<=m and j<=r):
            if(a[i]<=a[j]):
                a1[k]=a[i]
                k+=1
                i+=1
            else:
                a1[k]=a[j]
                k+=1
                j+=1
        while(i<=m):
            a1[k]=a[i]
            k+=1
            i+=1
        while(j<=r):
            a1[k]=a[j]
            k+=1
            j+=1
        for i in range(l,r+1):
            a[i]=a1[i-l]


thsort=[]
tqsort=[]
tmsort=[]
for s in n:
    A=[None]*s

    init(A,s)
    t = time.time_ns()
    heapsort(A,s)
    t=time.time_ns()-t
    thsort.append(t/1000)

    init(A,s)
    t = time.time_ns()
    quicksort(A,0,s-1)
    t=time.time_ns()-t
    tqsort.append(t/1000)

    init(A,s)
    t = time.time_ns()
    mergesort(A,0,s-1)
    t=time.time_ns()-t
    tmsort.append(t/1000)
    print(s)
print(thsort,tqsort,tmsort)

hplot=plt.figure(4)
bplot,=plt.plot(n,thsort,label='Heap Sort')
splot,=plt.plot(n,tqsort,label='Quick Sort')
iplot,=plt.plot(n,tmsort,label='Merge Sort')
plt.legend(handles=[bplot,splot,iplot])
plt.xlabel('Size')
plt.ylabel('Time(ms)')
plt.title('Random')


thsort=[]
tqsort=[]
tmsort=[]
for s in n:
    A=[None]*s

    init(A,s)
    A.sort()
    t = time.time_ns()
    heapsort(A,s)
    t=time.time_ns()-t
    thsort.append(t/1000)

    init(A,s)
    #A.sort()
    t = time.time_ns()
    quicksort(A,0,s-1)
    t=time.time_ns()-t
    tqsort.append(t/1000)


    init(A,s)
    A.sort()
    t = time.time_ns()
    mergesort(A,0,s-1)
    t=time.time_ns()-t
    tmsort.append(t/1000)
    print(s)
print(thsort,tqsort,tmsort)

qplot=plt.figure(5)
bplot,=plt.plot(n,thsort,label='Heap Sort')
splot,=plt.plot(n,tqsort,label='Quick Sort')
iplot,=plt.plot(n,tmsort,label='Merge Sort')
plt.legend(handles=[bplot,splot,iplot])
plt.xlabel('Size')
plt.ylabel('Time(ms)')
plt.title('Sorted(Ascending)')


thsort=[]
tqsort=[]
tmsort=[]
for s in n:
    A=[None]*s

    init(A,s)
    A.sort(reverse=True)
    t = time.time_ns()
    heapsort(A,s)
    t=time.time_ns()-t
    thsort.append(t/1000)

    init(A,s)
    #A.sort(reverse=True)
    t = time.time_ns()
    quicksort(A,0,s-1)
    t=time.time_ns()-t
    tqsort.append(t/1000)

    init(A,s)
    A.sort(reverse=True)
    t = time.time_ns()
    mergesort(A,0,s-1)
    t=time.time_ns()-t
    tmsort.append(t/1000)
    print(s)
print(thsort,tqsort,tmsort)

mplot=plt.figure(6)
bplot,=plt.plot(n,thsort,label='Heap Sort')
splot,=plt.plot(n,tqsort,label='Quick Sort')
iplot,=plt.plot(n,tmsort,label='Merge Sort')
plt.legend(handles=[bplot,splot,iplot])
plt.xlabel('Size')
plt.ylabel('Time(ms)')
plt.title('Sorted(Descending)')

hplot.show()
qplot.show()
mplot.show()

input()