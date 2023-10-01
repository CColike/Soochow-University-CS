#! /usr/bin/env python
# coding=utf-8
import ply.yacc as yacc
from py_lex import *
from node import node, num_node


# YACC for parsing Python

def simple_node(t, name):
    t[0] = node(name)
    for i in range(1, len(t)):
        t[0].add(node(t[i]))
    return t[0]


def p_program(t):
    '''program : statements'''
    if len(t) == 2:
        t[0] = node('[PROGRAM]')
        t[0].add(t[1])


def p_statements(t):
    '''statements : statements statement
                  | statement'''
    if len(t) == 3:
        t[0] = node('[STATEMENTS]')
        t[0].add(t[1])
        t[0].add(t[2])
    elif len(t) == 2:
        t[0] = node('[STATEMENTS]')
        t[0].add(t[1])


def p_statement(t):
    ''' statement : assignment
                  | operation
                  | print
                  | if_elif_else
                  | while
                  | for
                  | BREAK'''
    if len(t) == 2:  # 判断是否为'BREAK'
        if not isinstance(t[1], str):
            t[0] = node('[STATEMENT]')
            t[0].add(t[1])
        else:  # 为BREAK
            t[0] = node('[STATEMENT]')
            t[0].add(node('[BREAK]'))


def p_assignment(t):
    '''assignment : VARIABLE '=' NUMBER
                  | VARIABLE '[' expr ']' '=' NUMBER
                  | VARIABLE '=' VARIABLE
                  | VARIABLE '=' VARIABLE '[' expr ']'
                  | VARIABLE '=' num_list'''
    if len(t) == 4:
        if isinstance(t[3], str):  # NUMBER or VARIABLE
            if ord('0') <= ord(t[3][0]) <= ord('9'):  # NUMBER
                t[0] = node('[ASSIGNMENT]')
                t[0].add(node(t[1]))
                t[0].add(node(t[2]))
                t[0].add(num_node(t[3]))
            else:  # VARIABLE
                t[0] = node('[ASSIGNMENT]')
                t[0].add(node(t[1]))
                t[0].add(node(t[2]))
                t[0].add(node(t[3]))
        else:  # num_list
            t[0] = node('[ASSIGNMENT]')
            t[0].add(node(t[1]))
            t[0].add(node(t[2]))
            t[0].add(t[3])
    elif len(t) == 7:
        if t[2] == '[':  # NUMBER
            t[0] = node('[ASSIGNMENT]')
            t[0].add(node(t[1]))
            t[0].add(t[3])
            t[0].add(node(t[5]))
            t[0].add(num_node(t[6]))
        else:  # VARIABLE '[' expr ']'
            t[0] = node('[ASSIGNMENT]')
            t[0].add(node(t[1]))
            t[0].add(node(t[2]))
            t[0].add(node(t[3]))
            t[0].add(t[5])


def p_num_list(t):
    '''num_list : '[' numbers ']' '''
    if len(t) == 4:
        t[0] = node('[NUM_LIST]')
        t[0].add(t[2])


def p_numbers(t):
    '''numbers : NUMBER
               | numbers ',' NUMBER'''
    if len(t) == 2:
        t[0] = node('[NUMBERS]')
        t[0].add(num_node(t[1]))
    elif len(t) == 4:
        t[0] = node('[NUMBERS]')
        t[0].add(t[1])
        t[0].add(num_node(t[3]))


def p_operation(t):
    '''operation : VARIABLE '=' expr
                 | VARIABLE '[' expr ']' '=' expr'''
    if len(t) == 4:
        t[0] = node('[OPERATION]')
        t[0].add(node(t[1]))
        t[0].add(node(t[2]))
        t[0].add(t[3])
    elif len(t) == 7:
        t[0] = node('[OPERATION]')
        t[0].add(node(t[1]))
        t[0].add(t[3])
        t[0].add(node(t[5]))
        t[0].add(t[6])


def p_expr(t):
    '''expr : expr '+' term
            | expr '-' term
            | expr DIV expr
            | term
            | LEN '(' factor ')' '''
    if len(t) == 4:
        t[0] = node('[EXPRESSION]')
        t[0].add(t[1])
        t[0].add(node(t[2]))
        t[0].add(t[3])
    elif len(t) == 2:
        t[0] = node('[EXPRESSION]')
        t[0].add(t[1])
    elif len(t) == 5:
        t[0] = node('[EXPRESSION]')
        t[0].add(node('[LEN]'))
        t[0].add(t[3])


def p_term(t):
    '''term : term '*' factor
            | term '/' factor
            | factor'''
    if len(t) == 4:
        t[0] = node('[TERM]')
        t[0].add(t[1])
        t[0].add(node(t[2]))
        t[0].add(t[3])
    elif len(t) == 2:
        t[0] = node('[TERM]')
        t[0].add(t[1])


def p_factor(t):
    '''factor : NUMBER
              | VARIABLE
              | VARIABLE '[' expr ']'
              | '(' expr ')' '''
    if len(t) == 2:
        if ord('0') <= ord(t[1][0]) <= ord('9'):  # NUMBER
            t[0] = node('[FACTOR]')
            t[0].add(num_node(t[1]))
        else:  # VARIABLE
            t[0] = node('[FACTOR]')
            t[0].add(node(t[1]))
    elif len(t) == 4:
        t[0] = node('[FACTOR]')
        t[0].add(t[2])
    elif len(t) == 5:
        t[0] = node('[FACTOR]')
        t[0].add(node(t[1]))
        t[0].add(t[3])


def p_print(t):
    '''print : PRINT '(' VARIABLE ')' '''
    if len(t) == 5:
        t[0] = node('[PRINT]')
        t[0].add(node(t[3]))


def p_condition(t):
    '''condition : factor '>' factor
                 | factor '<' factor
                 | factor LE factor
                 | factor GE factor'''
    if len(t) == 4:
        t[0] = node('[CONDITION]')
        t[0].add(t[1])
        t[0].add(node(t[2]))
        t[0].add(t[3])


def p_if_elif_else(t):
    '''if_elif_else : if
                    | if elif else'''
    if len(t) == 2:
        t[0] = node('[IF_ELIF_ELSE]')
        t[0].add(t[1])
    elif len(t) == 4:
        t[0] = node('[IF_ELIF_ELSE]')
        t[0].add(t[1])
        t[0].add(t[2])
        t[0].add(t[3])


def p_if(t):
    '''if : IF '(' condition ')' '{' statements '}' '''
    if len(t) == 8:
        t[0] = node('[IF]')
        t[0].add(t[3])
        t[0].add(t[6])


def p_elif(t):
    '''elif : ELIF '(' condition ')' '{' statements '}' '''
    if len(t) == 8:
        t[0] = node('[ELIF]')
        t[0].add(t[3])
        t[0].add(t[6])


def p_else(t):
    '''else : ELSE '{' statements '}' '''
    if len(t) == 5:
        t[0] = node('[ELSE]')
        t[0].add(t[3])


def p_while(t):
    '''while : WHILE '(' condition ')' '{' statements '}' '''
    if len(t) == 8:
        t[0] = node('[WHILE]')
        t[0].add(t[3])
        t[0].add(t[6])


def p_for(t):
    '''for : FOR '(' conditions ')' '{' statements '}' '''
    if len(t) == 8:
        t[0] = node('[FOR]')
        t[0].add(t[3])
        t[0].add(t[6])


def p_conditions(t):
    '''conditions : assignment ';' condition ';' increment'''
    if len(t) == 6:
        t[0] = node('[CONDITIONS]')
        t[0].add(t[1])
        t[0].add(t[3])
        t[0].add(t[5])


def p_increment(t):
    '''increment : VARIABLE INC'''
    if len(t) == 3:
        t[0] = node('[INCREMENT]')
        t[0].add(node(t[1]))
        t[0].add(node(t[2]))


def p_error(t):
    print("Syntax error at '%s'" % t.value)


yacc.yacc()
