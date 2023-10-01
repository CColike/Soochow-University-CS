#-------------------------------------------------------
a=(65.5, 70.2, 100.5, 45.5, 88.8, 55.5, 73.5, 67.8)
p=sum(a)/8#平均值
for i in a:
    tot=abs(p-i)**2#计算
print('%.5f'%(tot/8))
#-------------------------------------------------------
l=list(map(int,input('please input the socres:').split()))
l.sort()  #在列表时就对它进行排序较为便捷
t=tuple(l)  #转换成元组才可以进行剥离元素
a,*b,c=t  #剥离最大最小值
print(sum(b)/len(b))
#-------------------------------------------------------
d={}
s=input('please input a string:')
for i in s:#枚举字符串中的字母
    d[i]=d.get(i,0)#用get防止报错
    d[i]+=1#统计
for i in d.items():
    print('%s:%d'%(i[0],i[1]))
#-------------------------------------------------------
a={'A':3,'#':10,3:100,(1,2):1}
b={'B':4,'#':50,1:999,(1,2):1}#在程序中创建两个字典
c=[]#储存最终结果
for i in a.keys():
    if i in b.keys():
        c.append(i)
print('the same keys are:',c)
#-------------------------------------------------------
def f(s):#在a和b的键值中寻找值为s的键
    x,y=[],[]
    for i in a.keys():
        if a[i]==s:
            x.append(i)
    for i in b.keys():
        if b[i]==s:
            y.append(i)
    return x,y

a={'A':3,'#':10,3:100,(1,2):1}
b={'B':100,'#':10,1:999,(1,2):10}
c=set(a.values())#a，b中都要有一样的值，所以只需要转化并枚举其中一个

for i in c:
    x,y=f(i)
    if x != [] and y != []:#输出
        print('have the same value:',i,'in a:',x)
        print('have the same value:',i,'in b:',y)
#-------------------------------------------------------
n=int(input('please input the number of staffs:'))
a=[[None for _ in range(2)] for _ in range(n)]
for i in range(n):
    a[i][0],a[i][1]=list(input('please input name and number').split())
#根据a规则进行排序
a.sort(key=lambda x:x[0])
#输出a规则结果
print('a):')
for i in range(n):
    print(a[i][0],a[i][1])
#根据b规则进行排序
a.sort(key=lambda x:x[1])
#输出b规则结果
print('b):')
for i in range(n):
    print(a[i][1],a[i][0])
#-------------------------------------------------------
import random
n=int(input('please input the number of numbers:'))
s=set()
for i in range(n):
    s.add(random.randint(1,1000))#在集合中增加一个1到1000的随机数
l=list(s)#转化成列表方便排序
l.sort()
print(l)#输出
#-------------------------------------------------------
def p(s):#用函数输出，避免写两遍
    for i in range(len(s)):
        if (i + 1) % 5 == 0:
            print('%5d' % s[i])
        else:
            print('%5d' % s[i], end='')
import random
#生成a和b两个集合
a,b=set(),set()
while len(a)<=200:
    a.add(random.randint(0,500))
while len(b)<=200:
    b.add(random.randint(0,500))
#不同的
c=list(a.symmetric_difference(b))
#相同的
d=list(a.intersection(b))
print('the different nums are:')
p(c)
print('the same nums are:')
p(d)
#-------------------------------------------------------
import random
def g():
    n=random.randint(1,10)
    x=set()
    for i in range(n):
        x.add(random.randint(0,1000))
    return x

#读入A|B和A&B并返回结果
def ff():
    global bing
    global jiao
    for i in range(3):
        x = list(map(int, input('please input A|B:').split()))
        y = list(map(int, input('please input A&B:').split()))
        if x==bing and jiao==y:
            return 'Binggo，you are right'
        else:
            print('Sorry, you are wrong,please try again')
    return('the right answer :\nA|B:%s\nA&B:%s'%(bing,jiao))

a,b=g(),g()#用函数生成ab集合
bing,jiao=a|b,a&b#生成交集和并集
#转化成列表方便下面的处理
a,b,bing,jiao=list(a),list(b),list(bing),list(jiao)
print('A is :')
for i in range(len(a)):
    print('%5d'%a[i],end='')
print('\nB is :')
for i in range(len(b)):
    print('%5d'%b[i],end='')
print()

print(ff())
#-------------------------------------------------------
n=int(input())
#while循环判断是否结束
while n!=1:
    if n%2==1:
        print(n,'*3+1=',n*3+1,sep='')
        n=n*3+1
    else:
        print(n,'/2=',n//2,sep='')
        n=n//2
#-------------------------------------------------------
x,y=list(map(int,input("请输入两个正整数:").split()))
a,b=max(x,y),min(x,y)#a是较大值，b是较小值
while a%b!=0:
    temp=a%b
    a=b
    b=temp#交替过程
print("最大公约数是:",b)
#-------------------------------------------------------
