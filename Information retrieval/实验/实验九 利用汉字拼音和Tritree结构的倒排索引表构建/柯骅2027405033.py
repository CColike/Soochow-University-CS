#[   (word1,{id1:[tf1, [pos1,pos2]],id2:[tf2,[pos1]]) ,(word2,{  }) ]
#利用字典树保存词
#1，先建第一行的字典，然后再建树
#2，在读入时直接建树
#3，树用什么建：字典：keys表示字典树的边   D={'你':{},}

#{word1 : {id1:[tf1, [pos1,pos2]]   ,   id2: [tf2, [pos1] ]    } ,word2:{  } }



def neww(word,tree,k):
    if(word==''):
        return
    if(word[0]not in tree):
        tree[word[0]]=tree.get(word[0],dict())
    neww(word[1::],tree[word[0]],k)
    if(len(word)==1):
        tree[word[0]]['AnS']=tree[word[0]].get('AnS',list())
        tree[word[0]]['AnS'].append(k)




from collections import defaultdict
import math
import jieba

def getdata():
    txt=[None]
    for i in range(1,10):
        Q = []
        with open("data/id"+str(i)+".txt","r",encoding='utf8')as f:
            for q in jieba.cut(f.read().strip()):
                Q.append(q)
            txt.append(Q)
    return txt


txt=getdata()


words=set()
for i in range(1,10):
    words=words.union(set(txt[i]))

DICT=[]
words=list(words)

for i in words:
#    DICT[i]=DICT.get(i,[])
    newnode={}
    for j in range(1,10):
        tf=txt[j].count(i)
        if(not tf):
            continue
        newnode[j]=newnode.get(j,[tf,[x for x in range(len(txt[j])) if i==txt[j][x]]])
    DICT.append((i,newnode))
#print(DICT)

#print(DICT)
tree={}
for i in range(len(words)):
    word=words[i]
    neww(word,tree,i)
#print(tree)

ans1=list()
for i in tree['阅']['读']['AnS']:
    ans1+=DICT[i][1].keys()

ans2=list()
for i in tree['理']['解']['AnS']:
    ans2+=DICT[i][1].keys()

print("含有阅读理解的文档编号为：",set(ans1).intersection(set(ans2)))

with open("柯骅2027405033Result.txt","w",encoding='utf-8') as f:
    f.write("含有阅读理解的文档编号为："+str(set(ans1).intersection(set(ans2))))


