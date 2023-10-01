

def get_next(m,k,mark,types):
    idx=-1
    for i in m.get(k,[]):
        if i[0]==mark:
            idx=i[1]
    if(idx==-1):
        return -1
    for i in range(len(types)):
        if idx in types[i][1]:
            return i

def types_to_turns(types,marks,beginn,endd):
    begin_idx=[]
    end_idx=[]
    for i in range(len(types)):
        if len(types[i][1]&set(beginn))!=0:
            begin_idx.append(i)
        if len(types[i][1]&set(endd))!=0:
            end_idx.append(i)
    turns=[]
    marks=list(marks)
    for i in range(len(types)):
        for j in range(len(marks)):
            turns.append((i,marks[j],types[i][0][j]))
    return turns,begin_idx,end_idx


def min_DFA(dfa_list,begin_idx,end_idx):
    m = dict()
    marks = set()
    n=-1
    for i in dfa_list:
        m[i[0]] = m.get(i[0], list())
        m[i[0]].append((i[1], i[2]))
        marks.add(i[1])
        n=max(n,i[0],i[2])
    types=[]
    a=set()
    b=set()
    for i in range(n+1):
        if i not in end_idx:
            a.add(i)
        else:
            b.add(i)
    types.append((None,a))
    types.append((None,b))#一种当前最优划分
    while(True):
        new_types=[]
        for type in types:#枚举各个状态，检查每个状态中是否有违规的（不一样）
                          #在一个状态中，不断分出新的状态，作为下一次的types
            new_types_temp=[]
            for i in type[1]:
                point=[]
                for mark in marks:
                    point.append(get_next(m,i,mark,types))
                flag=0#表示没有找到相同的point
                for p in range(len(new_types_temp)):#枚举当前type中已经存在的指向，如果新指向已经存在，那么将这个i放到new——types中对应的type中
                                #否则（新指向不存在)，那么添加一个新type，将这个i放到new——types的新的type中
                    if new_types_temp[p][0]==point:
                        new_types_temp[p][1].add(i)
                        flag=1
                        break
                if(flag==0):
                    new_types_temp.append((point,{i}))
            new_types=new_types+new_types_temp
        if(types==new_types):
            break
        else:
            types=new_types
    return types_to_turns(types,marks,begin_idx,end_idx)

if __name__=='__main__':
    dfa_list=[]
    begin_idx=[]
    end_idx=[]
    with open("input.txt", "r", encoding="utf-8") as f:
        s=f.readline()
        while(s!=''):
            x,ch,y=s.split()
            if(x=='start'):
                beginn=s.split()[2:]
                endd=f.readline().split()[2:]
                for i in beginn:
                    begin_idx.append(int(i))
                for i in endd:
                    end_idx.append(int(i))
                break

            x=int(x)
            y=int(y)
            dfa_list.append((x,ch,y))
            s=f.readline()
    turns,begin_idx,end_idx=min_DFA(dfa_list,begin_idx,end_idx)
    # print(turns,begin_idx,end_idx)

    with open("output.txt","w",encoding="utf-8")as f:
        for i in turns:
            f.write(str(i[0])+' '+i[1]+' '+str(i[2])+'\n')
        f.write("start state: ")
        for i in begin_idx:
            f.write(str(i)+' ')
        f.write("\naccepting state: ")
        for i in end_idx:
            f.write(str(i)+' ')