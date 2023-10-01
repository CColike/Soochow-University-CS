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

def TFIDF1(Q,txts):
    ans=[]
    cnt=0
    for i in txts:
        tot=0
        cnt+=1
        for q in Q:
            tot+=i.count(q)
        ans.append([D_name+str(cnt),tot])
    return ans

def TFIDF2(Q,txts):
    ans=[]
    cnt=0
    for i in txts:
        cnt+=1
        tot=0
        for q in Q:
            tot+=i.count(q)/(len(i))
        ans.append([D_name+str(cnt),tot])
    return ans

def TFIDF3(Q,txts):
    ans=[]
    cnt=0
    for i in txts:
        cnt+=1
        tot=0
        for q in range(len(Q)):
            tf=i.count(Q[q])
            tot+=(tf/len(i))*(math.log((len(txts)+1)/(1+df[q]))+1)
        ans.append([D_name+str(cnt),tot])
    return ans


def TFIDF4(Q,txts,k):
    ans=[]
    cnt=0
    for i in txts:
        cnt+=1
        tot=0
        for q in range(len(Q)):
            tf=i.count(Q[q])
            tot+=(tf/((k*len(i))+tf))*(math.log((len(txts)+1)/(1+df[q]))+1)
        ans.append([D_name+str(cnt),tot])
    return ans

def GetBefore(lst,k):
    lst1=sorted(lst,key=lambda x:-x[1])
    return [lst1[i][0]for i in range(k)]

def GetCorrectAns(name):
    with open("data\\"+name+".txt",encoding='utf-8')as f:
        return [i.strip() for i in f.readlines()]


D_num=15
D_name='doc'
Q_num=2
Q_name='query'
Stop_name='baidu_stopwords'
StopWords=GetStopWords(Stop_name)
#print(StopWords)
Need=[0,5,4]
CorrectAns_name='Ground truth results of query'
F=[]
for i in range(1,Q_num+1):
    NeedBefore=Need[i]
    Q=GetQ(Q_name+str(i))
    #print(Q)
    txts=GetD(D_name,D_num,StopWords)
    #print(txts)
    df=GetDf(Q,txts)
    #print(df)

    res=[0]
    print(Q_name,i,":")
    with open("柯骅2027405033Result.txt","a+",encoding='utf-8') as f:
        f.write(Q_name+str(i)+":\n")

    res.append(GetBefore(TFIDF1(Q,txts),NeedBefore))
    res.append(GetBefore(TFIDF2(Q,txts),NeedBefore))
    res.append(GetBefore(TFIDF3(Q,txts),NeedBefore))
    res.append(GetBefore(TFIDF4(Q,txts,k=1),NeedBefore))


    for j in range(1,5):
        print('方法'+str(j)+': \n   ',res[j])
        Result=res[j]
        CorrectAns = GetCorrectAns(CorrectAns_name + str(i))
        p = len(set(Result).intersection(set(CorrectAns))) / NeedBefore
        r = len(set(Result).intersection(set(CorrectAns))) / len(CorrectAns)
        print('       P=',p)
        print('       R=',r)
        print('       F=',(2*p*r)/(p+r))
        print('---------------------------------------------------------')
        with open("柯骅2027405033Result.txt", "a+", encoding='utf-8') as f:
            f.write('方法'+str(j)+': \n   ')
            f.write(str(res[j])+'\n')
            f.write('       P='+str(p)+'\n')
            f.write('       R='+str(r)+'\n')
            f.write('       F='+str((2*p*r)/(p+r))+'\n')
            f.write('---------------------------------------------------------\n')


