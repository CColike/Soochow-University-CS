#{word1 :[ [id1,tf1 [pos1,pos2]]   ,   [id2 tf2 [pos1] ]   ]   }
from collections import defaultdict
import math

def getdata():
    txt=[None]
    for i in range(1,15):
        with open("dataset/id"+str(i)+".txt","r")as f:
            txt.append(f.readline().split())
    return txt

def minn(x):
    for i in range(len(DICT['a'])):
        if(DICT['a'][i][0]==x):
            l1=DICT['a'][i][2]
            break
    for i in range(len(DICT['b'])):
        if(DICT['b'][i][0]==x):
            l2=DICT['b'][i][2]
            break
    ans=10000000007
    for i in l1:
        for j in l2:
            ans=min(ans,abs(i-j))
    return ans




def TFIDF4(Q,txts,k):#第四种方法计算tfidf值
    ans=[]

    for i in contain:
        tot=0
        for query_word in Q:
            for j in range(len(DICT[query_word])):
                if (DICT[query_word][j][0] == i):
                    tf=DICT[query_word][j][1]
            tot+= (tf/((k*len(Q))+tf))*(math.log((len(txts)+1)/(len(DICT['a'])+1))+1)
        ans.append((i,tot))

    return ans





txt=getdata()
words=set()
for i in range(1,15):
    words=words.union(set(txt[i]))

DICT={}
for i in words:
    DICT[i]=DICT.get(i,[])
    for j in range(1,15):
        tf=txt[j].count(i)
        if(not tf):
            continue
        newnode=[j,tf,[x for x in range(len(txt[j])) if i==txt[j][x]]]
        DICT[i].append(newnode)
print(DICT)

with open("query.txt","r")as f:
    q=f.readline().split()

contain=set([DICT[q[0]][x][0] for x in range(len(DICT[q[0]]))])

for i in range(1,len(q)):
    contain=contain.intersection(set([DICT[q[i]][x][0] for x in range(len(DICT[q[i]]))]))

print("包含query的文档编号有：",contain)

contain=list(contain)

contain.sort(key=lambda x:minn(x))
print("最小编辑距离排序结果为",contain)

tfidf_ans=TFIDF4(q,txt,k=1)
tfidf_ans.sort(key=lambda x:-x[1])
#print(tfidf_ans)
print("TF-IDF值排序结果为",[tfidf_ans[x][0] for x in range(len(tfidf_ans))])





