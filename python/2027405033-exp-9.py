import os
os.chdir(r'd:/python-ch10/')#改变当前工作目录
f=open('copy.txt')#打开文件copy.txt
n=open('new.txt','w')#创建文件new.txt
s=f.readline()
while s!='':#直到文章的末尾
    n.writelines(s)
    s=f.readline()
f.close()
n.close()
#思路：手动读取第一行文字，然后用while循环控制复制结束

import os
os.chdir(r'd:/python-ch10/')#改变当前工作目录
f=open('cat1.txt','a')#打开文件copy.txt
n=open('cat2.txt')#创建文件new.txt
s=n.readline()
while s!='':#直到文章的末尾
    f.writelines(s)
    s=n.readline()
f.close()
n.close()
#思路：只需要在第一题的基础上将操作模式等修改即可

#判断是否是符合条件的整数
def func(n):
    s=str(abs(n))
    if len(s)<2:
        return False
    for i in range(len(s)):
        if (i%2==0) and ((ord(s[i])-48)%2==0):
            return False
    return True
#主程序
import os
os.chdir(r'd:/python-ch10/')#改变当前工作目录
f=open('StrInts.txt','rb+')#打开文件
r=open('ResultInts.txt','w+')#创建文件
s=f.readlines()
j,l,n,ss=0,[],-1,' '
for i in range(len(s)):
    ss=bytes.decode(s[i])
    for i in range(len(ss)):
        o=ord(ss[i])
        if o in range(48,58):
            if j<0:
                j=j*10+48-o
            if j>0:
                j=j*10+o-48
            if not(ord(ss[i-1])in range(48,58)):
                j=o-48
            if ss[i-1]=='-':
                j=0-j

        elif j!=0:
            l.append(j)
            j=0
print(l)
ll=[]
for i in l:
    if func(i):
        ll.append(i)
for i in range(((len(ll)-1)//3)+1):#枚举每行
    s=''
    for j in range(3*i,min(len(ll),3*i+3)):
    # 用min来防止最后的一两个越界
        s=s+'%8d'%ll[j]
    #s=str.encode(s)
    r.writelines(s)

f.close()
r.close()

#思路：（1）读入每行
#     （2）寻找数字
#     （3）判断数字
#     （4）输出

import os
os.chdir(r'd:/python-ch10/')#改变当前工作目录
f=open('students_data.txt','rb+')#打开文件
s=f.readlines()
l=[[None for _ in range(3)]for _ in range(len(s))]
for i in range(len(s)):
    ss=bytes.decode(s[i])
    l[i]=list(ss.split())
    l[i][0]=int(l[i][0])
    l[i][2] = int(l[i][2])
    print('%-10d%-15s%5d'%tuple(l[i]))
#排序
l.sort(key=lambda x:x[0])
#清空txt
f.seek(0)
f.truncate()
#重新输入
s=int(input('please input the s:'))
for i in range(len(l)):
    if l[i][0]>=s:
        ss=' '.join((str(l[i][0]),l[i][1],str(l[i][2]),'\n')).encode()
        print(ss)
        f.write(ss)


import os
os.chdir(r'd:/python-ch10/')#改变当前工作目录
f=open('numbers.txt','rb+')#打开文件
r=open('sort.txt','w+')#创建文件
s=f.readlines()
l=[]
for i in range(len(s)):
    l.append(float(s[i].decode()))
#排序
l.sort()
tot=sum(l)
#平均值
p=tot/len(l)
tot=0
for i in l:
    ss=str(i)+'\n'
    r.write(ss)
    tot+=(i-p)**2
ss=str(p)+'\n'
r.write(ss)
#方差
fang=tot/len(l)
ss=str(fang)+'\n'
r.write(ss)
#思路：整体读入一行行处理，排序，计算平均值和方差，写入文件


import os
os.chdir(r'd:/python-ch10/folder/')#改变当前工作目录
f1=open('file1.txt')#打开文件1
f2=open('file2.txt')#打开文件2
f3=open('file3.txt')#打开文件3
f4=open('file4.txt')#打开文件4
n=open('merge.txt','w+')#创建文件
s=f1.readline()
while s!='':#直到文章的末尾
    n.writelines(s)
    s=f1.readline()
n.writelines('\n')
s=f2.readline()
while s!='':#直到文章的末尾
    n.writelines(s)
    s=f2.readline()
n.writelines('\n')
s=f3.readline()
while s!='':#直到文章的末尾
    n.writelines(s)
    s=f3.readline()
n.writelines('\n')
s=f4.readline()
while s!='':#直到文章的末尾
    n.writelines(s)
    s=f4.readline()
#思路：文件一个一个读入，按照第一题的方式进行写入，切换文件中途换行



import os
os.chdir(r'd:/python-ch10/')#改变当前工作目录
f=open('word.txt')#打开文件
r=open('new_word.txt','w+')#创建文件
s=f.readlines()#储存单词
for i in s:
    if i[0].upper() in ('A','E','I','O','U'):
        r.write(i)#写入
#思路：打开文件，判断是否符合，将符合的写入新文件


import os
os.chdir(r'd:/python-ch10/')#改变当前工作目录
f=open('names.txt','r+')#打开文件
s=f.readlines()#储存单词
ss=input('please input a name:')
s=set(s)
s.add(ss+'\n')
s=list(s)
s.sort()
#清空txt
f.seek(0)
f.truncate()
for i in s:
    f.write(i)
#思路：打开文件，读入新名字，用集合去重，转化成列表排序，写入

import os
os.chdir(r'd:/python-ch10/')#改变当前工作目录
f=open('bigfile.txt','rb+')#打开文件
l=[]
l.append(0)
s=f.readline()
l.append(f.tell())
while s!=''.encode():#直到文章的末尾
    s=f.readline()
    l.append(f.tell())
print(len(l)-2)#输出行数（第0个和最后一次循环分别多读了一个）
while 1:
    n=int(input('please input the number of the line:'))
    f.seek(l[n-1])
    print(f.readline().decode())
#思路：用tell先扫描一遍文件，记录每行开头的位置所在，并记录至一个列表
#     这样在输入之后就可以直接输出
