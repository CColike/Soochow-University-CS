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
        '''statements : statements statement '''
        t[0] = node('[STATEMENTS]')
        t[0].add(t[1])
        t[0].add(t[2])
    elif len(t) == 2:
        '''statements : statement '''
        t[0] = node('[STATEMENTS]')
        t[0].add(t[1])


def p_statement(t):
    ''' statement :
                  | assignment
                  | operation
                  | print
                  | if
                  | while
                  | function
                  | run_function
                  | return '''
    if len(t) == 1:
        t[0] = node('[STATEMENT]')
        t[0].add(node('[NONE]'))
    elif len(t) == 2:
        t[0] = node('[STATEMENT]')
        t[0].add(t[1])


def p_assignment(t):
    '''assignment : VARIABLE '=' NUMBER
                  | VARIABLE '=' num_list
                  | VARIABLE '=' VARIABLE
                  | VARIABLE '[' expression ']' '=' NUMBER
                  | VARIABLE '=' VARIABLE '[' expression ']' '''
    if len(t) == 4:
        if not isinstance(t[3], str):
            '''assignment : VARIABLE '=' num_list '''
            t[0] = node('[ASSIGNMENT]')
            t[0].add(node(t[1]))
            t[0].add(node(t[2]))
            t[0].add(t[3])
        else:
            if t[3][0].isdigit():
                '''assignment : VARIABLE '[' expression ']' '=' NUMBER '''
                t[0] = node('[ASSIGNMENT]')
                t[0].add(node(t[1]))
                t[0].add(node(t[2]))
                t[0].add(num_node(t[3]))
            else:
                '''assignment : VARIABLE '=' num_list '''
                t[0] = node('[ASSIGNMENT]')
                t[0].add(node(t[1]))
                t[0].add(node(t[2]))
                t[0].add(node(t[3]))
    elif len(t) == 7:
        if t[2] == '=':
            '''assignment :  VARIABLE '=' VARIABLE '[' expression ']'  '''
            t[0] = node('[ASSIGNMENT]')
            t[0].add(node(t[1]))
            t[0].add(node(t[2]))
            t[0].add(node(t[3]))
            t[0].add(t[5])
        else:
            '''assignment :  VARIABLE '[' expression ']' '=' NUMBER '''
            t[0] = node('[ASSIGNMENT]')
            t[0].add(node(t[1]))
            t[0].add(t[3])
            t[0].add(node(t[5]))
            t[0].add(num_node(t[6]))


def p_operation(t):
    '''operation : VARIABLE '=' expression
                 | VARIABLE '+' '=' expression
                 | VARIABLE '-' '=' expression
                 | VARIABLE '[' expression ']' '=' expression'''
    t[0] = node('[OPERATION]')
    if len(t) == 4:
        '''operation : VARIABLE '=' expression'''
        t[0].add(node(t[1]))
        t[0].add(node(t[2]))
        t[0].add(t[3])
    elif len(t) == 5:
        '''operation : VARIABLE '+' '=' expression
                     | VARIABLE '-' '=' expression '''
        t[0].add(node(t[1]))
        t[0].add(node(t[2] + t[3]))
        t[0].add(t[4])
    elif len(t) == 7:
        '''operation : VARIABLE '[' expression ']' '=' expression'''
        t[0].add(node(t[1]))
        t[0].add(t[3])
        t[0].add(node(t[5]))
        t[0].add(t[6])


def p_expressions(t):
    '''expressions : expression
                   | expressions ',' expression'''
    if len(t) == 2:
        t[0] = node('[EXPRESSIONS]')
        t[0].add(t[1])
    elif len(t) == 4:
        t[0] = node('[EXPRESSIONS]')
        t[0].add(t[1])
        t[0].add(t[3])


def p_expression(t):
    '''expression : term
                  | expression '+' term
                  | expression '-' term
                  | LEN '(' factor ')' '''
    if len(t) == 2:
        ''' expression : term '''
        t[0] = node('[EXPRESSION]')
        t[0].add(t[1])
    elif len(t) == 4:
        ''' expression : expression '+' term
                       | expression '-' term '''
        t[0] = node('[EXPRESSION]')
        t[0].add(t[1])
        t[0].add(node(t[2]))
        t[0].add(t[3])
    elif len(t) == 5:
        ''' expression : LEN '(' factor ')' '''
        t[0] = node('[EXPRESSION]')
        t[0].add(node('[LEN]'))
        t[0].add(t[3])


def p_term(t):
    '''term : factor
            | term '*' factor
            | term '/' factor '''
    if len(t) == 2:
        '''term : factor '''
        t[0] = node('[TERM]')
        t[0].add(t[1])
    elif len(t) == 4:
        '''term : term '*' factor
                | term '/' factor '''
        t[0] = node('[TERM]')
        t[0].add(t[1])
        t[0].add(node(t[2]))
        t[0].add(t[3])


def p_factor(t):
    '''factor : NUMBER
              | VARIABLE
              | '(' expression ')'
              | VARIABLE '[' expression ']' '''
    if len(t) == 2:
        if t[1][0].isdigit():
            '''factor : NUMBER '''
            t[0] = node('[FACTOR]')
            t[0].add(num_node(t[1]))
        else:
            '''factor : VARIABLE '''
            t[0] = node('[FACTOR]')
            t[0].add(node(t[1]))
    elif len(t) == 4:
        '''factor : '(' expression ')' '''
        t[0] = node('[FACTOR]')
        t[0].add(t[2])
    elif len(t) == 5:
        '''factor : VARIABLE '[' expression ']' '''
        t[0] = node('[FACTOR]')
        t[0].add(node(t[1]))
        t[0].add(t[3])


def p_variables(t):
    '''variables :
                 | VARIABLE
                 | variables ',' VARIABLE'''
    if len(t) == 1:
        t[0] = node('[VARIABLES]')
        t[0].add(node('[NONE]'))
    elif len(t) == 2:
        t[0] = node('[VARIABLES]')
        t[0].add(node(t[1]))
    elif len(t) == 4:
        t[0] = node('[VARIABLES]')
        t[0].add(t[1])
        t[0].add(node(t[3]))


def p_print(t):
    '''print : PRINT '(' VARIABLE ')' '''
    if len(t) == 5:
        t[0] = node('[PRINT]')
        t[0].add(node(t[3]))


def p_if(t):
    '''if : IF '(' condition ')' '{' statements '}' '''
    if len(t) == 8:
        t[0] = node('[IF]')
        t[0].add(t[3])
        t[0].add(t[6])


def p_function(t):
    '''function : DEF VARIABLE '(' variables ')' '{' statements '}' '''
    if len(t) == 9:
        t[0] = node('[FUNCTION]')
        t[0].add(node(t[2]))
        t[0].add(t[4])
        t[0].add(t[7])


def p_run_function(t):
    '''run_function : VARIABLE '(' expressions ')' '''
    if len(t) == 5:
        t[0] = node('[RUN_FUNCTION]')
        t[0].add(node(t[1]))
        t[0].add(t[3])


def p_return(t):
    '''return : RETURN variables'''
    if len(t) == 3:
        t[0] = node('[RETURN]')
        t[0].add(t[2])


def p_condition(t):
    '''condition : factor '>' factor
                 | factor '<' factor
                 | factor '<' '=' factor
                 | factor '>' '=' factor'''
    if len(t) == 4:
        '''condition : factor '>' factor
                     | factor '<' factor '''
        t[0] = node('[CONDITION]')
        t[0].add(t[1])
        t[0].add(node(t[2]))
        t[0].add(t[3])
    elif len(t) == 5:
        '''condition : factor '>' '=' factor
                     | factor '<' '=' factor '''
        t[0] = node('[CONDITION]')
        t[0].add(t[1])
        t[0].add(node(t[2] + t[3]))
        t[0].add(t[4])


def p_conditions(t):
    '''conditions : condition
                  | condition AND condition '''
    if len(t) == 2:
        '''conditions : condition '''
        t[0] = node('[CONDITIONS]')
        t[0].add(t[1])
    elif len(t) == 4:
        '''conditions : condition AND condition  '''
        t[0] = node('[CONDITIONS]')
        t[0].add(t[1])
        t[0].add(t[3])


def p_while(t):
    '''while : WHILE '(' conditions ')' '{' statements '}' '''
    if len(t) == 8:
        t[0] = node('[WHILE]')
        t[0].add(t[3])
        t[0].add(t[6])


def p_num_list(t):
    '''num_list : '[' numbers ']' '''
    if len(t) == 4:
        t[0] = node('[NUM_LIST]')
        t[0].add(t[2])


def p_numbers(t):
    '''numbers : NUMBER
               | numbers ',' NUMBER'''
    t[0] = node('[NUMBERS]')
    if len(t) == 2:
        t[0].add(num_node(t[1]))
    elif len(t) == 4:
        t[0].add(t[1])
        t[0].add(num_node(t[3]))


def p_error(t):
    print("Syntax error at '%s'" % t.value)


yacc.yacc()
