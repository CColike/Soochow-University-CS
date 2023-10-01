##
n=int(input())
a=n//100
b=n//10%10
c=n%10
print("%4d"%(a+b+c))

##
from math import *
a=[int(x) for x in input('请按顺序输入x1,y1,x2,y2,x3,y3:').split()]
x=sqrt((a[0]-a[2])**2+(a[1]-a[3])**2)
y=sqrt((a[0]-a[4])**2+(a[1]-a[5])**2)
z=sqrt((a[2]-a[4])**2+(a[3]-a[5])**2)
p=(x+y+z)/2
s=sqrt(p*(p-x)*(p-y)*(p-z))
print("%7.2f"%s)

##
tot=0
for i in range(5):
    tot=(tot+100)*(1+0.005)
s=(tot-500)/500*100
print('%10.5f'%tot)
print('%9.2f'%s,'%',sep='')

##
import time
print ('当前时间是：',time.strftime('%H:%M:%S',time.localtime(time.time())))

##
import random
import math
r=random.randint(5,20)
v=math.pi*r*r
print('%15.3f'%r)
print('%15.3f'%v)

##
a=complex(input())
b=complex(input())
a1=a.real
a2=a.imag
b1=b.real
b2=b.imag
c=(a1*b1+a2*b2)/(abs(a)*abs(b))
print(c)

##
a=input()
b=input()
a1,a2,a3=a.split(':')
b1,b2,b3=b.split(':')

a1=int(a1)
a2=int(a2)
a3=int(a3)
b1=int(b1)
b2=int(b2)
b3=int(b3)

d=abs((a3-b3)+(a2-b2)*60+(a3-b3)*3600)

print(d)


##
import random
import math
a=random.randint(10,50)
b=random.randint(10,50)
z=complex(a,b)
m=abs(z)
c=math.atan(b/a)
print(' ',math.floor(z.real),'+',math.floor(z.imag),'j',sep='')
print('%7.2f'%m)
print('%7.2f'%c)

##
import time
s=time.time( )
d=s//(60*60*24)
h=(s%(60*60*24))/60/60
print('当前距离1970年1月1日过去了',d,'天又','%.2f'%h,'小时')
