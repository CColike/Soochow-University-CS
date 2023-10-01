import jieba
import math
from collections import defaultdict

def Getquery():
    txts=[]
    with open("query.txt","r",encoding='utf-8')as f:
        for line in f.readlines():
            data=[]
            for p in jieba.cut(line.split('\t')[1]):
                #print(line.strip('\t'))
                if not (p in stopwords):
                    data.append(p)
            #print(data)
            txts.append(data)
    return txts

def GetStopWords():
    Stop=['\n']
    with open("baidu_stopwords.txt",encoding='utf-8')as f:
        for i in f.readlines():
            Stop.append(i.strip())
    return Stop

def getcan():
    txts=[]
    for line in c:
        data=[]
        for p in jieba.cut(line.split('\t')[1]):
            #print(line.strip('\t'))
            if not (p in stopwords):
                data.append(p)
        #print(data)
        txts.append(data)
    return txts


def coss(txt1,txt2):
    tot=0

    all_words=list(set(txt1).union(set(txt2)))
    for i in all_words:
        tot+=abs(txt1.count(i)-txt2.count(i))
        return tot
    '''
    all_word=list(set(txt1).union(set(txt2)))
    d1=TFIDF4(all_word,txt1)
    d2=TFIDF4(all_word,txt2)

    fenzi = 0
    fenmu1 = 0
    fenmu2 = 0
    for k in d1.keys():
        fenzi += d1[k] * d2[k]

    for k in d1.values():
        fenmu1 += (k * k)
    fenmu1 = fenmu1 ** 0.5

    for k in d2.values():
        fenmu2 += (k * k)
    fenmu2 = fenmu2 ** 0.5

    res = (fenzi) / (fenmu1 * fenmu2)
    return res
    '''

def TFIDF4(Q,txts,k=1):
    #print(Q)
    ans=defaultdict(int)
    for i in range(len(Q)):
        tf=Q.count(Q[i])
        ans[Q[i]]=tf
        #ans[Q[i]]=(tf/((k*len(Q))+tf)) * ( math.log((candidates_len+1) / (len(d.get(Q[i],list()))+1))  +1)
    return ans

def judge(txt):
    tot=0
    with open("answer.txt",encoding='utf-8')as f:
        k=list(f.readlines())
        for i in range(len(k)):
            if(k[i].split('\t')[1]==txt[i]):
                tot+=1
    return tot


#有#（禁用字开启）
#72：100000000000000000000000000000000000000000000000000000000000000000

#无#
#69：1





stopwords=GetStopWords()
stopwords=[]  #有#65   无#69
query=Getquery()
#print(query)
with open("candidates.txt", "r", encoding='utf-8')as f:
    c=f.readlines()
candidates=getcan()
print(candidates)


d={}
for line in range(len(candidates)):
    for word in candidates[line]:
        d[word]=d.get(word,list())
        d[word].append(line)

'''
#print(d)
candidates_len=10100
final_ans=[]
for q in range(len(query)):#枚举查询
    num_lst=[]

    for word in query[q]:
        num_lst.append(d.get(word,list()))
    #print(num_lst)

    df=[]
    for i in range(len(num_lst)):
        df.append(len(num_lst[i]))#含有现查询这句话（q）中排序i这个词的文章总个数

    ans={}
    for m_num in num_lst:#枚举含有各个词的文章编号
        for num in m_num:
            ans[num]=ans.get(num,TFIDF4(query[q],candidates[num]))
    #for i in ans.keys():
        #print(candidates[i],ans[i])
    l=list(ans.items())
    l.sort(key=lambda x:-x[1])
    print(c[l[0][0]])
    final_ans.append(c[l[0][0]].split('\t')[1])

#用长度判断离谱的数据，然后选取另外一种的方法求得的
#出现多次反而选取一个的

#向量空间模型？


#想法：向量空间模型：同时计算两个文档的各个词的tfidf，求cos
#符号是否要禁用，是否要禁用一些特定的



print(judge(final_ans))
'''

candidates_len=10100
final_ans=[]
for q in range(len(query)):#枚举查询
    num_lst=[]

    for word in query[q]:
        num_lst.append(d.get(word,list()))
    #print(num_lst)

    df=[]
    for i in range(len(num_lst)):
        df.append(len(num_lst[i]))#含有现查询这句话（q）中排序i这个词的文章总个数

    ans={}
    for m_num in num_lst:#枚举含有各个词的文章编号
        for num in m_num:
            ans[num]=ans.get(num,coss(query[q],candidates[num]))
    print(ans)
    #for i in ans.keys():
        #print(candidates[i],ans[i])
    l=list(ans.items())
    l.sort(key=lambda x:x[1])
    print(c[l[0][0]])
    final_ans.append(c[l[0][0]].split('\t')[1])




print(judge(final_ans))


#相似词数最多的
#tf只有1和0两个数字？
#出现次数之差的最小值