import jieba
import math

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
    with open(stopwords_name,encoding='utf-8')as f:
        for i in f.readlines():
            Stop.append(i.strip())
    return Stop

def getcan():
    txts=[]
    for line in c:
        data=[]
        for p in jieba.cut(line.split('\t')[1]):
            #print(line.strip('\t'))
            if not (p in stopwords):#stopwords中有'/n'
                data.append(p)
        #print(data)
        txts.append(data)
    return txts


def TFIDF4(q,qqq,k=0.00000001):
    ans=float(0)
    for word_num1 in range(len(q)):
        tf=qqq.count(q[word_num1])
        #print(qqq.count('/n'))
        ans+=(tf/((k*len(qqq))+tf)) * ( math.log((candidates_len+1) / (df[word_num1]+1))  )
    return ans

def judge(my_ans):
    tot=0
    with open("answer-std.txt",encoding='utf-8')as f:
        k=list(f.readlines())
        for i in range(len(k)):
            if(k[i].split('\t')[1]==my_ans[i].split('\t')[1]):
                tot+=1
            else:
                print(k[i].split('\t')[1],my_ans[i])
    return tot


#有#（禁用字开启，带中文）
#72：100000000000000000000000000000000000000000000000000000000000000000

#无#
#69：1
#71:100000000000000000000000


#禁用字不带中文
#77：100000000000000000000000000000000000000000000000000000000000000000
#78：100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000



stopwords_name='cn_stopwords.txt'
stopwords=GetStopWords()
#stopwords=[]  #有#65   无#69
query=Getquery()
#print(query)
with open("candidates.txt", "r", encoding='utf-8')as f:
    c=f.readlines()
candidates=getcan()
#print(candidates)


d={}
for line in range(len(candidates)):
    for word in candidates[line]:
        d[word]=d.get(word,list())
        d[word].append(line)
#print(d['/n'])   其中没有\n换行符
#print(d)
candidates_len=10100
final_ans=[]

for q in range(len(query)):#枚举查询
    num_lst=[]

    for word in query[q]:
        num_lst.append(d.get(word,list()))#[[1,2,3,4],[7,8,9,5]]
    #print(num_lst)

    df=[]
    for i in range(len(num_lst)):
        df.append(len(num_lst[i]))   #含有现查询这句话（q）中排序i这个词的文章总个数

    ans={}
    for m_num in num_lst:            #枚举含有各个词的文章编号[1,2,3,4]    [7,8,9,5]
        for num in m_num:
            ans[num]=ans.get(num,TFIDF4(query[q],candidates[num]))




    l=list(ans.items())   #[(123,5.1231351),(587,1132.31351)]   (序号，tfidf值)
    l.sort(key=lambda x:-x[1])
    print(c[l[0][0]])   #C7472	谁有好的电影网址  c:candidates带\n换行符

    final_ans.append(c[l[0][0]])
    # final_ans.append(c[l[0][0]].split('\t')[1])





with open("2027405033.txt","w",encoding='utf-8') as f:
    for i in range(len(final_ans)):
        f.write(final_ans[i])

#print(judge(final_ans))



#用长度判断离谱的数据，然后选取另外一种的方法求得的
#出现多次反而选取一个的

#向量空间模型？


#想法：向量空间模型：同时计算两个文档的各个词的tfidf，求cos
#符号是否要禁用，是否要禁用一些特定的
