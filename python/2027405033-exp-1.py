#1
a=int(input('请输入a:'))
b=int(input('请输入b:'))
c=a//b
d=a%b
print(' a除以b 的商为:',c)
print(' a除以b 的余数为:',d)

#2
a=int(input('请输入a:'))
b=int(input('请输入b:'))
c=int(input('请输入c:'))
d=int(input('请输入d:'))
m=max(max(a,b),max(c,d))
print('其中最大的数为:',m)

#3
s=input('请输入你的姓名:')
l=len(s)
print('你的姓名的长度为:',l)

#4
import math
h=int(input('请输入h(厘米):'))
r=int(input('请输入r(厘米):'))
v=r*r*math.pi*h
if 0==20000%v:
    k=round(20000//v)
else:
    k=round(20000//v+1)
print('大象要喝',k,'桶水')

#5
import math
x1=int(input('请输入第一个点的横坐标:'))
y1=int(input('请输入第一个点的纵坐标:'))
x2=int(input('请输入第二个点的横坐标:'))
y2=int(input('请输入第二个点的纵坐标:'))
d=math.sqrt((x1-x2)**2+(y1-y2)**2)
print('两点的距离为:',d)

#6
import random
t1=random.randint(100,999)
x1=t1//100
x2=(t1%100)//10
x3=t1%10
#t2=x3*100+x2*10+x1
print(t1,'互换后为',x3,end='')
print(x2,end='')
print(x1)

#拓展
x=float(input())
i=x
while abs(i*i-x)>0.00000000001:
    i=((x-i*i)/(2*i))+i
print(i)
