#encoding=utf-8
import os
import jieba
import math
from collections import defaultdict     #dic['saasd']不会报错

txts=[]

for i in range(1,10):
    s='Reference '+str(i)+'.txt'
    with open("date\\"+s,"r",encoding='utf-8')as f:
        date=f.read()
        txts.append(jieba.lcut(date))
with open("date\\Target.txt","r",encoding='utf-8')as f:
    target=f.read()

l=jieba.lcut(target)
print(l)
tot=len(l)
s=set(l)
dic=defaultdict(float)

for i in s:
    tf=l.count(i)/tot
    cnt=1
    for j in txts:
        if i in j:
            cnt+=1
    tf_idf=tf*(math.log(11/(cnt+1))+1)
    dic[i]=tf_idf
#print(dic)

stp=[]
with open("date\\baidu_stopwords.txt","r",encoding='utf-8')as f:
    stp = f.read().splitlines()

ll=list(dic.items())
ll.sort(key=lambda x:x[1],reverse=True)
'''
i,cnt=-1,0
while(cnt<5):
    i+=1
    if not(ll[i][0]in stp):
        cnt+=1
        print(ll[i][0])
'''
i,cnt=-1,0
with open("柯骅2027405033Keywords.txt","w",encoding='utf-8') as f:
    while (cnt < 5):
        i += 1
        if not(ll[i][0]in stp):
            cnt += 1
            f.write(ll[i][0]+'\n')
f.close()