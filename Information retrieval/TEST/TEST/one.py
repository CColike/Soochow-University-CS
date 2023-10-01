"""
读取 one_1.json 、 one_2.json 、 one_3.json 和 one_4.json 四个json格式文件中的数据，其中， 有的文件中有 result 字段，格式为数组。
要求:
    1. print出四个文件中result数组的交集，并将数组中的数据按行存入文件one_5.txt
    2. print出四个文件中result数组的并集，并将数组中的数据按行存入文件one_6.txt
"""

import json
InterSection=set()
Union=set()

#读取文件并同时计算交集和并集
for i in range(1,5):
    with open("data/one_"+str(i)+".json","r",encoding='utf-8-sig')as f:
        json_dict=json.load(f)
        NewSet=set(json_dict['result']) if json_dict['result']!=None else set()   #空集特殊处理
        Union=Union.union(NewSet)
        InterSection=InterSection.intersection(NewSet) if i!=1 else NewSet       #第一个特殊集合处理

#print结果
print("InterSection=",InterSection)
print("Union=",Union)

#保存结果
with open("data/one_5.json","w",encoding="utf-8-sig")as f:
    f.write(str(InterSection))
with open("data/one_6.json","w",encoding="utf-8-sig")as f:
    f.write(str(Union))
