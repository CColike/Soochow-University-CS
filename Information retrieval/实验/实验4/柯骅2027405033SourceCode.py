#encoding=utf-8
#tf idf 求文章的关键字算法     可以根据文章库和停用词算出 某个词 在 指定文章中的权重
import os
import jieba
import math
from collections import defaultdict     #dic['saasd']不会报错

def jud(a,b,c):
    print(a,b,c)
    if a>b and a>c:
        print(1)
    if b>a and b>c:
        print(2)
    if c>a and c>b:
        print(3)

def GetStopWords(name):
    Stop=[]
    with open("data\\"+name+".txt",encoding='utf-8')as f:
        for i in f.readlines():
            Stop.append(i.strip())
    return Stop

def GetQ(name):
    with open("data\\"+name+".txt", "r", encoding='utf-8')as f:
        Q = jieba.lcut(f.read())
    return Q

def GetD(name,n,StopWords):
    txts=[]
    for i in range(1,n+1):
        with open("data\\"+name+str(i)+'.txt',"r",encoding='utf-8')as f:
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



D_num=3
D_name='d'
Q_num=3
Q_name='d'
Stop_name='baidu_stopwords'
StopWords=GetStopWords(Stop_name)
txts=GetD(D_name,D_num,StopWords)
maxx=-1

for i in range(2,Q_num+1):
    for j in range(1,i):
        Q1=GetQ(Q_name+str(i))
        Q2=GetQ(Q_name+str(j))

        df=GetDf(Q1,txts)
        D1=TFIDF4(Q1,txts,k=1)

        df=GetDf(Q2,txts)
        D2=TFIDF4(Q2,txts,k=1)

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

        if(maxx<res):
            maxx=res
            ans=(j,i)

print(ans)

with open("柯骅2027405033Result.txt","w",encoding='utf-8') as f:
    f.write(str(ans[0])+'  '+str(ans[1]))



