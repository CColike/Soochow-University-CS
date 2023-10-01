################################################################################################################
s=input('please input a string:')
if len(s)<2:
    print()     #s的长度小于2
else:
    print(s[:2]+s[len(s)-2::])  #返回一个由s的前2个字符和后2个字符组成的新字符串
    
#思路：if语句结合字符串切片

################################################################################################################
s=input('please input a string:')
n=int(input('please input "n":'))
print(s[:n-1]+s[n:]) #切片

#思路：字符串切片

################################################################################################################
l=list(input('please input a sentence:').split())#split转变成列表
print(' '.join(l[::-1]))#用join拼接

#思路：（1）拆分：split（）
#     （2）倒序拼接：切片+join

################################################################################################################
s=input('plsase input a string:')
d={}
for i in s:
    d[i]=d.get(i,0)  #防止下一步报错
    d[i]+=1  #value出现的次数+1
l=list(d.items())
for i in range(len(l)-1):
    print("'%s':%d,"%(l[i][0],l[i][1]),sep='',end='')
print("'%s':%d"%(l[len(l)-1][0],l[len(l)-1][1]),sep='',end='')

#思路：
#（1）用字典统计字符串出现次数
#（2）因为输出格式中用逗号间隔，但是最后一个没有逗号，所以转换成列表来判断是否最后一个

################################################################################################################
s=input('please input a verb:')
l=len(s)
#规则a）
if s[l-1]=='y':
    print(s[:l-1]+'ies')
#规则b）
#一行太长，用反斜杠写到两行
elif s[l-1]=='o' or s[l-1]=='s' or s[l-1]=='x'\
    or s[l-1]=='z' or s[l-2:l]=='ch' or s[l-2:l]=='sh':
    print(s+'es')
#规则c）
else:
    print(s+'s')

#思路：if语句搭配切片判断并输出

################################################################################################################
s=input('please input a password:')
if len(s)<8:  #条件1）
    print(False)
else:  #条件2）3）
    a,b,c=0,0,0  # 用abc来标记是否符合好密码条件
    for i in s:
        o=ord(i)
        if o in range(47,57):
            a=1
        if o in range(97,123):
            b=1
        if o in range(65,91):
            c=1
    if a and b and c:
        print(True)
    else:
        print(False)

#思路：
#（1）if判断条件是否满足
#（2）用标记变量来标记特征

################################################################################################################
a=int(input('please input a:'))
b=int(input('please input b:'))
s=input('please input the number:')
#先转化成十进制，存入n
n=int(s,a)
#初始化16进制以内的字母和数字，初始化最终输出逆序余数列表w
aa=[]
while n!=0:
    x=n//b
    y=n%b
    # aa列表按 照规则增加当前余数
    if y in range(10):
        aa.append(y)
    else:
        aa.append(chr(55+y))
    n=x
for i in aa[::-1]:   #逆序输出
    print(i,end='')

#思路：
#（1）将a进制先转化成10进制
#（2）用辗转相除求b进制

################################################################################################################
s=input('please input a string:')
ss=''
for i in s:
    if not(i in (' ','.',',','!')):   #过滤操作
        ss=ss+i
ss=ss.upper()  #对大小写不敏感
if ss==ss[::-1]:  #回文
    print(True)
else:
    print(False)
#思路：
#（1）用if语句和for循环过滤不需要的东西
#（2）用upper对大小写不敏感
#（3）切片判断回文

################################################################################################################
import re
s=input('please input a sentence:')
s=re.sub(' +',' ',s)#将多个空格替换成一个空格
s=re.sub('([,?!.;\'\"])(\w+)',r'\1 \2',s)#在标点后加空格
print(s)

#思路：采用正则表达式中的sub替换

################################################################################################################
import re
ss=''
for i in range(3):
    s=input()
    s=re.sub(r'<(\w+)>(.+)</\1>',r'\1: \2',s)##re中的替换
    ss=ss+s+'\n'##多行输出
print(ss)

##思路：类似于第9题，采用re中的sub替换
##      用’\n’在多行输出

################################################################################################################
n1=int(input('n1:'))
m1=int(input('m1:'))
n2=int(input('n2:'))
m2=int(input('m2:'))
a=[[None for _ in range(m1)]for _ in range(n1)]
b=[[None for _ in range(m2)]for _ in range(n2)]
c=[[0 for _ in range(m2)]for _ in range(n1)]
for i in range(n1):
    for j in range(m1):
        a[i][j]=int(input('A {:0},{:1}:'.format(i,j)))##格式化输出
for i in range(n2):
    for j in range(m2):
        b[i][j]=int(input('B {:0},{:1}:'.format(i,j)))##格式化输出
print(a)
print(b)
for i in range(n1):
    for j in range(m2):
        for k in range(m1):
            c[i][j]=c[i][j]+(a[i][k]*b[k][j])##根据公式

print(c)

################################################################################################################
def sort(lst):
    if len(lst)<2: ##无需排序
        return lst
    mid=lst[len(lst) // 2]  ##找到基准
    l,r=[],[]
    lst.remove(mid)   ##删除基准
    for i in lst:
        if i>=mid:    #比基准大放到r列表
            r.append(i)
        else:
            l.append(i)
    return sort(l)+[mid]+sort(r)  #返回排好序的列表

n=int(input('please input the amount of numbers:'))
a=list(map(int,input('please input the numbers:').split()))
print(sort(a))
################################################################################################################

