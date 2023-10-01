import ply.lex as lex

reversed = {'if': 'IF', 'int': 'INT', 'while': 'WHILE'}
tokens = [
    'SEMICOLON', 'LB_BR', 'RB_BR','LL_BR', 'RL_BR', 'EQUAL',
    'LT','GT', 'MINUS', 'PLUS', 'LSHIFT', 'RSHIFT',
    'ID','INT', 'STRING',
    'WHILE','IF'
]

t_LL_BR = r'\('
t_RL_BR = r'\)'
t_EQUAL = r'='
t_LT = r'<'
t_GT=r'>'
t_MINUS = r'-'
t_PLUS = r'\+'
t_LSHIFT = r'<<'
t_RSHIFT = r'>>'
t_SEMICOLON = r';'
t_LB_BR = r'\{'
t_RB_BR = r'}'

def t_ID(t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    t.type = reversed.get(t.value, 'ID')    # Check for reserved words
    return t

def t_INT(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_STRING(t):
    r'\"([^\\\n]|(\\.))*?\"'
    t.value = str(t.value[1:-1])
    return t

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

t_ignore = ' \t'

lexer = lex.lex()
with open("prog.txt","r",encoding= "utf-8") as f:
    data=f.read()
lexer.input(data)
while True:
    tok = lexer.token()
    if not tok: break
    print(tok)