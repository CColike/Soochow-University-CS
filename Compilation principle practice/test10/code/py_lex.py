#! /usr/bin/env python
# coding=utf-8
import ply.lex as lex

# LEX for parsing Python

# Tokens
tokens = ('VARIABLE', 'NUMBER', 'CLASS', 'SELF', 'STR', 'PRINT', 'DEF')
literals = ['=', '+', '-', '*', '(', ')', '{', '}', '<', '>', ',', '.']


# Define of tokens

def t_NUMBER(t):
    r'[0-9]+'
    return t


def t_STR(t):
    r'\'\w*\''
    return t


def t_PRINT(t):
    r'(?<!\.)print(?=\()'
    return t


def t_DEF(t):
    r'def'
    return t


def t_CLASS(t):
    r'class'
    return t


def t_SELF(t):
    r'self'
    return t


def t_VARIABLE(t):
    r'[a-zA-Z\$_][a-zA-Z\d_]*'
    return t


# Ignored
t_ignore = " \t"


def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


lex.lex()
