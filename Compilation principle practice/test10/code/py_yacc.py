#! /usr/bin/env python
# coding=utf-8
import ply.yacc as yacc
from py_lex import *
from node import node, num_node


# YACC for parsing Python

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
                  | function
                  | run_function
                  | class'''
    if len(t) == 2:
        t[0] = node(['STATEMENT'])
        t[0].add(t[1])





def p_operation(t):
    '''operation : VARIABLE '=' expression
                 | self '=' expression
                 | VARIABLE '+' '=' expression
                 | VARIABLE '-' '=' expression
                 | VARIABLE '[' expression ']' '=' expression '''
    if len(t) == 4:
        if not isinstance(t[1], node):
            ''' self '=' expression'''
            t[0] = node('[OPERATION]')
            t[0].add(node(t[1]))
            t[0].add(node(t[2]))
            t[0].add(t[3])
        else:
            '''VARIABLE '=' expression'''
            t[0] = node('[OPERATION]')
            t[0].add(t[1])
            t[0].add(node(t[2]))
            t[0].add(t[3])
    elif len(t) == 5:
        '''VARIABLE '+'/'-' '=' expression'''
        t[0] = node('[OPERATION]')
        t[0].add(node(t[1]))
        t[0].add(node(t[2] + t[3]))
        t[0].add(t[4])
    elif len(t) == 7:
        '''VARIABLE '[' expression ']' '=' expression'''
        t[0] = node('[OPERATION]')
        t[0].add(node(t[1]))
        t[0].add(t[3])
        t[0].add(node(t[5]))
        t[0].add(t[6])


def p_assignment(t):
    '''assignment : VARIABLE '=' NUMBER
                  | self '=' VARIABLE
                  | VARIABLE '=' VARIABLE
                  | VARIABLE '[' expression ']' '=' NUMBER
                  | VARIABLE '=' VARIABLE '[' expression ']'
                  | VARIABLE '=' VARIABLE '(' expressions ')' '''
    if len(t) == 4:
        if isinstance(t[1], node):
            t[0] = node('[ASSIGNMENT]')
            t[0].add(t[1])
            t[0].add(node(t[2]))
            t[0].add(node(t[3]))
        elif isinstance(t[3], str):
            if t[3][0].isdigit():
                t[0] = node('[ASSIGNMENT]')
                t[0].add(node(t[1]))
                t[0].add(node(t[2]))
                t[0].add(num_node(t[3]))
            else:
                t[0] = node('[ASSIGNMENT]')
                t[0].add(node(t[1]))
                t[0].add(node(t[2]))
                t[0].add(node(t[3]))
    elif len(t) == 7:
        if t[2] == '[':
            t[0] = node('[ASSIGNMENT]')
            t[0].add(node(t[1]))
            t[0].add(t[3])
            t[0].add(node(t[5]))
            t[0].add(num_node(t[6]))
        elif t[5].getdata() == '[EXPRESSIONS]':
            t[0] = node('[ASSIGNMENT]')
            t[0].add(node(t[1]))
            t[0].add(node(t[2]))
            t[0].add(node(t[3]))
            t[0].add(t[5])
        elif t[5].getdata() == '[EXPRESSION]':
            t[0] = node('[ASSIGNMENT]')
            t[0].add(node(t[1]))
            t[0].add(node(t[2]))
            t[0].add(node(t[3]))
            t[0].add(t[5])

def p_expressions(t):
    '''expressions :
                   | expression
                   | expressions ',' expression'''
    if len(t) == 1:
        '''(empty)'''
        t[0] = node('[EXPRESSIONS]')
        t[0].add(node('[NONE]'))
    elif len(t) == 2:
        '''expression'''
        t[0] = node('[EXPRESSIONS]')
        t[0].add(t[1])
    elif len(t) == 4:
        '''expressions ',' expression'''
        t[0] = node('[EXPRESSIONS]')
        t[0].add(t[1])
        t[0].add(t[3])


def p_expression(t):
    '''expression : term
                  | expression '+' term
                  | expression '-' term '''
    if len(t) == 2:
        '''term'''
        t[0] = node('[EXPRESSION]')
        t[0].add(t[1])
    elif len(t) == 4:
        '''expression '+'/'-' term'''
        t[0] = node('[EXPRESSION]')
        t[0].add(t[1])
        t[0].add(node(t[2]))
        t[0].add(t[3])


def p_term(t):
    '''term : factor
            | term '*' factor
            | term '/' factor '''
    if len(t) == 2:
        '''factor'''
        t[0] = node('[TERM]')
        t[0].add(t[1])
    elif len(t) == 4:
        '''term '*'/'/' factor'''
        t[0] = node('[TERM]')
        t[0].add(t[1])
        t[0].add(node(t[2]))
        t[0].add(t[3])


def p_factor(t):
    '''factor : STR
              | self
              | NUMBER
              | VARIABLE
              | '(' expression ')'
              | VARIABLE '[' expression ']' '''
    if len(t) == 2:
        if isinstance(t[1], node):
            '''self'''
            t[0] = node('[FACTOR]')
            t[0].add(t[1])
        elif t[1][0] == "'" and t[1][-1] == "'":
            '''STR'''
            t[0] = node('[FACTOR]')
            t[0].add(node(t[1]))
        elif t[1][0].isdigit():
            '''NUMBER'''
            t[0] = node('[FACTOR]')
            t[0].add(num_node(t[1]))
        else:
            '''VARIABLE'''
            t[0] = node('[FACTOR]')
            t[0].add(node(t[1]))
    elif len(t) == 4:
        ''' '(' expression ')' '''
        t[0] = node('[FACTOR]')
        t[0].add(t[2])
    elif len(t) == 5:
        ''' VARIABLE '[' expression ']' '''
        t[0] = node('[FACTOR]')
        t[0].add(node(t[1]))
        t[0].add(t[3])


def p_print(t):
    '''print : PRINT '(' variables ')' '''
    if len(t) == 5:
        t[0] = node('[PRINT]')
        t[0].add(t[3])


def p_function(t):
    '''function : DEF VARIABLE '(' variables ')' '{' statements '}'
                | DEF VARIABLE '(' SELF ')' '{' statements '}'
                | DEF VARIABLE '(' SELF ',' variables ')' '{' statements '}' '''
    if len(t) == 9:
        if t[4] == 'self':
            ''' DEF VARIABLE '(' SELF ')' '{' statements '}' '''
            t[0] = node('[FUNCTION]')
            t[0].add(node(t[2]))
            t[0].add(node('[SELF]'))
            t[0].add(t[7])
        elif t[4].getdata() == '[VARIABLES]':
            ''' DEF VARIABLE '(' variables ')' '{' statements '}' '''
            t[0] = node('[FUNCTION]')
            t[0].add(node(t[2]))
            t[0].add(t[4])
            t[0].add(t[6])
            t[0].add(t[9])
    elif len(t) == 11:
        ''' DEF VARIABLE '(' SELF ',' variables ')' '{' statements '}'  '''
        t[0] = node('[FUNCTION]')
        t[0].add(node(t[2]))
        t[0].add(node('[SELF]'))
        t[0].add(t[6])
        t[0].add(t[9])


def p_run_function(t):
    '''run_function : VARIABLE '(' expressions ')'
                    | VARIABLE '.' VARIABLE '(' expressions ')' '''
    if len(t) == 7:
        ''' VARIABLE '.' VARIABLE '(' expressions ')' '''
        t[0] = node('[RUN_FUNCTION]')
        t[0].add(node(t[1]))
        t[0].add(node(t[3]))
        t[0].add(t[5])
    elif len(t) == 5:
        ''' VARIABLE '(' expressions ')' '''
        t[0] = node('[RUN_FUNCTION]')
        t[0].add(node(t[1]))
        t[0].add(t[3])


def p_variables(t):
    '''variables :
                 | VARIABLE
                 | self
                 | variables ',' VARIABLE
                 | variables ',' self '''
    if len(t) == 1:
        '''(empty)'''
        t[0] = node('[VARIABLES]')
        t[0].add(node('[NONE]'))
    elif len(t) == 2:
        if isinstance(t[1], node):
            t[0] = node('[VARIABLES]')
            t[0].add(t[1])
        else:
            t[0] = node('[VARIABLES]')
            t[0].add(node(t[1]))
    elif len(t) == 4:
        if isinstance(t[3], node):
            ''' variables ',' self '''
            t[0] = node('[VARIABLES]')
            t[0].add(t[1])
            t[0].add(t[3])
        else:
            ''' variables ',' VARIABLE '''
            t[0] = node('[VARIABLES]')
            t[0].add(t[1])
            t[0].add(node(t[3]))


def p_class(t):
    '''class : CLASS VARIABLE '{' statements '}' '''
    if len(t) == 6:
        t[0] = node('[CLASS]')
        t[0].add(node(t[2]))
        t[0].add(t[4])


def p_self(t):
    '''self : SELF '.' VARIABLE '''
    if len(t) == 4:
        t[0] = node('[SELF]')
        t[0].add(node(t[3]))
    elif len(t) == 2:
        t[0] = node('[SELF]')


def p_error(t):
    print("Syntax error at '%s'" % t.value)


yacc.yacc()
