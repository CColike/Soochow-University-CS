#1---------------------------------------------------------------------------
def func1(n):
    tot=0
    for i in range(1,n):#枚举1-（n-1）的数
        if n%i==0:
            tot+=i
    return tot
print(func1(8))
print(func1(100))
#思路：用for循环找出所有因数，累加
#2---------------------------------------------------------------------------
def func2(n):
    return int(str(n)[::-1])#转化成字符串再转化成整数

print(func2(650000))
print(func2(123456789))
#思路：转化成字符串，用反向切片
#3---------------------------------------------------------------------------
def jud(n):#判断是否为反素数
    t=0
    for i in range(2,int(n**0.5)+1):
        if n%i==0:
            t=1
    n=int(str(n)[::-1])
    for i in range(2,int(n**0.5)+1):
        if n%i==0:
            t=1
    if t:
        return False
    else:
        return True

c=0
i=1
while c<30:#计数，只输出30个
    i+=1
    if jud(i):
        c+=1
        print('%5d'%i,end='')
        if c%8==0:
            print()#换行
#思路：编写一个判断反素数的函数
#     只需要在判断素数的基础上在判断他的反数即可
#     在主程序中用while控制个数

#4---------------------------------------------------------------------------
def func4(n):
    t=0
    #判断是否是素数
    for i in range(2,int(n**0.5)+1):
        if n%i==0:
            return False
    n=n+1
    tot=0
    #计算p
    while n!=1:
        if n%2!=0:
            return False
        else:
            n=n//2
            tot+=1
    return tot

for i in range(2,1000):
    if func4(i):#返回值只有False和p两种情况
        print('%3d%4d'%(func4(i),i))
#思路：梅森素数只需要判断是否是素数和是否是2的p次方-1即可
#5---------------------------------------------------------------------------
def jia(s,n=5):#加密
    s = s + ' '
    ss = ''
    j = 0
    for i in s:
        o = ord(i)
        if o in range(48, 58):#判断并联系连在一起的整数
            j = j * 10 + o - 48
        elif j != 0:
            ss = ss + str(j * 5)
            j = 0
        if o in range(97, 123):
            ss = ss + chr((o +n-96) % 26 + 96)
        if o in range(65, 91):
            ss = ss + chr((o +n-64) % 26 + 64)
    return ss

def jie(s,n=5):#解密
    s = s + ' '
    ss = ''
    j = 0
    for i in s:
        o = ord(i)
        if o in range(48, 58):#判断并联系连在一起的整数
            j = j * 10 + o - 48
        elif j != 0:
            ss = ss + str(j // 5)
            j = 0
        if o in range(97, 123):
            ss = ss + chr((o-96+26-n) % 26+96)
        if o in range(65, 91):
            ss = ss + chr((o-64+26-n) % 26+64)
    return ss

s=input('please input a string:')
n=int(input('please input n:'))
print(jia(s,n))
print(jie(s,n))
#思路：枚举所有的s中的字符
#     利用其ord（）进行加密和解密
#6---------------------------------------------------------------------------
def func6(s):
    return ' '.join(list(s.split())[::-1])
print(func6(input('please input a sentence:')))
#思路：字符串和列表转换的熟练应用
#7---------------------------------------------------------------------------
def func7(s,n=0):
    d,s={},s.upper()#对大小写不敏感
    for i in s:
        d[i]=d.get(i,0)#放止报错
        d[i]+=1
    return(d[s[n]])
print(func7('This is a test example.'))
#思路：用字典统计每种字母出现的次数
#8---------------------------------------------------------------------------
def fib(n):
    if n==1 or n==2:#初值/终止条件
        return 1
    else:
        return fib(n-1)+fib(n-2)#自身调用自身
print(fib(int(input('please input n:'))))
#思路：根据初值决定终止条件，再用递归不断调用自身
#9---------------------------------------------------------------------------
def mao1(a):#从小到大排序
    l=len(a)
    for i in range(l):#每次找到剩余数中最大数
        for j in range(l-i-1):
            if a[j]>a[j+1]:
                temp=a[j]
                a[j]=a[j+1]
                a[j+1]=temp
    return a

def mao2(a):#从大到小排序
    l=len(a)
    for i in range(l):#每次找到剩余数中最小数
        for j in range(l-i-1):
            if a[j]<a[j+1]:
                temp=a[j]
                a[j]=a[j+1]
                a[j+1]=temp
    return a

l=list(map(int,input('please input 10 numbers:').split()))
print(mao1(l))
print(mao2(l))
#思路：从数组的第一个数开始，依次和后面的数相比
#     若前者大则交换顺序，直到所有大的数冒到最后，最后按照从小到大排序。
#10---------------------------------------------------------------------------
def sor1(l):#正序
    return ''.join(sorted(l,key=lambda x:ord(x)))
def sor2(l):#逆序
    return ''.join(sorted(l,key=lambda x:-ord(x)))
l=list(input('please input a string:'))
print(sor1(l))
print(sor2(l))
#思路：用key=lambda 进行排序
#     逆序排序只需要加上负号即可
#11---------------------------------------------------------------------------
def func(s):
    s = s.lower()#对大小写不敏感
    ss,l='',{}#用字典储存，键是字母，值是ascii码的和
    for i in s:
        o = ord(i)
        if o in range(97, 123):
            ss = ss + i
        else:
            if ss:#添加单词至字典
                l[ss]=l.get(ss,sum(ord(ss[i]) for i in range(len(ss))))
                ss=''
    l=list(l.items())
    l.sort(key=lambda x:x[1])#用关键字排序
    print(len(l))
    for i in l:
        print(i[0],i[1])

s='A major drawback of cross-network recommender solutions is that they can only be applied to users that are overlapped across networks. Thus, the non-overlapped users, which form the majority of users are ignored. As a solution, we propose CnGAN, a novel multi-task learning based recommend architecture。'
func(s)

#思路：（1）因为就算大写也只能算是一个单词，所以先全部变成小写
#     （2）先采用字典储存，键是单词，值是ascii的和
#     （3）排序用关键字排序即可
#---------------------------------------------------------------------------
def func(n,a,b,c):
    if n==1: #当n=1是直接移动即可
        print(a,'to',c)  # 打印 func 为字符串,a和c是参数
        return
    func(n-1, a, c, b)  # 移动上面的n-1个盘子
    func(1,a,b,c)  # 最后一个盘子
    func(n-1,b,a,c)  # b到a再到c

func(int(input('please input the number of plates:')),'A','B','C')
#---------------------------------------------------------------------------
x,y=list(map(int,input("请输入两个正整数:").split()))
a,b=max(x,y),min(x,y)#a是较大值，b是较小值
while a%b!=0:
    temp=a%b
    a=b
    b=temp#交替过程
print("最小公倍数数是:",x*y//b)

