##
n=int(input())
n=n//15
tot=(n//5)*7+(n%5//3)*4+(n%5%3)
print(tot)

##
a=int(input())
b=int(input())
c=int(input())
if a==0:
    print('错误：输入的a不能为零，否则无意义')
else:
    d=(b**2)-(4*a*c)
    if d>0:
        print('%10.5f'%((  d**0.5-b)/(2*a)))
        print('%10.5f'%((0-d**0.5-b)/(2*a)))
    if d<0:
        xa=(0-b)/(2*a)
        xb=(0-d)**0.5/(2*a)
        print('%10.5f'%xa,'+','%10.5f'%xb,'j',sep='')
        print('%10.5f' % xa, '-', '%10.5f' % xb, 'j', sep='')
    if d==0:
        print('%10.5f' % ((d ** 0.5 - b) / (2 * a)))

##
def func(x1,y1,x2,y2):
    return (((x1-x2)**2+(y1-y2)**2)**0.5)
x1,y1=map(int,input().split())
x2,y2=map(int,input().split())
x3,y3=map(int,input().split())

if (y1-y2)*(x2-x3)==(y2-y3)*(x1-x2):
    print('无法组成三角形')
else:
    a = func(x1, y1, x2, y2)
    b = func(x3, y3, x2, y2)
    c = func(x1, y1, x3, y3)
    p = (a + b + c) / 2
    g = (p * (p - a)*(p - b)*(p - c))**0.5
    print('s=', g)
    print('c=', a+b+c)

##
x1,y1=map(int,input().split())
r=int(input())
x2,y2=map(int,input().split())
print('点在圆周内') if (x1-x2)**2+(y1-y2)**2<=r**2  else print('点在圆周外') 


##
s=input()
print(len(s))
if len(s)==1:
    print(int(s[0]))
    print(int(s[0]))
elif len(s)==2:
    print(int(s[0]),int(s[1]))
    print(int(s[1]),int(s[0]),sep='')
elif len(s)==3:
    print(int(s[0]),int(s[1]),int(s[2]))
    print(int(s[2]),int(s[1]),int(s[0]),sep='')
elif len(s)==4:
    print(int(s[0]),int(s[1]),int(s[2]),int(s[3]))
    print(int(s[3]),int(s[2]),int(s[1]),int(s[0]),sep='')
elif len(s)==5:
    print(int(s[0]),int(s[1]),int(s[2]),int(s[3]),int(s[4]))
    print(int(s[4]),int(s[3]),int(s[2]),int(s[1]),int(s[0]),sep='')

##
a,b,c=map(int,input().split())
if a<=b and a<=c:
    print(a,end=' ')
elif b<=a and b<=c:
    print(b,end=' ')
else:
    print(c,end=' ')
if a<=b and a>=c or a>=b and a<=c:
    print(a,end=' ')
elif b<=a and b>=c or b>=a and b<=c:
    print(b,end=' ')
else:
    print(c,end=' ')
if a>=b and a>=c:
    print(a,end=' ')
elif b>=a and b>=c:
    print(b,end=' ')
else:
    print(c,end=' ')

##
n=int(input())
s=[]
while n!=0:
    s.append(n%2)
    n=n//2
for i in s[::-1]:
    print(i,end='')

##
n=int(input())
if n<100000:
    print(1.015*n)
elif 100000<=n<500000:
    print(1.02*n)
elif 500000<=n<1000000:
    print(1.03*n)
else:
    print(1.035*n)

##
c=input()
if 96<ord(c)<123:
    print(chr(ord(c)-32))
elif 64<ord(c)<91:
    print(chr(ord(c)+32))
else:
    print(c)

##
a,b,c=map(int,input().split(':'))
c=c+30;
if c>=60:
    b+=1
    c=c%60
b=b+5
if b>=60:
    a+=1
    b=b%60
if a==24:
    a=0
print(a,b,c,sep=':')

##找到第一大的数
ch=ord(input())
print('yes') if ch in range(97,123) or ch in range(65,91) or ch in range(48,58) else print('no')
