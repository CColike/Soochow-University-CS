#{word1 : {id1:[tf1, [pos1,pos2]]   ,   id2: [tf2, [pos1] ]    } ,word2:{  } }



from collections import defaultdict
import math

def getdata():
    txt=[None]
    for i in range(1,15):
        with open("dataset/id"+str(i)+".txt","r")as f:
            txt.append(f.readline().split())
    return txt



def minn(x):#x:文章编号
    l1=DICT['a'][x][1]
    l2=DICT['b'][x][1]
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
            tf=DICT[query_word][i][0]
            tot+= (tf/((k*len(Q))+tf))*(math.log((len(txts)+1)/(len(DICT[query_word].keys())+1))+1)
        ans.append((i,tot))

    return ans





txt=getdata()
words=set()
for i in range(1,15):
    words=words.union(set(txt[i]))

DICT={}
for i in words:
#    DICT[i]=DICT.get(i,[])
    newnode={}
    for j in range(1,15):
        tf=txt[j].count(i)
        if(not tf):
            continue
        newnode[j]=newnode.get(j,[tf,[x for x in range(len(txt[j])) if i==txt[j][x]]])
    DICT[i]=DICT.get(i,newnode)
#print(DICT)

with open("query.txt","r")as f:
    q=f.readline().split()



contain=set(DICT[q[0]].keys())

for i in range(1,len(q)):
    contain=contain.intersection(set(DICT[q[i]].keys()))

print("包含query的文档编号有:",contain)

contain=list(contain)

distance=[]
for i in contain:
    distance.append((i,minn(i)))
distance.sort(key=lambda x:x[1])
print("最小编辑距离排序结果为:",[distance[x][0] for x in range(len(distance))])

tfidf_ans=TFIDF4(q,txt,k=1)
tfidf_ans.sort(key=lambda x:-x[1])
print("TF-IDF值排序结果为:",[tfidf_ans[x][0] for x in range(len(tfidf_ans))])

distance.sort(key=lambda x:x[0])
tfidf_ans.sort(key=lambda x:x[0])

multi=[]
for i in range(len(distance)):
    multi.append((distance[i][0],distance[i][1]/tfidf_ans[i][1]))
multi.sort(key=lambda x:x[1])
print("探索方法(使用已得的两组数据的商进行排序)：",[multi[x][0] for x in range(len(multi))])

with open("柯骅2027405033Result.txt","w") as f:
    f.write("包含query的文档编号有:"+str(contain)+'\n')
    f.write("最小编辑距离排序结果为:"+str([distance[x][0] for x in range(len(distance))])+'\n')
    f.write("TF-IDF值排序结果为:"+str([tfidf_ans[x][0] for x in range(len(tfidf_ans))])+'\n')
    f.write("探索方法(使用已得的两组数据的商进行排序)："+str([multi[x][0] for x in range(len(multi))])+'\n')