#! /usr/bin/env python
# coding=utf-8
from __future__ import division

c_table = {}  # class table


class Tran:

    def __init__(self):
        self.v_table = {}  # variable table
        self.f_table = {}  # function table

    def update_v_table(self, name, value):
        self.v_table[name] = value

    def update_f_table(self, name, value):
        self.f_table[name] = value

    def trans(self, node):
        # Translation
        # Assignment
        if node.getdata() == '[ASSIGNMENT]':
            '''assignment : VARIABLE '=' NUMBER
                          | self '=' VARIABLE
                          | VARIABLE '=' VARIABLE
                          | VARIABLE '[' expression ']' '=' NUMBER
                          | VARIABLE '=' VARIABLE '[' expression ']'
                          | VARIABLE '=' VARIABLE '(' expressions ')' '''
            if len(node.getchildren()) == 3:
                if node.getchild(0).getdata() == '[SELF]':
                    '''self '=' VARIABLE'''
                    self.trans(node.getchild(0))
                    self.update_v_table(node.getchild(0).getvalue(), self.v_table[node.getchild(2).getdata()])
                elif node.getchild(2).getdata()[0].isdigit():
                    '''VARIABLE '=' NUMBER'''
                    self.update_v_table(node.getchild(0).getdata(), node.getchild(2).getvalue())
                else:
                    ''' VARIABLE '=' VARIABLE '''
                    self.update_v_table(node.getchild(0).getdata(), self.v_table[node.getchild(2).getdata()])
            elif len(node.getchildren()) == 4:
                if node.getchild(2).getdata() == '=':
                    ''' VARIABLE '[' expression ']' '=' NUMBER'''
                    self.trans(node.getchild(1))
                    index = int(node.getchild(1).getvalue())
                    self.v_table[node.getchild(0).getdata()][index] = node.getchild(3).getvalue()
                elif node.getchild(3).getdata() == '[EXPRESSION]':
                    ''' VARIABLE '=' VARIABLE '[' expression ']' '''
                    self.trans(node.getchild(3))
                    index = int(node.getchild(3).getvalue())
                    value = self.v_table[node.getchild(2).getdata()][index]
                    self.update_v_table(node.getchild(0).getdata(), value)
                elif node.getchild(3).getdata() == '[EXPRESSIONS]':
                    '''  VARIABLE '=' VARIABLE '(' expressions ')'  '''
                    variable, cname = node.getchild(0).getdata(), node.getchild(2).getdata()
                    self.trans(node.getchild(3))
                    vname1 = node.getchild(3).getvalue()
                    c = c_table[cname]
                    vname0, fnode = c.f_table['__init__']
                    for i in range(len(vname1)):
                        c.v_table[vname0[i]] = vname1[i]
                    c.trans(fnode)
                    self.update_v_table(variable, (cname, c))


        # Expression
        elif node.getdata() == '[EXPRESSIONS]':
            '''expressions :
                           | expression
                           | expressions ',' expression'''
            if len(node.getchildren()) == 1:
                if node.getchild(0).getdata() == '[NONE]':
                    '''(empty)'''
                    node.setvalue([])
                else:
                    ''' expression '''
                    self.trans(node.getchild(0))
                    node.setvalue([node.getchild(0).getvalue()])
            elif len(node.getchildren()) == 2:
                ''' expressions ',' expression '''
                self.trans(node.getchild(0))
                self.trans(node.getchild(1))
                value1 = node.getchild(0).getvalue()
                value2 = [node.getchild(1).getvalue()]
                value2.extend(value1)
                node.setvalue(value2)

        # Self
        elif node.getdata() == '[SELF]':
            '''self : SELF '.' VARIABLE'''
            if len(node.getchildren()) == 1:
                node.setvalue('self.' + node.getchild(0).getdata())

        # Operation
        elif node.getdata() == '[OPERATION]':
            '''operation : VARIABLE '=' expression
                         | self '=' expression
                         | VARIABLE '+' '=' expression
                         | VARIABLE '-' '=' expression
                         | VARIABLE '[' expression ']' '=' expression '''
            if len(node.getchildren()) == 3:
                if node.getchild(0).getdata() == '[SELF]':
                    ''' self '=' expression '''
                    self.trans(node.getchild(0))
                    self.trans(node.getchild(2))
                    self.update_v_table(node.getchild(0).getvalue(), node.getchild(2).getvalue())
                elif node.getchild(1).getdata()[0] == '=':
                    ''' VARIABLE '=' expression '''
                    self.trans(node.getchild(2))
                    self.update_v_table(node.getchild(0).getdata(), node.getchild(2).getvalue())
                elif node.getchild(1).getdata()[1] == '=':
                    ''' VARIABLE '+' '=' expression '''
                    self.trans(node.getchild(2))
                    arg1 = self.v_table[node.getchild(0).getdata()]
                    arg2 = node.getchild(2).getvalue()
                    op = node.getchild(1).getdata()[0]
                    if op == '+':
                        value = arg1 + arg2
                    elif op == '-':
                        value = arg1 - arg2
                    self.update_v_table(node.getchild(0).getdata(), value)
            elif len(node.getchildren()) == 4:
                ''' VARIABLE '[' expression ']' '=' expression '''
                arg = self.v_table[node.getchild(0).getdata()]
                self.trans(node.getchild(1))
                index = int(node.getchild(1).getvalue())
                self.trans(node.getchild(3))
                value = node.getchild(3).getvalue()
                arg[index] = value

        # Expr
        elif node.getdata() == '[EXPRESSION]':
            '''expr : term
                    | expression '+' term
                    | expression '-' term '''
            if len(node.getchildren()) == 1:
                ''' term '''
                self.trans(node.getchild(0))
                node.setvalue(node.getchild(0).getvalue())
            elif len(node.getchildren()) == 3:
                '''expression '+'/'-' term'''
                self.trans(node.getchild(0))
                self.trans(node.getchild(2))
                arg0, arg1 = node.getchild(0).getvalue(), node.getchild(2).getvalue()
                op = node.getchild(1).getdata()
                if op == '+':
                    value = arg0 + arg1
                elif op == '-':
                    value = arg0 - arg1
                node.setvalue(value)


        # Term
        elif node.getdata() == '[TERM]':
            '''term : factor
                    | term '*' factor
                    | term '/' factor'''
            if len(node.getchildren()) == 1:
                '''factor'''
                self.trans(node.getchild(0))
                node.setvalue(node.getchild(0).getvalue())
            elif len(node.getchildren()) == 3:
                '''term '*'/'/' factor'''
                self.trans(node.getchild(0))
                self.trans(node.getchild(2))
                arg0, arg1 = node.getchild(0).getvalue(), node.getchild(2).getvalue()
                op = node.getchild(1).getdata()
                if op == '*':
                    value = arg0 + arg1
                elif op == '/':
                    value = arg0 - arg1
                node.setvalue(value)
        # Factor
        elif node.getdata() == '[FACTOR]':
            '''factor : STR
                      | self
                      | NUMBER
                      | VARIABLE
                      | '(' expression ')'
                      | VARIABLE '[' expression ']' '''
            if len(node.getchildren()) == 1:
                if ord('0') <= ord(node.getchild(0).getdata()[0]) <= ord('9'):
                    '''NUMBER'''
                    node.setvalue(node.getchild(0).getvalue())
                elif node.getchild(0).getdata()[0] == "'":
                    '''STR'''
                    node.setvalue(node.getchild(0).getdata()[1:-1])
                elif node.getchild(0).getdata() == '[SELF]':
                    '''self'''
                    self.trans(node.getchild(0))
                    node.setvalue(self.v_table[node.getchild(0).getvalue()])
                elif node.getchild(0).getdata() == '[EXPRESSION]':
                    ''''(' expr ')' '''
                    self.trans(node.getchild(0))
                    node.setvalue(node.getchild(0).getvalue())
                else:
                    ''' VARIABLE '''
                    node.setvalue(self.v_table[node.getchild(0).getdata()])

            elif len(node.getchildren()) == 2:
                '''  VARIABLE '[' expression ']'  '''
                self.trans(node.getchild(1))
                node.setvalue(self.v_table[node.getchild(0).getdata()][int(node.getchild(1).getvalue())])



        # Function
        elif node.getdata() == '[FUNCTION]':
            '''function : DEF VARIABLE '(' variables ')' '{' statements '}'
                        | DEF VARIABLE '(' SELF ')' '{' statements '}'
                        | DEF VARIABLE '(' SELF ',' variables ')' '{' statements '}' '''
            if node.getchild(1).getdata() == '[VARIABLES]':
                ''' DEF VARIABLE '(' variables ')' '{' statements '}' '''
                self.trans(node.getchild(1))
                fname, vname = node.getchild(0).getdata(), node.getchild(1).getvalue()
                self.f_table[fname] = (vname, node.getchild(2))
            elif node.getchild(1).getdata() == '[SELF]':
                if len(node.getchildren()) == 3:
                    ''' DEF VARIABLE '(' SELF ')' '{' statements '}' '''
                    fname, vname = node.getchild(0).getdata(), []
                    self.f_table[fname] = (vname, node.getchild(2))
                elif len(node.getchildren()) == 4:
                    '''  DEF VARIABLE '(' SELF ',' variables ')' '{' statements '}' '''
                    self.trans(node.getchild(2))
                    fname, vname = node.getchild(0).getdata(), node.getchild(2).getvalue()
                    self.f_table[fname] = (vname, node.getchild(3))

        # Run_function
        elif node.getdata() == '[RUN_FUNCTION]':
            '''run_function : VARIABLE '(' expressions ')'
                            | VARIABLE '.' VARIABLE '(' expressions ')' '''
            if len(node.getchildren()) == 2:
                ''' VARIABLE '(' expressions ')' '''
                self.trans(node.getchild(1))
                fname, vname1 = node.getchild(0).getdata(), node.getchild(1).getvalue()
                vname0, fnode = self.f_table[fname]
                t = Tran()
                for i in range(len(vname1)):
                    t.v_table[vname0[i]] = vname1[i]
                value = t.trans(fnode)
                if isinstance(value, list):
                    node.setvalue(value[1])

            elif len(node.getchildren()) == 3:
                ''' VARIABLE '.' VARIABLE '(' expressions ')' '''
                self.trans(node.getchild(2))
                variable, fname, vname1 = node.getchild(0).getdata(), node.getchild(1).getdata(), node.getchild(
                    2).getvalue()
                c = self.v_table[variable][1]
                vname0, fnode = c.f_table[fname]  # function_name : (variable_names, function)
                for i in range(len(vname1)):
                    c.v_table[vname0[i]] = vname1[i]
                value = c.trans(fnode)
                if isinstance(value, list):
                    node.setvalue(value[1])

        # Variables
        elif node.getdata() == '[VARIABLES]':
            '''variables :
                         | VARIABLE
                         | variables ',' VARIABLE
                         | self
                         | variables ',' self'''
            if len(node.getchildren()) == 1:
                if node.getchild(0).getdata() == '[NONE]':
                    '''(empty)'''
                    node.setvalue([])
                elif node.getchild(0).getdata() == '[SELF]':
                    ''' self '''
                    self.trans(node.getchild(0))
                    node.setvalue([node.getchild(0).getvalue()])
                else:
                    ''' VARIABLE '''
                    node.setvalue([node.getchild(0).getdata()])
            elif len(node.getchildren()) == 2:
                if node.getchild(1).getdata() == '[SELF]':
                    ''' variables ',' self '''
                    self.trans(node.getchild(0))
                    self.trans(node.getchild(1))
                    value1 = node.getchild(0).getvalue()
                    value2 = [node.getchild(1).getvalue()]
                    value2.extend(value1)
                    node.setvalue(value2)
                else:
                    ''' variables ',' VARIABLE '''
                    self.trans(node.getchild(0))
                    value1 = node.getchild(0).getvalue()
                    value2 = [node.getchild(1).getdata()]
                    value2.extend(value1)
                    node.setvalue(value2)




        # Class
        elif node.getdata() == '[CLASS]':
            '''class : CLASS VARIABLE '{' statements '}' '''
            if len(node.getchildren()) == 2:
                '''  CLASS VARIABLE '{' statements '}' '''
                cname = node.getchild(0).getdata()
                t = Tran()
                t.trans(node.getchild(1))
                c_table[cname] = t
        # Print
        elif node.getdata() == '[PRINT]':
            '''print : PRINT '(' variables ')' '''
            self.trans(node.getchild(0))
            arg = node.getchild(0).getvalue()
            value = ''
            for i in range(len(arg)):
                value += str(self.v_table[arg[-1 - i]])
                value += ' '
            print(value)
        else:
            for c in node.getchildren():
                self.trans(c)

        return node.getvalue()
