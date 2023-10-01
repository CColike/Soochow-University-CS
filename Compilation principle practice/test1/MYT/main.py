def add_dot(s):
    ans=''
    for i in range(len(s)-1):
        if ('a'<=s[i]<='z' or s[i]==')' or s[i]=='*') and ('a'<=s[i+1]<='z' or s[i+1]=='('):
            ans=ans+s[i]+'.'
        else:
            ans=ans+s[i]
    ans+=s[-1]
    return ans

def get_por(c):
    if(c=='*'):
        return 3
    if(c=='|'):
        return 2
    if(c=='.'):
        return 1
    if(c=='('):
        return 0

def suffix(s):
    b=list()
    ans=''
    for i in s:
        if 'a'<=i<='z':
            ans+=i
        elif i==')':
            while(len(b)>0 and b[-1]!='('):
                ans+=b[-1]
                b.pop()
            b.pop()
        elif i=='(':
            b.append('(')
        else:
            while(len(b)!=0 and get_por(b[-1])>get_por(i)):
                ans+=b[-1]
                b.pop()
            b.append(i)

    while(len(b)!=0):
        ans+=b[-1]
        b.pop()
    return ans

def suf_to_nfa(suf):
    ans_list=[]
    b=[]
    k=0 #k:已经用过多少个了
    for i in range(len(suf)):
        ch=suf[i]
        if 'a'<=ch<='z':
            b.append((ch,-1,-1))
        elif ch=='*':
            if(b[-1][1]==-1):
                k+=2
                node=(b[-1][0],k-1,k)
                b.pop()
                b.append(node)
                ans_list.append((k-1,'e',k))
            node=b[-1]
            b.pop()
            ans_list.append((node[2], 'e', k + 2))
            ans_list.append((k+1, 'e', k + 2))
            ans_list.append((node[2], 'e', node[1]))
            ans_list.append((k+1, 'e', node[1]))
            b.append(('!',k+1,k+2))
            k+=2
        elif ch=='|':
            if b[-1][1]==-1 and b[-2][1]==-1:
                node1=b[-1]
                node2=b[-2]
                b.pop()
                b.pop()
                ans_list.append((k+1,node1[0],k+2))
                ans_list.append((k+1,node2[0],k+3))
                ans_list.append((k + 2, 'e', k + 4))
                ans_list.append((k + 3, 'e', k + 4))
                ans_list.append((k + 4, 'e', k + 6))
                ans_list.append((k + 5, 'e', k + 1))
                b.append(('!',k+5,k+6))
                k+=6
            else:
                if (b[-1][1] == -1):
                    node = b[-1]
                    b.pop()
                    b.append((node[0], k + 1, k + 2))
                    ans_list.append((k + 1, node[0], k + 2))
                    k += 2
                if (b[-2][1] == -1):
                    node = b[-2]
                    b.pop()
                    b.append((node[0], k + 1, k + 2))
                    ans_list.append((k + 1, node[0], k + 2))
                    k += 2
                node1=b[-1]
                node2=b[-2]
                b.pop()
                b.pop()
                ans_list.append((k+1,'e',node1[1]))
                ans_list.append((k+1,'e',node2[1]))
                ans_list.append((node1[2],'e',k+2))
                ans_list.append((node2[2],'e',k+2))
                b.append(('!',k+1,k+2))
                k+=2
        else:
            node1=b[-1]
            node2=b[-2]
            b.pop()
            b.pop()
            if node1[1]==-1:
                node1=(node1[0],k+1,k+2)
                ans_list.append((k+1,node1[0],k+2))
                k+=2
            if node2[1]==-1:
                node2=(node2[0],k+1,k+2)
                ans_list.append((k+1,node2[0],k+2))
                k+=2
            ans_list.append((node2[2],'e',node1[1]))
            b.append(('!',node2[1],node1[2]))
    return (ans_list,b[0][1],b[0][2])

def re_to_nfa(reg):
    # print(add_dot(reg))
    suf=suffix(add_dot(reg))
    # print(suf)
    ans_list=suf_to_nfa(suf)
    return ans_list

if __name__=='__main__':
    with open("input.txt", "r", encoding="utf-8") as f:
        reg=f.read()
    # reg="(ab)*|(ab)"
    ans_list,begin_node,end_node=re_to_nfa(reg)
    # print(ans_list,begin_node,end_node)

    with open("output.txt","w",encoding="utf-8")as f:
        for i in ans_list:
            f.write(str(i[0])+' '+i[1]+' '+str(i[2])+'\n')
        f.write("start state: "+str(begin_node)+'\n')
        f.write("accepting state: "+str(end_node)+'\n')