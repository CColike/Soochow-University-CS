import numpy as np
import re
d1=[3,56,8,9,79,16,215,25,69,19,32,1,1926,55,39]
d2={3:0,56:1,8:2,9:3,79:4,16:5,215:6,25:7,69:8,19:9 ,32:10,1:11,1926:12,55:13,39:14}

m=np.zeros((15,15),dtype=int)

for i in range(15):
    m[i][i]=1



with open ("data/data.txt")as f:
    for i in f.readlines():
        t=re.findall(r'\d+',i)
        #print(t)
        for i in range(1,len(t)):
            m[d2[int(t[0])]][d2[int(t[i])]]=1

mt=np.transpose(m)

a=np.ones((15,1),dtype=float)
for i in range(15):
    a[i][0]=1/(15**0.5)


last_a=last_h=-1000007

while(True):
    h=np.matmul(m,a)
    tot=0
    for i in h:
        tot+=i**2
    tot=tot**0.5
    for i in range(15):
        h[i]/=tot

    a=np.matmul(mt,h)
    tot = 0
    for i in a:
        tot+=i**2
    tot=tot**0.5
    for i in range(15):
        a[i]/=tot

    #print(a)
    #print(h)

    a_std=np.std(a,ddof=1)
    h_std=np.std(h,ddof=1)
    if(abs(a_std-last_a)<1e-5 and abs(h_std-last_h)<1e-5):
        break

    last_a=a_std
    last_h=h_std


aa=[]
hh=[]
for i in range(15):
    aa.append((i,a[i]))
    hh.append((i,h[i]))

aa.sort(key=lambda x:-x[1])
hh.sort(key=lambda x:-x[1])

#print(aa)
#print(hh)

print("入度从多到少:")
for i in aa:
    print(d1[i[0]])

print("出度从多到少:")
for i in hh:
    print(d1[i[0]])

with open("柯骅2027405033Result.txt","w",encoding='utf-8') as f:
    f.write("入度从多到少:\n")
    for i in aa:
        f.write(str(d1[i[0]])+'\n')
    f.write("出度从多到少:\n")
    for i in hh:
        f.write(str(d1[i[0]])+'\n')