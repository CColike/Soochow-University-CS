"""
读取文件 two_1.txt 、 two_2.txt 中的数据，两个文件里面均是按照升序存储的数值。 
要求:
    1. 将两个文件中的数值合并为一个降序数组，按行存储到文件two_3.txt中。 
    2. 从要求1得到数组中找到和为10的两个数的索引下标，print到控制台
"""

#读取两个文件
def GetWords(n):
    lst=[]
    for i in range(1,n+1):
        with open("data//two_"+str(i)+".txt","r")as f:
            for words in f.readlines():
                lst.append(int(words.strip()))
    return sorted(lst,reverse=True)

#保存产生的新列表
def Save(lst):
    with open("data//two_3.txt","w")as f:
        for i in lst:
            f.writelines(str(i)+'\n')

#寻找和为10的数的下标
def Find(lst):
    D={}
    for i in range(len(lst)):
        D[lst[i]]=D.get(0,i)
    for i in lst:
        if 10-i in D.keys()and i>5:
            print(D[i],D[10-i])

lst=GetWords(2)
Save(lst)
Find(lst)
