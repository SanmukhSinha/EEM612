
n=int(input('Enter Number: '))
maxcount=0
maxnum=0

for x in range(n+1):
    count=0
    num=x
    while x>1:
        if x%2==0:
            x//=2
        else:
            x=x*3+1
        count+=1
    if count>maxcount:
        maxcount=count
        maxnum=num

print("Max Gold Shekel = ",maxcount," for X = ",maxnum)