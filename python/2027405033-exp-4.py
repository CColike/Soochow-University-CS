##
l=list(input().split())
l=[int(i) for i in l]
l.sort()
print(l[(len(l)-1)//2])


##
l=list(map(int,input().split()))
b=True
for i in range(len(l)//2):
    if l[i]!=l[len(l)-i-1]:
        b=False
print(b)


##
def func(n):
    if n==1:
        return False
    for i in range(2,int(n**0.5)+1):
        if n%i==0:
            return False
    return True

tot=0
l=list(map(int,input().split()))
ll=[]
for i in l:
    if func(i):
        ll.append(i)

print(ll)
ll.sort()
for i in range(len(ll)):
    for j in range(i):
        if (ll[i]+ll[j]) in ll and i!=j:
            tot+=1
print(tot)


##
tot=0
for i in range(2,501):
    b=0                      
    for j in range(2,int(i**0.5)+1):
        if i % j==0:
            b=1
    if b:
        continue
    tot+=1
    print(i,end=' ')
    if tot%5==0:        
        print()


##
l=list(map(int,input().split()))
for i in l:
    for j in range(l.count(i)-1):
        l.remove(i)

l.sort()
print(l)


##
s1=list(map(str,input()))
s2=list(map(str,input()))
s1.sort()
s2.sort()
if s1==s2:
    print(True)
else:
    print(False)


##
import numpy
arr=numpy.random.randint(100,500,(4,4))
arr=arr.transpose()
print(arr)


##
t=[['张飞',78,75],['李大刀',92,67],['李墨白',84,88],['王老虎',50,50],['雷小米',99,98]]
t.sort(key=lambda x:x[1]+x[2],reverse=True)
print(t)


##
n=int(input())
a=[[None]*(n+1) for _ in range(n+1)]

i=2
j=(n-1)//2
for t in range(1,n*n+1):
    x=1 if i==n else i+1
    y=j
    i=n if i==1 else i-1
    j=1 if j==n else j+1
    if a[i][j]==None:
        a[i][j]=t
    else:
        a[x][y]=t
        i=x
        j=y
for i in range(1,n+1):
    for j in range(1,n+1):
        print(a[i][j],end=' ')
    print()

l=list(map(int,input().split()))
l.sort()
print(l[(len(l)-1)//2])




##拓展
l=list(map(int,input().split()))
for i in range(len(l)//2):
    t=l[i]
    l[i]=l[len(l)-i-1]
    l[len(l)-i-1]=t     
print(l)


##
lst=list(map(int,input().split()))
n=int(input())
lst.sort()
l=0
r=len(lst)-1
while l<r:
    mid=(l+r)//2
    if lst[mid]>=n:
        r=mid         
    else:
        l=mid+1      
print(l+1)

##
l=list(map(int,input().split()))
for i in range(1,len(l)):
    for j in range(i):
        if l[i]<l[j]:
            t=l[i]
            l[i]=l[j]
            l[j]=t         
print(l)
