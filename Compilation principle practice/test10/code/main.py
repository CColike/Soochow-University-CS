#! /usr/bin/env python
#coding=utf-8
from py_yacc import yacc
from util import clear_text
from translation import Tran

def get_tree(node):
    global ans
    if node:
        ans+=str(node.getdata()).replace("[", "").replace("]", "").replace("/'", "").replace('_','-')
    children=node.getchildren()
    if children:
        for child in children:
            ans+='['
            get_tree(child)
            ans+=']'

text=clear_text(open('stu.py','r').read())
# syntax parse
root=yacc.parse(text)
root.print_node(0)
# get tree string
ans=""
get_tree(root)
print("["+ans+"]")
# translation
t=Tran()
t.trans(root)
print(t.v_table)