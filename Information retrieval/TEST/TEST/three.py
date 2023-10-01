"""
要求:
    1. 使用python的requests库发送请求，获取数据
    2. 统计要求1获取的100篇文章中，包含多少种文章主题topics，每种主题有多少篇文章，以如下字 典的形式print 输出
"""

import requests
import json

#读取文章
def Get():
    url = "http://106.15.232.22:8897/search"
    d={"index":"write","query":"地震"}
    r = requests.post(url, json=d)
    t=json.loads(r.content.decode())["hits"]["hits"]   #t即为100篇文章
    return t

#计算各类topics数量
def cnt(txts):
    D={}
    for pages in txts:#枚举txts中的每一篇文章寻找topics
        topics=pages["_source"]["topics"]
        D[topics]=D.get(topics,0)
        D[topics]+=1
    return D

txts=Get()
ans=cnt(txts)
#按格式转换成json输出
print(json.dumps(ans,ensure_ascii=False,indent=5))