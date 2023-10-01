#encoding=utf-8
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

def GetStopWords():
    Stop=[]
    with open("date\\baidu_stopwords.txt",encoding='utf-8')as f:
        for i in f.readlines():
            Stop.append(i.strip())
    return Stop

def GetQ():
    with open("date\\Query.txt", "r", encoding='utf-8')as f:
        Q = jieba.lcut(f.read())
    return Q

def GetD(name,n,StopWords):
    txts=[]
    for i in range(1,n+1):
        with open("date\\"+name+str(i)+'.txt',"r",encoding='utf-8')as f:
            tot_len=0
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




def TFIDF1(Q,txts):
    ans=[]
    for i in txts:
        tot=0
        for q in Q:
            tot+=i.count(q)
        ans.append(tot)
    return ans

def TFIDF2(Q,txts):
    ans=[]
    global leng
    for i in txts:
        tot=0
        for q in Q:
            tot+=i.count(q)/(len(i))
        ans.append(tot)
    return ans

def TFIDF3(Q,txts):
    ans=[]
    for i in txts:
        tot=0
        for q in range(len(Q)):
            tf=i.count(Q[q])
            tot+=(tf/len(i))*(math.log((len(txts)+1)/(1+df[q]))+1)
        ans.append(tot)
    return ans


def TFIDF4(Q,txts,k):
    ans=[]
    for i in txts:
        tot=0
        for q in range(len(Q)):
            tf=i.count(Q[q])
            tot+=(tf/((k*len(i))+tf))*(math.log((len(txts)+1)/(1+df[q]))+1)
        ans.append(tot)
    return ans

D_num=3
StopWords=GetStopWords()
#print(StopWords)
Q=GetQ()
#print(Q)
txts=GetD('ID',D_num,StopWords)
#print(txts)
df=GetDf(Q,txts)
#print(df)
res=[]

res.append(TFIDF1(Q,txts))
res.append(TFIDF2(Q,txts))
res.append(TFIDF3(Q,txts))
print('方法一: sim(Query, ID1) =', res[0][0], 'sim(Query, ID2) =', res[0][1], 'sim(Query, ID3) =',res[0][2])
print('方法二: sim(Query, ID1) =', res[1][0], 'sim(Query, ID2) =', res[1][1], 'sim(Query, ID3) =',res[1][2])
print('方法三: sim(Query, ID1) =', res[2][0], 'sim(Query, ID2) =', res[2][1], 'sim(Query, ID3) =',res[2][2])

res.append(TFIDF4(Q,txts,k=1))
print('k=1:   ',res[0])
res.append(TFIDF4(Q,txts,k=0.01))
print('k=0.01:',res[1])
res.append(TFIDF4(Q,txts,k=100))
print('k=100: ',res[2])
