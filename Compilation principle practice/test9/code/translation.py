#! /usr/bin/env python
# coding=utf-8
from __future__ import division

f_table = {}  # function table


class Tran:

    def __init__(self):
        self.v_table = {}  # variable table

    def update_v_table(self, name, value):
        self.v_table[name] = value

    def trans(self, node):

        # Translation

        # Assignment
        if node.getdata() == '[ASSIGNMENT]':
            '''assignment : VARIABLE '=' NUMBER
                          | VARIABLE '=' num_list
                          | VARIABLE '=' VARIABLE
                          | VARIABLE '[' expression ']' '=' NUMBER
                          | VARIABLE '=' VARIABLE '[' expression ']' '''
            length = len(node.getchildren())
            if length == 3:
                if node.getchild(2).getdata() == '[NUM_LIST]':
                    '''VARIABLE '=' num_list'''
                    self.trans(node.getchild(2))
                    value = node.getchild(2).getvalue()
                    self.update_v_table(node.getchild(0).getdata(), value)
                elif node.getchild(2).getdata()[0].isdigit():
                    '''VARIABLE '=' NUMBER'''
                    value = node.getchild(2).getvalue()
                    self.update_v_table(node.getchild(0).getdata(), value)
                else:
                    '''VARIABLE '=' VARIABLE'''
                    value = self.v_table[node.getchild(2).getdata()]
                    self.update_v_table(node.getchild(0).getdata(), value)
            elif length == 4:
                if node.getchild(1).getdata() == '=':
                    '''VARIABLE '=' VARIABLE '[' expression ']' '''
                    lst = self.v_table[node.getchild(2).getdata()]
                    self.trans(node.getchild(3))
                    idx = int(node.getchild(3).getvalue())
                    value = lst[idx]
                    self.update_v_table(node.getchild(0).getdata(), value)
                else:
                    '''VARIABLE '[' expression ']' '=' NUMBER'''
                    lst = self.v_table[node.getchild(0).getdata()]
                    self.trans(node.getchild(1))
                    idx = int(node.getchild(1).getvalue())
                    value = node.getchild(3).getvalue()
                    lst[idx] = value

        # Operation
        elif node.getdata() == '[OPERATION]':
            '''operation : VARIABLE '=' expression
                         | VARIABLE '+' '=' expression
                         | VARIABLE '-' '=' expression
                         | VARIABLE '[' expression ']' '=' expression'''
            if len(node.getchildren()) == 3:
                if node.getchild(1).getdata()[0] == '=':
                    '''VARIABLE '=' expression'''
                    self.trans(node.getchild(2))
                    value = node.getchild(2).getvalue()
                    node.getchild(0).setvalue(value)
                    self.update_v_table(node.getchild(0).getdata(), value)
                else:
                    '''VARIABLE '+' '=' expression'''
                    arg1 = self.v_table[node.getchild(0).getdata()]
                    self.trans(node.getchild(2))
                    arg2 = node.getchild(2).getvalue()
                    op = node.getchild(1).getdata()[0]
                    if op == '+':
                        value = arg1 + arg2
                    else:
                        value = arg1 - arg2
                    node.getchild(0).setvalue(value)
                    self.update_v_table(node.getchild(0).getdata(), value)
            elif len(node.getchildren()) == 4:
                '''VARIABLE '[' expression ']' '=' expression'''
                arg = self.v_table[node.getchild(0).getdata()]
                self.trans(node.getchild(1))
                index = int(node.getchild(1).getvalue())
                self.trans(node.getchild(3))
                value = node.getchild(3).getvalue()
                arg[index] = value

        # Expression
        elif node.getdata() == '[EXPRESSION]':
            '''expression : term
                          | expression '+' term
                          | expression '-' term
                          | LEN '(' factor ')' '''
            if len(node.getchildren()) == 1:
                ''' term '''
                self.trans(node.getchild(0))
                value = node.getchild(0).getvalue()
                node.setvalue(value)
            elif len(node.getchildren()) == 2:
                ''' LEN '(' factor ')' '''
                self.trans(node.getchild(1))
                value = len(node.getchild(1).getvalue())
                node.setvalue(value)
            elif len(node.getchildren()) == 3:
                ''' expression '+'/'-' term'''
                self.trans(node.getchild(0))
                arg0 = node.getchild(0).getvalue()
                self.trans(node.getchild(2))
                arg1 = node.getchild(2).getvalue()
                op = node.getchild(1).getdata()
                if op == '+':
                    value = arg0 + arg1
                elif op == '-':
                    value = arg0 - arg1
                node.setvalue(value)

        # Num_list
        elif node.getdata() == '[NUM_LIST]':
            '''num_list : '[' numbers ']' '''
            if len(node.getchildren()) == 1:
                self.trans(node.getchild(0))
                value = [float(x) for x in node.getchild(0).getvalue().split()]
                node.setvalue(value)

        # Numbers
        elif node.getdata() == '[NUMBERS]':
            '''numbers : NUMBER
                       | numbers ',' NUMBER'''
            if len(node.getchildren()) == 1:
                value = str(node.getchild(0).getvalue())
                node.setvalue(value)
            elif len(node.getchildren()) == 2:
                self.trans(node.getchild(0))
                value0 = node.getchild(0).getvalue()
                value1 = str(node.getchild(1).getvalue())
                value = value0 + ' ' + value1
                node.setvalue(value)

        # Term
        elif node.getdata() == '[TERM]':
            '''term : factor
                    | term '*' factor
                    | term '/' factor '''
            if len(node.getchildren()) == 1:
                '''factor'''
                self.trans(node.getchild(0))
                value = node.getchild(0).getvalue()
                node.setvalue(value)
            elif len(node.getchildren()) == 3:
                '''term '*'/'/' factor'''
                self.trans(node.getchild(0))
                self.trans(node.getchild(2))
                arg0 = node.getchild(0).getvalue()
                arg1 = node.getchild(2).getvalue()
                op = node.getchild(1).getdata()
                if op == '*':
                    value = arg0 + arg1
                elif op == '/':
                    value = arg0 - arg1
                node.setvalue(value)

        # Factor
        elif node.getdata() == '[FACTOR]':
            '''factor : NUMBER
                      | VARIABLE
                      |'(' expression ')' 
                      | VARIABLE '[' expression ']' '''
            length = len(node.getchildren())
            if length == 1:
                if node.getchild(0).getdata()[0].isdigit():
                    ''' NUMBER '''
                    value = node.getchild(0).getvalue()
                    node.setvalue(value)
                elif node.getchild(0).getdata() == '[EXPRESSION]':
                    ''' '(' expression ')' '''
                    self.trans(node.getchild(0))
                    value = node.getchild(0).getvalue()
                    node.setvalue(value)
                else:
                    '''VARIABLE'''
                    value = self.v_table[node.getchild(0).getdata()]
                    node.setvalue(value)
            elif length == 2:
                ''' VARIABLE '[' expression ']' '''
                arg = self.v_table[node.getchild(0).getdata()]
                self.trans(node.getchild(1))
                index = int(node.getchild(1).getvalue())
                value = arg[index]
                node.setvalue(value)

        # Print
        elif node.getdata() == '[PRINT]':
            '''print : PRINT '(' VARIABLE ')' '''
            arg0 = self.v_table[node.getchild(0).getdata()]
            print(arg0)

        # If
        elif node.getdata() == '[IF]':
            '''if : IF '(' condition ')' '{' statements '}' '''
            children = node.getchildren()
            self.trans(children[0])
            condition = children[0].getvalue()
            if condition:
                for c in children[1:]:
                    value = self.trans(c)
                    if isinstance(value, list) and value[0] == '[RETURN]':
                        return value

        # While
        elif node.getdata() == '[WHILE]':
            '''while : WHILE '(' conditions ')' '{' statements '}' '''
            children = node.getchildren()
            while self.trans(children[0]):
                for c in children[1:]:
                    self.trans(c)

        # Function
        elif node.getdata() == '[FUNCTION]':
            '''function : DEF VARIABLE '(' variables ')' '{' statements '}' '''
            fname = node.getchild(0).getdata()
            self.trans(node.getchild(1))
            vname = node.getchild(1).getvalue()
            f_table[fname] = (vname, node.getchild(2))  # function_name : (variable_names, function)

        # Run_function
        elif node.getdata() == '[RUN_FUNCTION]':
            '''run_function : VARIABLE '(' expressions ')' '''
            fname = node.getchild(0).getdata()
            self.trans(node.getchild(1))
            vname1 = node.getchild(1).getvalue()
            vname0, fnode = f_table[fname]  # function_name : (variable_names, function)
            t = Tran()
            for i in range(len(vname1)):
                t.v_table[vname0[i]] = vname1[i]
            value = t.trans(fnode)
            if isinstance(value, list):
                node.setvalue(value[1])

        # Variables
        elif node.getdata() == '[VARIABLES]':
            '''variables :
                         | VARIABLE
                         | variables ',' VARIABLE'''
            if len(node.getchildren()) == 1:
                '''(empty)'''
                if node.getchild(0).getdata() == '[NONE]':
                    value = []
                    node.setvalue(value)
                else:
                    '''VARIABLE'''
                    value = [node.getchild(0).getdata()]
                    node.setvalue(value)
            elif len(node.getchildren()) == 2:
                '''variables ',' VARIABLE'''
                self.trans(node.getchild(0))
                value = [node.getchild(1).getdata()]
                node.setvalue(value)
                value.extend(node.getchild(0).getvalue())

        # Conditions
        elif node.getdata() == '[CONDITIONS]':
            '''conditions : condition
                          | condition AND condition'''
            if len(node.getchildren()) == 1:
                ''' condition '''
                self.trans(node.getchild(0))
                value = node.getchild(0).getvalue()
                node.setvalue(value)
            elif len(node.getchildren()) == 2:
                '''condition AND condition '''
                self.trans(node.getchild(0))
                arg0 = node.getchild(0).getvalue()
                self.trans(node.getchild(1))
                arg1 = node.getchild(1).getvalue()
                value = arg0 and arg1
                node.setvalue(value)


        # Condition
        elif node.getdata() == '[CONDITION]':
            '''condition : factor '>' factor
                         | factor '<' factor
                         | factor '<' '=' factor
                         | factor '>' '=' factor'''
            self.trans(node.getchild(0))
            self.trans(node.getchild(2))
            arg0 = node.getchild(0).getvalue()
            op = node.getchild(1).getdata()
            arg1 = node.getchild(2).getvalue()
            if op == '>':
                node.setvalue(arg0 > arg1)
            elif op == '<':
                node.setvalue(arg0 < arg1)
            elif op == '<=':
                node.setvalue(arg0 <= arg1)
            elif op == '>=':
                node.setvalue(arg0 >= arg1)

        # Expressions
        elif node.getdata() == '[EXPRESSIONS]':
            '''expressions : expression
                           | expressions ',' expression'''
            if len(node.getchildren()) == 1:
                '''expression '''
                self.trans(node.getchild(0))
                value = [node.getchild(0).getvalue()]
                node.setvalue(value)
            elif len(node.getchildren()) == 2:
                ''' expressions ',' expression '''
                self.trans(node.getchild(0))
                self.trans(node.getchild(1))
                value = [node.getchild(1).getvalue()]
                value.extend(node.getchild(0).getvalue())
                node.setvalue(value)

        # Return
        elif node.getdata() == '[RETURN]':
            '''return : RETURN variables'''
            return ['[RETURN]', node.getchild(0).getvalue()]

        else:
            for c in node.getchildren():
                value = self.trans(c)
                if isinstance(value, list) and value[0] == '[RETURN]':
                    return value

        return node.getvalue()
