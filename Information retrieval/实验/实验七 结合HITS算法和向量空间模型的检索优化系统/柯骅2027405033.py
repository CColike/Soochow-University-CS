#tf idf 求文章的关键字算法     可以根据文章库和停用词算出 某个词 在 指定文章中的权重
import os
import jieba
import math
from collections import defaultdict     #dic['saasd']不会报错
import numpy as np
import re

def Get_one(name,StopWords=()):
    Q=[]
    with open(name, "r", encoding='utf-8')as f:
        for p in jieba.cut(f.read().strip()):
            if not (p in StopWords):
                Q.append(p)
    return Q

def Get_ones(name,n,StopWords=()):
    txts=[]
    for i in range(1,n+1):
        with open(name,"r",encoding='utf-8')as f:
            #print(f.read())
            date = []
            for p in jieba.cut(f.read().strip()):
                if not (p in StopWords):
                    date.append(p)
            #print(date)
            txts.append(date)
    return txts

def GetStopWords(name):
    Stop=[]
    with open(name,encoding='utf-8')as f:
        for i in f.readlines():
            Stop.append(i.strip())
    return Stop

def GetQ(name):
    with open(name, "r", encoding='utf-8')as f:
        Q = jieba.lcut(f.read())
    return Q

def GetD(StopWords):
    txts=[]
    for i in D_list:
        if os.path.exists("DocSet\\"+str(i)+'.txt'):
            with open("DocSet\\"+str(i)+'.txt',"r",encoding='utf-8')as f:
                #print(f.read())
                date = []
                for p in jieba.cut(f.read().strip()):
                    if not (p in StopWords):
                        date.append(p)
                #print(date)
                txts.append(date)
    return txts

def GetDf(Q,txts):
    df=[]
    for q in Q:
        tot=0
        for i in txts:
            if q in i:
                tot+=1
        df.append(tot)
    return df

def TFIDF4(Q,txts,k):
    ans=defaultdict(int)
    for i in range(len(Q)):
        tf=Q.count(Q[i])
        ans[Q[i]]=(tf/((k*len(Q))+tf)) * ( math.log((len(txts)+1) / (df[i]+1))  +1)
    return ans


#############################################################

D_list=[3,56,8,9,79,16,215,25,69,19,32,1,1926,55,39]
D_name=''#文档库
Stop_name='baidu_stopwords.txt'
StopWords=GetStopWords(Stop_name)
txts=GetD(StopWords)
ans1={}

##print([1,2]+[3,4])

Q=Get_one("query.txt")

for j in D_list:
    if not os.path.exists("DocSet\\"+str(j)+'.txt'):
        continue
    D=GetQ("DocSet\\"+str(j)+".txt")

    df=GetDf(Q,txts)#df在TFIDF4中要用，是全局变量    D是query    Q是文档库
    D1=TFIDF4(Q,txts,k=1)

    df=GetDf(D,txts)
    D2=TFIDF4(D,txts,k=1)

    fenzi=0
    fenmu1=0
    fenmu2=0
    for k in D1.keys():
        fenzi+=D1[k]*D2[k]

    for k in D1.values():
        fenmu1+=(k*k)
    fenmu1=fenmu1**0.5

    for k in D2.values():
        fenmu2+=(k*k)
    fenmu2=fenmu2**0.5

    res=(fenzi)/(fenmu1*fenmu2)

    ans1[j]=ans1.get(j,res)

ans1=list(ans1.items())
ans1.sort(key=lambda x:-x[1])
print("method 1:")
ans1=list(ans1[x][0]for x in range(13))
print(ans1)


#写入文件
with open("List1.txt","w") as f:
    for i in ans1:
        f.write(str(i)+'\n')

###################################################################################
#method 2
print("\n\n\nmethod 2:")
d1=[3,56,8,9,16,215,25,69,19,32,1,1926,55]
d2={3:0,56:1,8:2,9:3,16:4,215:5,25:6,69:7,19:8 ,32:9,1:10,1926:11,55:12}

exceptt=[39,79]

m=np.zeros((13,13),dtype=int)

for i in range(13):
    m[i][i]=1


with open ('Structuraldata.txt')as f:
    for i in f.readlines():
        t=re.findall(r'\d+',i)
        u=int(t[0])
        if(u in exceptt):
            continue
        for i in range(1,len(t)):
            v=int(t[i])
            if(v not in exceptt):
                m[d2[u]][d2[v]]=1

mt=np.transpose(m)

a=np.ones((13,1),dtype=float)
for i in range(13):
    a[i][0]=1/(13**0.5)


last_a=last_h=-1000007

while(True):
    h=np.matmul(m,a)
    tot=0
    for i in h:
        tot+=i**2
    tot=tot**0.5
    for i in range(13):
        h[i]/=tot

    a=np.matmul(mt,h)
    tot = 0
    for i in a:
        tot+=i**2
    tot=tot**0.5
    for i in range(13):
        a[i]/=tot

    #print(a)
    #print(h)

    a_std=np.std(a,ddof=1)
    h_std=np.std(h,ddof=1)
    if(abs(a_std-last_a)<1e-5 and abs(h_std-last_h)<1e-5):
        break

    last_a=a_std
    last_h=h_std


aa=[]
hh=[]
for i in range(13):
    aa.append((i,a[i]))
    hh.append((i,h[i]))

aa.sort(key=lambda x:-x[1])
hh.sort(key=lambda x:-x[1])

#print(aa)
#print(hh)

print("Authority由高到低:")
for i in aa:
    print(d1[i[0]])

print("Hub由高到低:")
for i in hh:
    print(d1[i[0]])

#写入文件
with open("ListHub.txt","w") as f:
    f.write("Authority由高到低:\n")
    for i in aa:
        f.write(str(d1[i[0]])+'\n')

with open("ListAuthority.txt","w") as f:
    f.write("Hub由高到低:\n")
    for i in hh:
        f.write(str(d1[i[0]])+'\n')