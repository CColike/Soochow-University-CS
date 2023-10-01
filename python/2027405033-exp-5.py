##
n=int(input('请输入整数n：'))
for i in range(1,n+1):
    for j in range(n-i):
        print(' ',end='')    #输出空格
    for j in range(2*i-1):
        print('*',end='')    #输出*号
    print()


##
n=int(input())
a=[[None]*(n+1) for _ in range(n+1)]  #开拓二维列表
for i in range(1,n+1):    #初始化第一行和第一列
    a[0][i]=i
    a[i][0]=i
for i in range(1,n+1):   #填上相乘所得数字
    for j in range(1,i+1):
        a[i][j]=i*j
for i in range(n+1):     #按要求格式输出
    for j in range(n+1):
        if a[i][j]:
            print(a[i][j],end='\t')   #按tab格式要求输出
        else:
            print(' ',end='\t')
    print()


##
n=int(input('请输入整数n：'))
for i in range (1,n+1):   #上半部分
    #输出一行前面的空格
    for j in range(n-i):  
        print('  ',end='')
    #输出*号
    for j in range(n+i-1):
        print('*',end='   ')
    print()

for i in range(n-1,0,-1):  #下半部分（只需改变第一行的i循环即可）
    # 输出一行前面的空格
    for j in range(n - i):
        print('  ', end='')
    # 输出*号
    for j in range(n + i - 1):
        print('*', end='   ')
    print()


##
while 1:
    n=input('Please input the number of numbers：')
    if n.isdigit():   #判断输入是否合法
        break
    else:
        print('当前的输入非法需要重新输入数值')
n=int(n)  #while循环结束后，n一定是整数
if n!=0:     #如果输入‘n=0’代表退出程序
    tot=0
    for i in range(n):
        tot+=int(input('Please input number %d：'%(i+1)))#格式化
    print('sum=',tot)


##
#判断素数的函数
def is_prime(n):
    if n==1:
        return False
    for i in range(2,int(n**0.5)+1):
        if n%i==0:
            return False
    return True
#主程序
n=int(input('请输入整数n：'))
a=[]
for i in range(1,n):
    if is_prime(i):
        a.append(i)
for i in range(1,len(a)-1):
    print(a[i-1],end=', ') #因格式要求将最后一个素数单独输出
#防止没有素数时程序报错
if a!=[]:
    print(a[len(a)-1])


##
a=int(input('请输入整数a：'))
n=int(input('请输入整数n：'))
tot=0
aa=a
for i in range(n):#共有n个数相加，只需控制循环次数即可
    tot+=aa
    aa=aa*10+a
print(tot)


##
n=int(input('Please input the number of rows：'))
m=int(input('Please input the number of columns：'))
a=[[[]for _ in range(m)]for _ in range(n)]   #开拓二维列表
#读入A
for i in range(n):     
    for j in range(m):
        a[i][j]=int(input('Please input A[{:0},{:1}]: '.format(i,j)))
#直接计算C
for i in range(n):
    for j in range(m):
        a[i][j]+=int(input('Please input B[{:0},{:1}]: '.format(i,j)))
print('C=',a)


##
n=int(input('请输入整数n：'))
k=int(input('请输入整数k：'))

b=[0 for _ in range(n+1)]  #b标记列表，表示小朋友是否淘汰
x=0   #当前是编号为x的小朋友
step=0  #报数已经报到了step号
out_num=0   #已经淘汰的小朋友数量

#模拟游戏开始：
while True:  
    x=x+1 if x!=n else 1
    if b[x]==0:  #编号为x的小朋友没有被淘汰：
        step+=1
        if step%k==0:   #此时淘汰
            out_num+=1
            b[x]=1
        if out_num==n-1:  #判断是否已经决出了胜利者
            break

#寻找最终赢家：
for i in range(1,n+1):
    if b[i]==0:
        print('%d号小朋友获胜'%i)
        break


##
import random
x=random.randint(100,999)  #生成一个三位随机数
n=0
tot=0
while n!=x:  #终止条件
    n=int(input('请输入所猜之数：'))
    if n<x:
        print('小了')
    if n>x:
        print('大了')
    tot+=1
print('对了')
print('您一共猜了%d次'%tot)  #格式化输出


##
n1=int(input('n1:'))
m1=int(input('m1:'))
n2=int(input('n2:'))
m2=int(input('m2:'))
#开辟二维列表
a=[[None for _ in range(m1)]for _ in range(n1)]
b=[[None for _ in range(m2)]for _ in range(n2)]
c=[[0 for _ in range(m2)]for _ in range(n1)]
#读入矩阵a
for i in range(n1):
    for j in range(m1):
        a[i][j]=int(input('A({:0},{:1}):'.format(i,j)))
#读入矩阵b
for i in range(n2):
    for j in range(m2):
        b[i][j]=int(input('B({:0},{:1}):'.format(i,j)))
#计算c
for i in range(n1):
    for j in range(m2):
        for k in range(m1):
            c[i][j]=c[i][j]+(a[i][k]*b[k][j])

print(c)


##
#func函数来判断输入它是否是完数
def func(n):
    tot=0
    for i in range(1,n):
        if n%i==0:
            tot+=i
    if n==tot:
        return True
    else: 
        return False


#按题目要求进行枚举
for i in range(100,1001,1):
    if func(i):
        print(i,end=' ')