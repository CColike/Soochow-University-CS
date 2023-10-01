#encoding=utf-8
#tf idf 求文章的关键字算法     可以根据文章库和停用词算出 某个词 在 指定文章中的权重
import os
import jieba
import math
from collections import defaultdict     #dic['saasd']不会报错

def Get_one(name,StopWords=()):
    Q=[]
    with open("data\\"+name+".txt", "r", encoding='utf-8')as f:
        for p in jieba.cut(f.read().strip()):
            if not (p in StopWords):
                Q.append(p)
    return Q

def Get_ones(name,n,StopWords=()):
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


def cnt(word,txts):
    cnt=0
    for i in txts:
        if(word in i):
            cnt+=1
    return cnt
#############################################################
#method     1
D_num=20
D_name='doc'#文档库
Q_num=3
Q_name='doc'
Stop_name='baidu_stopwords'
StopWords=GetStopWords(Stop_name)
txts=GetD(D_name,D_num,StopWords)
ans1={}

##print([1,2]+[3,4])

Q1=Get_one("doc5")+Get_one("doc7")+["麻辣烫","特色"]

for j in range(11,21):
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

    ans1[j]=ans1.get(j,res)   ###########

ans1=list(ans1.items())
ans1.sort(key=lambda x:-x[1])
print("method 1:")
ans1=list(ans1[x][0]for x in range(10))
print(ans1)
###############################################################
#method     2
#给定 R和 N， 让你判断新来的一篇文档D的 与 用户需求 的相关度
#R:相关文档   N:总文档 （包含R）
#相关度=ΣXi*log(Pi(1-Qi)/Qi(1-Pi))
#ti代表词，Xi代表它在新来的D中是否出现（出现为1，不出现为0）---------只需计算D中所有分词即可（每个只算一遍，即使它在D中出现了很多遍）
#Pi=ri/Ri           代表ti在相关文档中出现的频率（每篇只算+1）
#Qi=(ni-ri)/(N-Ri)  代表ti在不相关文档（即所有文档去除相关文档R剩下的文档）中出现的频率（每篇只算+1）
#一共有3种文档    N R D
#预处理
#最外层枚举D，对于计算过的D中的词添加到列表中，每次D清空
#写一个计算对于  [[][][][]]中有多少个[]含有指定词    ==》ri==》Pi
#                                             ==》ni==》Qi

D_num=10
N_num=10
R_num=2
D_name='doc'
N_name='doc'
Stop_name='baidu_stopwords'
StopWords=GetStopWords(Stop_name)

R=[Get_one("doc5"),Get_one("doc7"),["麻辣烫"],["特色"]]
N=Get_ones(N_name,N_num)

ans2=[]

for i in range(11,21):
    done=[]
    with open ("data\\"+D_name+str(i)+'.txt',"r",encoding='utf-8')as f:
        sum=0
        for word in jieba.cut(f.read().strip()):
            if word not in done:
                ri=cnt(word,R)
                pi=ri/R_num
                ni=cnt(word,N)
                sum=sum+(((ri+0.5)*(N_num-R_num-ni+ri+0.5))/((R_num-ri+0.5)*(ni-ri+0.5)))
                done.append(word)                          #(ri+0.5)(N-Ri-ni+ri+0.5)/(Ri-ri+0.5)(ni-ri+0.5)
    ans2.append((i,sum))

ans2.sort(key=lambda x:-x[1])
#print(ans2)

print("method 2:")
ans2=list(ans2[x][0]for x in range(10))
print(ans2)

with open("柯骅2027405033Result.txt","w",encoding='utf-8') as f:
    f.write(str(ans1)+'\n')
    f.write(str(ans2))







