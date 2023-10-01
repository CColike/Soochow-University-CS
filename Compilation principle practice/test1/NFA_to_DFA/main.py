import copy

same_set=set()
def get_category(m,k):#统计k的同系 放到same_set
    lis=m.get(k,list())
    same_set.add(k)
    for i in lis:
        if(i[0]=='e' and i[1] not in same_set):
            get_category(m,i[1])

def get_next(m,k,ch):
    lis=m.get(k,list())
    for i in lis:
        if(i[0]==ch):
            return i[1]
    return -1

def nfa_to_dfa(nfa_list,beginn):
    m=dict()
    marks=set()
    for i in nfa_list:
        m[i[0]]=m.get(i[0],list())
        m[i[0]].append((i[1], i[2]))
        marks.add(i[1])
    marks.discard('e')
    marks=list(marks)#去除e的符号集
    turns=[]
    k=0
    same_set.clear()#同系的点
    get_category(m, beginn)#获取和beginn同系的点
    saved_idxs=[copy.deepcopy(same_set),]#等待去处理的点的集合的列表
    next_idxs=set()
    t=0#当前状态编号
    while(t<len(saved_idxs)):
        same_idxs=saved_idxs[t]
        for mark in marks:#枚举符号
            next_idxs.clear()
            for same_idx in same_idxs:#枚举本系的点，寻找mark的出路
                next_idx=get_next(m,same_idx,mark)
                if(next_idx!=-1):
                    next_idxs.add(next_idx)
            same_set.clear()
            for i in next_idxs:
                get_category(m,i)
            flag=0
            for i in range(len(saved_idxs)):
                if saved_idxs[i]==same_set:
                    turns.append((t,mark,i))
                    flag=1
            if(flag==0):
                saved_idxs.append(copy.deepcopy(same_set))
                turns.append((t,mark,k+1))
                k+=1
        t+=1
    return saved_idxs,turns

if __name__=='__main__':
    nfa_list=[]
    with open("input.txt", "r", encoding="utf-8") as f:
        s=f.readline()
        while(s!=''):
            x,ch,y=s.split()
            if(x=='start'):
                beginn=int(y)
                endd=int(f.readline().split()[2])
                break
            x=int(x)
            y=int(y)
            nfa_list.append((x,ch,y))
            s=f.readline()

    status,dfa_list=nfa_to_dfa(nfa_list,beginn)
    new_begin=[]
    new_end=[]
    for i in range(len(status)):
        if beginn in status[i]:
            new_begin.append(i)
        if endd in status[i]:
            new_end.append(i)

    # print(dfa_list,new_begin,new_end)
    with open("output.txt","w",encoding="utf-8")as f:
        for i in dfa_list:
            f.write(str(i[0])+' '+i[1]+' '+str(i[2])+'\n')
        f.write("start state: ")
        for i in new_begin:
            f.write(str(i)+' ')
        f.write("\naccepting state: ")
        for i in new_end:
            f.write(str(i)+' ')