#给定 R和 N， 让你判断新来的一篇文档D的 与 用户需求 的相关度
#相关度=ΣXi*log(Pi(1-Qi)/Qi(1-Pi))
#ti代表词，Xi代表它在新来的D中是否出现（出现为1，不出现为0）---------只需计算D中所有分词即可（每个只算一遍，即使它在D中出现了很多遍）
#Pi=ri/Ri           代表ti在相关文档中出现的频率（每篇只算+1）
#Qi=(ni-ri)/(N-Ri)  代表ti在不相关文档（即所有文档去除相关文档R剩下的文档）中出现的频率（每篇只算+1）
#一共有3种文档    N R D
#预处理
#最外层枚举D，对于计算过的D中的词添加到列表中，每次D清空
#写一个计算对于  [[][][][]]中有多少个[]含有指定词    ==》ri==》Pi
#                                             ==》ni==》Qi
import jieba
import math
from collections import defaultdict     #dic['saasd']不会报错


def GetStopWords(name):
    Stop=[]
    with open("data\\"+name+".txt",encoding='utf-8')as f:
        for i in f.readlines():
            Stop.append(i.strip())
    return Stop

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

def cnt(word,txts):
    cnt=0
    for i in txts:
        if(word in i):
            cnt+=1
    return cnt

D_num=1
R_num=1
N_num=1
D_name=''
R_name=''
N_name=''
Stop_name='baidu_stopwords'
StopWords=GetStopWords(Stop_name)

R=Get_ones(R_name,R_num)
N=Get_ones(N_name,N_num)

ans=[]
for i in range(1,D_num+1):
    done=[]
    with open ("data\\"+D_name+str(i)+'.txt',"r",encoding='utf-8')as f:
        for word in jieba.cut(f.read().strip()):
            if word not in done:
                ri=cnt(word,R)
                pi=ri/R_num
                qi=(cnt(word,N)-ri)/(N_num-R_num)
                sum+=math.log((pi*(1-qi))/(qi*(1-pi)))
                done.append(word)
    ans.append((i,sum))

ans.sort(key=lambda x:x[1])




