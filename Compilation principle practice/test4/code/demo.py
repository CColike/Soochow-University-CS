import copy

def read_grams():
    with open("./input.txt", "r") as f:
        grams = ["S->E"] + [i.replace("id", "i").split()[0] for i in f.readlines()]
    return grams

def get_begin_dot_grams(grams):
    dot_grams = []
    for gram in grams:
        for idx in range(gram.find("->") + 2, len(gram) + 1):
            dot_grams.append(gram[:idx] + "." + gram[idx:])
    return dot_grams

def get_same(dot_gram):
    if dot_gram[-1] == '.':
        return None
    if not dot_gram.split(".")[1][0].isupper():
        return None
    ans = [i for i in dot_grams if i[0] == dot_gram.split(".")[1][0] and i[3] == "."]
    return ans

def get_closure(i):
    res = list(set(i))
    for dot_gram in res:
        next = get_same(dot_gram)
        if next != None:
            res += [gram for gram in next if gram not in res]
    return list(set(res))

def get_non_stop():
    res = []
    for gram in grams:
        for c in gram:
            if not c.isupper() and c not in "->":
                res.append(c)
    res.append("$")
    return res

def get_chars():
    res2 = set()
    res1 = get_non_stop()
    for gram in grams:
        for c in gram:
            if c.isupper() and c not in "->":
                res2.add(c)
    return res1 + list(res2)

def get_next(item, c):
    next = []
    for i in item:
        if i[-1] == ".":
            continue
        x, y = i.split(".")
        if y[0] == c:
            next.append(x + y[0] + '.' + y[1:])
    return get_closure(next)

def get_items():
    items = [get_closure(["S->.E"])]
    chars = get_chars()
    goto = []
    idx = -1
    for i in items:
        idx += 1
        goto.append([None for _ in range(len(chars))])
        for c_idx in range(len(chars)):
            next = get_next(i, chars[c_idx])
            if len(next) == 0:
                continue
            # add next
            flag = True
            for check_idx in range(len(items)):
                if set(items[check_idx]) == set(next):
                    flag = False
                    goto[idx][c_idx] = check_idx
                    break
            if flag:
                items.append(next)
                goto[idx][c_idx] = len(items) - 1
    return items, goto, chars

def get_first():
    first = {}
    for gram in grams:
        x, y = gram.split("->")
        if not y[0].isupper():
            first[x] = first.get(x, "") + y[0]
    while True:
        cpy = copy.deepcopy(first)
        for gram in grams:
            x, y = gram.split("->")
            if y[0].isupper():
                first[x] = first.get(x, "") + first.get(y[0], "")
        same_flag = True
        for x, y in first.items():
            new_set, old_set = set(list(y)), set(list(cpy.get(x, "")))
            if new_set != old_set:
                same_flag = False
            first[x] = "".join(new_set)
        if same_flag:
            break
    return first

def get_follow(first):
    follow = {"S": "$"}
    while True:
        cpy = copy.deepcopy(follow)
        for gram in grams:
            x, y = gram.split("->")
            for idx in range(len(y) - 1):
                # A->…Ba…
                if y[idx].isupper() and not y[idx + 1].isupper():
                    follow[y[idx]] = follow.get(y[idx], "") + y[idx + 1]
                # A->…BC…
                if y[idx].isupper() and y[idx + 1].isupper():
                    follow[y[idx]] = follow.get(y[idx], "") + first.get(y[idx + 1], "").replace("e", "")
            # A->…B
            if y[-1].isupper():
                follow[y[-1]] = follow.get(y[-1], "") + follow.get(x[0], "")
            # A->…BC
            if len(y) >= 2 and y[-1].isupper() and y[-2].isupper():
                if first.get(y[-1], "").find("e") != -1:
                    follow[y[-2]] = follow.get(y[-2], "") + follow.get(x[0], "")
        # 去重
        same_flag = True
        for x, y in follow.items():
            new_set, old_set = set(list(y)), set(list(cpy.get(x, "")))
            if new_set != old_set:
                same_flag = False
            follow[x] = "".join(new_set)
        if same_flag:
            break
    return follow

def list_find(chars, c):
    for i in range(len(chars)):
        if chars[i] == c:
            return i
    return -1

def get_table(items, goto, chars):
    action = [[None for _ in range(len(chars))] for _ in range(len(items))]
    first = get_first()
    follow = get_follow(first)
    final_idx = list_find(chars, "$")
    for idx in range(len(items)):
        # 如果[A->a.]在Ii中，那么对FOLLOW(A)中的所有b，置action[i, b]为rj，j是产生式A->的编号
        for gram in items[idx]:
            if gram[-1] == ".":
                for b in follow[gram[0]]:
                    action[idx][list_find(chars, b)] = "r" + str(list_find(grams, gram[:-1]))
                continue
            # 如果[A->aab]在Ii中，并且goto(Ii, a ) = Ij，那么置action[i, a]为sj
            next_char_idx = list_find(chars, gram.split(".")[1][0])
            if goto[idx][next_char_idx] != None:
                action[idx][next_char_idx] = "s" + str(goto[idx][next_char_idx])
        # 如果[S->E.]在Ii中，那么置action[i, $] = acc
        if "S->E." in items[idx]:
            action[idx][final_idx] = "acc"
    # 对所有的非终结符A，如果goto(Ii, A) = Ij, 那么goto[i, A] = j
    for i in action:
        for j in range(len(chars)):
            if chars[j].isupper() and i[j] is not None:
                i[j] = i[j][1:]
    return action

class Node:
    def __init__(self, ch=None):
        self.ch = ch
        self.child = []

    def to_tree(self):
        if len(self.child) != 0:
            res = self.ch
            for i in self.child:
                res += i.to_tree()
            return "[" + res + "]"
        else:
            return "[" + self.ch + "]"

def analyse(action, sentence):
    sentence = sentence.replace("id", "i")
    sentence = sentence + "$"
    stack = [(None, 0, None)]
    while (True):
        act = action[stack[-1][1]][list_find(chars, sentence[0])]
        if act[0] == "s":
            stack.append((sentence[0], int(act[1:]), Node(sentence[0])))
            sentence = sentence[1:]
        if act[0] == "r":
            gram = grams[int(act[1:])]
            new_node = Node(gram[0])
            for i in range(len(gram.split("->")[1])):
                temp_node = stack.pop()[2]
                new_node.child.insert(0, temp_node)
            stack.append((gram[0], int(action[stack[-1][1]][list_find(chars, gram[0])]), new_node))
        if act[0] == "a":
            break
    return stack[1][2].to_tree().replace("i", "id")

if __name__ == "__main__":
    grams = read_grams()
    for idx in range(len(grams)):
        print(str(idx)+":",grams[idx])
    print()
    dot_grams = get_begin_dot_grams(grams)
    items, goto, chars = get_items()
    for idx in range(len(items)):
        print("I"+str(idx)+":",items[idx])
    print("goto:")
    print("chars:",chars)
    for idx in range(len(goto)):
        print("I"+str(idx)+":",goto[idx])
    action = get_table(items, goto, chars)
    print("action:")
    print("chars:", chars)
    for idx in range(len(action)):
        print("I" + str(idx) + ":", action[idx])
    res = analyse(action, "id+(id+id)*id")
    print(res)
