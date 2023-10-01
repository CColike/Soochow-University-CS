i = 0

class Node:
    def __init__(self, ch=None):
        self.ch = ch
        self.child = []

    def to_tree(self):
        if len(self.child)!=0:
            res=self.ch
            for i in self.child:
                res+=i.to_tree()
            return "["+res+"]"
        else:
            return "["+self.ch+"]"

def E(e):
    print("E → TE'")
    t, e_ = Node('T'), Node("E'")
    e.child += [t, e_]
    T(t)
    E_(e_)

def E_(e_):
    global i
    if sentence_list[i] == '+':
        i += 1
        print("E' → +TE'")
        plus, t, e_1 = Node("+"), Node("T"), Node("E'")
        e_.child += [plus, t, e_1]
        T(t)
        E_(e_1)
    else:
        print("E'->e")
        e_.child.append(Node('e'))

def T(t):
    print("T → F T'")
    f, t_ = Node("F"), Node("T'")
    t.child += [f, t_]
    F(f)
    T_(t_)

def T_(t_):
    global i
    if sentence_list[i] == "*":
        i += 1
        print("T\' → * F T\' ")
        mul, f, t_1 = Node("*"), Node("F"), Node("T'")
        t_.child += [mul, f, t_1]
        F(f)
        T_(t_1)
    else:
        print("T' → e")
        t_.child+=[Node("e")]

def F(f):
    global i
    if sentence_list[i] == "(":
        i += 1
        print("F → (E)")
        lb, e, rb = Node("("), Node("E"), Node(")")
        f.child += [lb, e, rb]
        E(e)
        i += 1
    elif sentence_list[i] == "id":
        i += 1
        print("F → id")
        id = Node("id")
        f.child += [id]
    else:
        print("Error!Check the sentence!")
        exit()

if __name__ == '__main__':
    sentence = "id + id * id"
    sentence_list = sentence.split() + ["#"]
    e = Node('E')
    E(e)
    if sentence_list[i]!="#":
        print("Error!Check the sentence!")
        exit()
    print(e.to_tree())