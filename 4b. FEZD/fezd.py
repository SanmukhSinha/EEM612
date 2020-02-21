file=open("4b. FEZD\\05test01.txt","r")
#file=open("05test02.txt","r")

line=file.readline()
r,c=map(int,line.split())
a=[None]*r 

def change(a,i,j,r,c,cnt):
    if i>0 and j>0:
        if a[i-1][j-1]=='T':
            a[i-1][j-1]=cnt
            change(a,i-1,j-1,r,c,cnt)

    if i>0:
        if a[i-1][j]=='T':
            a[i-1][j]=cnt
            change(a,i-1,j,r,c,cnt)

    if i>0 and j<c-1:
        if a[i-1][j+1]=='T':
            a[i-1][j+1]=cnt
            change(a,i-1,j+1,r,c,cnt)

    if j>0:
        if a[i][j-1]=='T':
            a[i][j-1]=cnt
            change(a,i,j-1,r,c,cnt)
    
    if j<c-1:
        if a[i][j+1]=='T':
            a[i][j+1]=cnt
            change(a,i,j+1,r,c,cnt)
    
    if i<r-1 and j>0:
        if a[i+1][j-1]=='T':
            a[i+1][j-1]=cnt
            change(a,i+1,j-1,r,c,cnt)
    
    if i<r-1:
        if a[i+1][j]=='T':
            a[i+1][j]=cnt
            change(a,i+1,j,r,c,cnt)
    
    if i<r-1 and j<c-1:
        if a[i+1][j+1]=='T':
            a[i+1][j+1]=cnt
            change(a,i+1,j+1,r,c,cnt)
    
    
        

for i in range(r):
    line=file.readline()
    a[i]=list(map(int,line.split()))

for i in range(r):
    for j in range(c):
        if a[i][j]==0:
            a[i][j]='N'
        else:
            a[i][j]='T'

cnt=1

for i in range(r):
    for j in range(c):
        if a[i][j]=='T':
            a[i][j]=cnt
            change(a,i,j,r,c,cnt)
            cnt+=1

for i in range(r):
    for j in range(c):
        if a[i][j]=='N':
            a[i][j]=0
for i in a:
    print(i)    
print(cnt-1)


file.close()
