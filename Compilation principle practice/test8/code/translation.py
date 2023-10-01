v_table = {}  # variable table


def update_v_table(name, value):
    v_table[name] = value


def trans(node):
    # Translation
    # Assignment
    if node.getdata() == '[ASSIGNMENT]':
        '''assignment : VARIABLE '=' NUMBER
                      | VARIABLE '[' expr ']' '=' NUMBER
                      | VARIABLE '=' VARIABLE
                      | VARIABLE '=' VARIABLE '[' expr ']'
                      | VARIABLE '=' num_list'''
        if len(node.getchildren()) == 3:
            if ord('0') <= ord(node.getchild(2).getdata()[0]) <= ord('9'):  # NUMBER
                value = node.getchild(2).getvalue()
                # update v_table
                update_v_table(node.getchild(0).getdata(), value)
            elif node.getchild(2).getdata() == '[NUM_LIST]':  # num_list
                trans(node.getchild(2))
                value = node.getchild(2).getvalue()
                # update v_table
                update_v_table(node.getchild(0).getdata(), value)
            else:  # VARIABLE
                value = v_table[node.getchild(2).getdata()]
                # update v_table
                update_v_table(node.getchild(0).getdata(), value)

        elif len(node.getchildren()) == 4:
            if node.getchild(2).getdata() == '=':  # NUMBER
                arg = v_table[node.getchild(0).getdata()]
                trans(node.getchild(1))
                index = int(node.getchild(1).getvalue())
                value = node.getchild(3).getvalue()
                # update VARIABLE
                arg[index] = value

            elif node.getchild(1).getdata() == '=':  # VARIABLE '[' expr ']'
                arg1 = v_table[node.getchild(2).getdata()]
                trans(node.getchild(3))
                index = int(node.getchild(3).getvalue())
                value = arg1[index]
                # update v_table
                update_v_table(node.getchild(0).getdata(), value)

    # Num_list
    elif node.getdata() == '[NUM_LIST]':
        '''num_list : '[' numbers ']' '''
        if len(node.getchildren()) == 1:
            trans(node.getchild(0))
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
            trans(node.getchild(0))

            value0 = node.getchild(0).getvalue()
            value1 = str(node.getchild(1).getvalue())
            value = value0 + ' ' + value1
            node.setvalue(value)

    # Operation
    elif node.getdata() == '[OPERATION]':
        '''operation : VARIABLE '=' expr
                     | VARIABLE '[' expr ']' '=' expr'''
        if len(node.getchildren()) == 3:
            trans(node.getchild(2))
            value = node.getchild(2).getvalue()
            node.getchild(0).setvalue(value)
            # update v_table
            update_v_table(node.getchild(0).getdata(), value)
        elif len(node.getchildren()) == 4:
            arg = v_table[node.getchild(0).getdata()]
            trans(node.getchild(1))
            index = int(node.getchild(1).getvalue())
            trans(node.getchild(3))
            value = node.getchild(3).getvalue()
            # update VARIABLE
            arg[index] = value

    # Expr
    elif node.getdata() == '[EXPRESSION]':
        '''expr : expr '+' term
                | expr '-' term
                | expr DIV factor
                | term
                | LEN '(' factor ')' '''
        if len(node.getchildren()) == 3:
            trans(node.getchild(0))
            arg0 = node.getchild(0).getvalue()
            trans(node.getchild(2))
            arg1 = node.getchild(2).getvalue()
            op = node.getchild(1).getdata()
            if op == '+':
                value = arg0 + arg1
            elif op == '-':
                value = arg0 - arg1
            elif op == '//':
                value = arg0 // arg1
            node.setvalue(value)

        elif len(node.getchildren()) == 1:  # term
            trans(node.getchild(0))
            value = node.getchild(0).getvalue()
            node.setvalue(value)

        elif len(node.getchildren()) == 2:
            trans(node.getchild(1))
            value = len(node.getchild(1).getvalue())
            node.setvalue(value)

    # Term
    elif node.getdata() == '[TERM]':
        '''term : term '*' factor
                | term '/' factor
                | factor'''
        if len(node.getchildren()) == 3:
            trans(node.getchild(0))
            arg0 = node.getchild(0).getvalue()
            trans(node.getchild(2))
            arg1 = node.getchild(2).getvalue()
            op = node.getchild(1).getdata()
            if op == '*':
                value = arg0 + arg1
            elif op == '/':
                value = arg0 - arg1
            node.setvalue(value)
        elif len(node.getchildren()) == 1:
            trans(node.getchild(0))
            value = node.getchild(0).getvalue()
            node.setvalue(value)

    # Factor
    elif node.getdata() == '[FACTOR]':
        '''factor : NUMBER
                  | VARIABLE
                  | VARIABLE '[' expr ']'
                  | '(' expr ')' '''
        if len(node.getchildren()) == 1:
            if ord('0') <= ord(node.getchild(0).getdata()[0]) <= ord('9'):  # NUMBER
                value = node.getchild(0).getvalue()
                node.setvalue(value)
            elif node.getchild(0).getdata() == '[EXPRESSION]':  # '(' expr ')'
                trans(node.getchild(0))
                value = node.getchild(0).getvalue()
                node.setvalue(value)
            else:  # VARIABLE
                value = v_table[node.getchild(0).getdata()]
                node.setvalue(value)

        elif len(node.getchildren()) == 2:
            arg = v_table[node.getchild(0).getdata()]
            trans(node.getchild(1))
            index = int(node.getchild(1).getvalue())
            value = arg[index]
            node.setvalue(value)

    # Print
    elif node.getdata() == '[PRINT]':
        '''print : PRINT '(' VARIABLE ')' '''
        arg0 = v_table[node.getchild(0).getdata()]
        print(arg0)

    # Condition
    elif node.getdata() == '[CONDITION]':
        '''condition : factor '>' factor
                     | factor '<' factor
                     | factor LE factor
                     | factor GE factor'''
        trans(node.getchild(0))
        arg0 = node.getchild(0).getvalue()
        trans(node.getchild(2))
        arg1 = node.getchild(2).getvalue()
        op = node.getchild(1).getdata()
        if op == '>':
            node.setvalue(arg0 > arg1)
        elif op == '<':
            node.setvalue(arg0 < arg1)
        elif op == '<=':
            node.setvalue(arg0 <= arg1)
        elif op == '>=':
            node.setvalue(arg0 >= arg1)

    # If_elif_else
    elif node.getdata() == '[IF_ELIF_ELSE]':
        '''if_elif_else : if
                        | if elif else'''
        if len(node.getchildren()) == 1:
            if trans(node.getchild(0)) == '[BREAK]':
                return '[BREAK]'
        elif len(node.getchildren()) == 3:
            trans(node.getchild(0).getchild(0))
            condition = node.getchild(0).getchild(0).getvalue()
            if condition:
                if trans(node.getchild(0)) == '[BREAK]':
                    return '[BREAK]'
            else:
                trans(node.getchild(1).getchild(0))
                condition = node.getchild(1).getchild(0).getvalue()
                if condition:
                    if trans(node.getchild(1)) == '[BREAK]':
                        return '[BREAK]'
                else:
                    if trans(node.getchild(2)) == '[BREAK]':
                        return '[BREAK]'

    # If
    elif node.getdata() == '[IF]':
        r'''if : IF '(' condition ')' '{' statements '}' '''
        children = node.getchildren()
        trans(children[0])
        condition = children[0].getvalue()
        if condition:
            for c in children[1:]:
                trans(c)

    # Elif
    elif node.getdata() == '[ELIF]':
        '''elif : ELIF '(' condition ')' '{' statements '}' '''
        children = node.getchildren()
        trans(children[0])
        condition = children[0].getvalue()
        if condition:
            for c in children[1:]:
                trans(c)

    # Else
    elif node.getdata() == '[ELSE]':
        if trans(node.getchild(0)) == '[BREAK]':
            return '[BREAK]'

    # While
    elif node.getdata() == '[WHILE]':
        r'''while : WHILE '(' condition ')' '{' statements '}' '''
        children = node.getchildren()
        break_flag = False
        while trans(children[0]):
            for c in children[1:]:
                if trans(c) == '[BREAK]':
                    break_flag = True
                    break
            if break_flag:
                break

    # For
    elif node.getdata() == '[FOR]':
        '''for : FOR '(' conditions ')' '{' statements '}' '''
        conditions = node.getchild(0)
        children = node.getchildren()
        break_flag = False
        trans(conditions.getchild(0))  # assignment
        while trans(conditions.getchild(1)):  # condition
            for c in children[1:]:
                if trans(c) == '[BREAK]':
                    break_flag = True
                    break
            if break_flag:
                break
            trans(conditions.getchild(2))  # increment

    # Increment
    elif node.getdata() == '[INCREMENT]':
        value = v_table[node.getchild(0).getdata()] + 1
        # update v_table
        update_v_table(node.getchild(0).getdata(), value)

    # Break
    elif node.getdata() == '[BREAK]':
        return '[BREAK]'

    else:
        for c in node.getchildren():
            # 原本仅为trans(c)
            if trans(c) == '[BREAK]':
                return '[BREAK]'

    return node.getvalue()
