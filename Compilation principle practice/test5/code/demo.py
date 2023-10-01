def read_grams():
    with open("input.txt", "r")as f:
        grams = []
        for gram in f.readlines():
            x, y = gram.split("->")
            # grams.append((" ".join(gram.split()[:-1]),float(gram.split()[-1])))
            grams.append((x[:-1].split(), y[1:].split()[:-1], float(y.split()[-1])))
        return grams

def get_p(gram):
    for i in grams:
        if i[:-1] == gram[:-1]:
            return i[-1]

def get_before(g):
    res = []
    for gram in grams:
        if len(gram[1]) == 1 and gram[1][0] == g[0][0]:
            res.append([gram[0], gram[1], g[2] * gram[2], (-1, -1), (-1, -1)])  # 从本组找
    return res

def get_closure(gs):
    '''线性递归地找一元匹配闭包'''
    if len(gs) == 0:
        return []
    for g in gs:
        before = get_before(g)
        gs += before  # 动态循环
    '''选取每个表达式的最大概率（去重）'''
    gs.sort(key=lambda x: -x[2])
    res = []
    for g in gs:
        flag = True
        for r in res:
            if r[0] == g[0]:
                flag = False
        if flag:
            res.append(g)
    return res

def get_leaf():
    for dp_idx in range(length):
        for gram in grams:
            if len(gram[1]) == 1 and gram[1][0] == sentence[dp_idx]:
                dp[dp_idx][dp_idx].append(list(gram) + [(-2, -2), (-2, -2)])  # 树叶词本身
    for idx in range(length):
        dp[idx][idx] = get_closure(dp[idx][idx])

def get_branch(X, Y):
    if X == [] or Y == []:
        return []
    res = []
    for x in X:
        for y in Y:
            after = x[0] + y[0]
            for gram in grams:
                if len(gram[1]) == 2 and gram[1] == after:
                    res.append([gram[0], gram[1], x[2] * y[2] * gram[2]])
    return res

def get_branches():
    for d in range(1, length):
        for i in range(length - d):
            j = i + d
            '''get dp[i][j]=dp[i][k]+dp[k+1][j]    '''
            for k in range(i, j):
                new_nodes = get_branch(dp[i][k], dp[k + 1][j])
                dp[i][j] += [new_node + [(i, k), (k + 1, j)] for new_node in new_nodes]
            '''closure'''
            dp[i][j] = get_closure(dp[i][j])

def get_tree(begin_idx, end_idx, s):
    max_p = 0
    max_gram = []
    res1 = "["
    res2 = "]"
    if s == " ":
        for gram in dp[begin_idx][end_idx]:
            if max_p < gram[2]:
                max_p = gram[2]
                max_gram = gram
    else:
        for gram in dp[begin_idx][end_idx]:
            if gram[0][0] == s:
                max_gram = gram
    res1 += max_gram[0][0] + "["
    res2 = "]" + res2

    while max_gram[3] == (-1, -1):
        for gram in dp[begin_idx][end_idx]:
            if gram[0][0] == max_gram[1][0]:
                max_gram = gram
                res1 = res1 + "[" + max_gram[0][0]
                res2 = "]" + res2
                break
    if max_gram[3] == (-2, -2):
        return res1 + "[" + max_gram[1][0] + "]" + res2
    return res1 + get_tree(max_gram[3][0], max_gram[3][1], max_gram[1][0]) + get_tree(max_gram[4][0], max_gram[4][1],
                                                                                      max_gram[1][1]) + res2
grams = read_grams()
sentence = "fish people fish tanks"
sentence = sentence.split(" ")
length = len(sentence)
dp = [[[] for _ in range(length)] for _ in range(length)]

# print(grams)
'''处理dp[i][i]叶子结点'''
get_leaf()
# print(dp)
'''处理非叶子节点(枝干)'''
get_branches()
# for i in dp:
#     print(i)
print(get_tree(0, len(sentence) - 1, " "))
