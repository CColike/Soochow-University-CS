
# parsetab.py
# This file is automatically generated. Do not edit.
# pylint: disable=W,C,R
_tabversion = '3.10'

_lr_method = 'LALR'

_lr_signature = "CLASS DEF NUMBER PRINT SELF STR VARIABLEprogram : statementsstatements : statements statement\n                  | statement statement : assignment\n                  | operation\n                  | print\n                  | function\n                  | run_function\n                  | classoperation : VARIABLE '=' expression\n                 | self '=' expression\n                 | VARIABLE '+' '=' expression\n                 | VARIABLE '-' '=' expression\n                 | VARIABLE '[' expression ']' '=' expression assignment : VARIABLE '=' NUMBER\n                  | self '=' VARIABLE\n                  | VARIABLE '=' VARIABLE\n                  | VARIABLE '[' expression ']' '=' NUMBER\n                  | VARIABLE '=' VARIABLE '[' expression ']'\n                  | VARIABLE '=' VARIABLE '(' expressions ')' expressions :\n                   | expression\n                   | expressions ',' expressionexpression : term\n                  | expression '+' term\n                  | expression '-' term term : factor\n            | term '*' factor\n            | term '/' factor factor : STR\n              | self\n              | NUMBER\n              | VARIABLE\n              | '(' expression ')'\n              | VARIABLE '[' expression ']' print : PRINT '(' variables ')' function : DEF VARIABLE '(' variables ')' '{' statements '}'\n                | DEF VARIABLE '(' SELF ')' '{' statements '}'\n                | DEF VARIABLE '(' SELF ',' variables ')' '{' statements '}' run_function : VARIABLE '(' expressions ')'\n                    | VARIABLE '.' VARIABLE '(' expressions ')' variables :\n                 | VARIABLE\n                 | self\n                 | variables ',' VARIABLE\n                 | variables ',' self class : CLASS VARIABLE '{' statements '}' self : SELF '.' VARIABLE "
    
_lr_action_items = {'VARIABLE':([0,2,3,4,5,6,7,8,9,13,15,16,17,18,19,22,23,24,26,28,29,30,31,32,33,34,35,36,38,41,42,44,45,49,50,51,52,53,54,55,57,58,59,61,62,63,64,65,66,67,70,73,74,75,76,77,79,86,87,88,89,90,91,92,93,94,95,97,98,100,101,102,103,104,],[10,10,-3,-4,-5,-6,-7,-8,-9,25,27,-2,28,36,36,43,44,47,50,-17,-15,-10,36,-24,-27,-30,-31,-33,-32,36,36,-16,-11,47,-48,10,36,36,36,36,36,36,36,-40,36,-12,-13,36,-36,82,10,-25,-26,-34,-28,-29,36,47,-47,-19,-20,-35,-14,-18,-41,10,10,10,10,-37,-38,10,10,-39,]),'PRINT':([0,2,3,4,5,6,7,8,9,16,28,29,30,32,33,34,35,36,38,44,45,50,51,61,63,64,66,70,73,74,75,76,77,87,88,89,90,91,92,93,94,95,97,98,100,101,102,103,104,],[12,12,-3,-4,-5,-6,-7,-8,-9,-2,-17,-15,-10,-24,-27,-30,-31,-33,-32,-16,-11,-48,12,-40,-12,-13,-36,12,-25,-26,-34,-28,-29,-47,-19,-20,-35,-14,-18,-41,12,12,12,12,-37,-38,12,12,-39,]),'DEF':([0,2,3,4,5,6,7,8,9,16,28,29,30,32,33,34,35,36,38,44,45,50,51,61,63,64,66,70,73,74,75,76,77,87,88,89,90,91,92,93,94,95,97,98,100,101,102,103,104,],[13,13,-3,-4,-5,-6,-7,-8,-9,-2,-17,-15,-10,-24,-27,-30,-31,-33,-32,-16,-11,-48,13,-40,-12,-13,-36,13,-25,-26,-34,-28,-29,-47,-19,-20,-35,-14,-18,-41,13,13,13,13,-37,-38,13,13,-39,]),'CLASS':([0,2,3,4,5,6,7,8,9,16,28,29,30,32,33,34,35,36,38,44,45,50,51,61,63,64,66,70,73,74,75,76,77,87,88,89,90,91,92,93,94,95,97,98,100,101,102,103,104,],[15,15,-3,-4,-5,-6,-7,-8,-9,-2,-17,-15,-10,-24,-27,-30,-31,-33,-32,-16,-11,-48,15,-40,-12,-13,-36,15,-25,-26,-34,-28,-29,-47,-19,-20,-35,-14,-18,-41,15,15,15,15,-37,-38,15,15,-39,]),'SELF':([0,2,3,4,5,6,7,8,9,16,17,18,19,23,24,28,29,30,31,32,33,34,35,36,38,41,42,44,45,49,50,51,52,53,54,55,57,58,59,61,62,63,64,65,66,67,70,73,74,75,76,77,79,86,87,88,89,90,91,92,93,94,95,97,98,100,101,102,103,104,],[14,14,-3,-4,-5,-6,-7,-8,-9,-2,14,14,14,14,14,-17,-15,-10,14,-24,-27,-30,-31,-33,-32,14,14,-16,-11,69,-48,14,14,14,14,14,14,14,14,-40,14,-12,-13,14,-36,14,14,-25,-26,-34,-28,-29,14,14,-47,-19,-20,-35,-14,-18,-41,14,14,14,14,-37,-38,14,14,-39,]),'$end':([1,2,3,4,5,6,7,8,9,16,28,29,30,32,33,34,35,36,38,44,45,50,61,63,64,66,73,74,75,76,77,87,88,89,90,91,92,93,100,101,104,],[0,-1,-3,-4,-5,-6,-7,-8,-9,-2,-17,-15,-10,-24,-27,-30,-31,-33,-32,-16,-11,-48,-40,-12,-13,-36,-25,-26,-34,-28,-29,-47,-19,-20,-35,-14,-18,-41,-37,-38,-39,]),'}':([3,4,5,6,7,8,9,16,28,29,30,32,33,34,35,36,38,44,45,50,61,63,64,66,70,73,74,75,76,77,87,88,89,90,91,92,93,97,98,100,101,103,104,],[-3,-4,-5,-6,-7,-8,-9,-2,-17,-15,-10,-24,-27,-30,-31,-33,-32,-16,-11,-48,-40,-12,-13,-36,87,-25,-26,-34,-28,-29,-47,-19,-20,-35,-14,-18,-41,100,101,-37,-38,104,-39,]),'=':([10,11,20,21,50,60,],[17,23,41,42,-48,79,]),'[':([10,28,36,44,],[18,52,59,59,]),'+':([10,28,29,30,32,33,34,35,36,37,38,40,44,45,50,56,63,64,71,73,74,75,76,77,78,80,88,90,91,92,],[20,-33,-32,54,-24,-27,-30,-31,-33,54,-32,54,-33,54,-48,54,54,54,54,-25,-26,-34,-28,-29,54,54,-35,-35,54,-32,]),'-':([10,28,29,30,32,33,34,35,36,37,38,40,44,45,50,56,63,64,71,73,74,75,76,77,78,80,88,90,91,92,],[21,-33,-32,55,-24,-27,-30,-31,-33,55,-32,55,-33,55,-48,55,55,55,55,-25,-26,-34,-28,-29,55,55,-35,-35,55,-32,]),'(':([10,12,17,18,19,23,25,28,31,41,42,43,52,53,54,55,57,58,59,62,65,79,],[19,24,31,31,31,31,49,53,31,31,31,65,31,31,31,31,31,31,31,31,31,31,]),'.':([10,14,69,],[22,26,26,]),'NUMBER':([17,18,19,23,31,41,42,52,53,54,55,57,58,59,62,65,79,],[29,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,92,]),'STR':([17,18,19,23,31,41,42,52,53,54,55,57,58,59,62,65,79,],[34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,]),')':([19,24,32,33,34,35,36,38,39,40,46,47,48,49,50,53,56,65,68,69,72,73,74,75,76,77,80,81,82,83,86,90,96,],[-21,-42,-24,-27,-30,-31,-33,-32,61,-22,66,-43,-44,-42,-48,-21,75,-21,84,85,89,-25,-26,-34,-28,-29,-23,93,-45,-46,-42,-35,99,]),',':([19,24,32,33,34,35,36,38,39,40,46,47,48,49,50,53,65,68,69,72,73,74,75,76,77,80,81,82,83,86,90,96,],[-21,-42,-24,-27,-30,-31,-33,-32,62,-22,67,-43,-44,-42,-48,-21,-21,67,86,62,-25,-26,-34,-28,-29,-23,62,-45,-46,-42,-35,67,]),'{':([27,84,85,99,],[51,94,95,102,]),'*':([28,29,32,33,34,35,36,38,44,50,73,74,75,76,77,88,90,92,],[-33,-32,57,-27,-30,-31,-33,-32,-33,-48,57,57,-34,-28,-29,-35,-35,-32,]),'/':([28,29,32,33,34,35,36,38,44,50,73,74,75,76,77,88,90,92,],[-33,-32,58,-27,-30,-31,-33,-32,-33,-48,58,58,-34,-28,-29,-35,-35,-32,]),']':([32,33,34,35,36,37,38,50,71,73,74,75,76,77,78,90,],[-24,-27,-30,-31,-33,60,-32,-48,88,-25,-26,-34,-28,-29,90,-35,]),}

_lr_action = {}
for _k, _v in _lr_action_items.items():
   for _x,_y in zip(_v[0],_v[1]):
      if not _x in _lr_action:  _lr_action[_x] = {}
      _lr_action[_x][_k] = _y
del _lr_action_items

_lr_goto_items = {'program':([0,],[1,]),'statements':([0,51,94,95,102,],[2,70,97,98,103,]),'statement':([0,2,51,70,94,95,97,98,102,103,],[3,16,3,16,3,3,16,16,3,16,]),'assignment':([0,2,51,70,94,95,97,98,102,103,],[4,4,4,4,4,4,4,4,4,4,]),'operation':([0,2,51,70,94,95,97,98,102,103,],[5,5,5,5,5,5,5,5,5,5,]),'print':([0,2,51,70,94,95,97,98,102,103,],[6,6,6,6,6,6,6,6,6,6,]),'function':([0,2,51,70,94,95,97,98,102,103,],[7,7,7,7,7,7,7,7,7,7,]),'run_function':([0,2,51,70,94,95,97,98,102,103,],[8,8,8,8,8,8,8,8,8,8,]),'class':([0,2,51,70,94,95,97,98,102,103,],[9,9,9,9,9,9,9,9,9,9,]),'self':([0,2,17,18,19,23,24,31,41,42,49,51,52,53,54,55,57,58,59,62,65,67,70,79,86,94,95,97,98,102,103,],[11,11,35,35,35,35,48,35,35,35,48,11,35,35,35,35,35,35,35,35,35,83,11,35,48,11,11,11,11,11,11,]),'expression':([17,18,19,23,31,41,42,52,53,59,62,65,79,],[30,37,40,45,56,63,64,71,40,78,80,40,91,]),'term':([17,18,19,23,31,41,42,52,53,54,55,59,62,65,79,],[32,32,32,32,32,32,32,32,32,73,74,32,32,32,32,]),'factor':([17,18,19,23,31,41,42,52,53,54,55,57,58,59,62,65,79,],[33,33,33,33,33,33,33,33,33,33,33,76,77,33,33,33,33,]),'expressions':([19,53,65,],[39,72,81,]),'variables':([24,49,86,],[46,68,96,]),}

_lr_goto = {}
for _k, _v in _lr_goto_items.items():
   for _x, _y in zip(_v[0], _v[1]):
       if not _x in _lr_goto: _lr_goto[_x] = {}
       _lr_goto[_x][_k] = _y
del _lr_goto_items
_lr_productions = [
  ("S' -> program","S'",1,None,None,None),
  ('program -> statements','program',1,'p_program','py_yacc.py',11),
  ('statements -> statements statement','statements',2,'p_statements','py_yacc.py',18),
  ('statements -> statement','statements',1,'p_statements','py_yacc.py',19),
  ('statement -> assignment','statement',1,'p_statement','py_yacc.py',30),
  ('statement -> operation','statement',1,'p_statement','py_yacc.py',31),
  ('statement -> print','statement',1,'p_statement','py_yacc.py',32),
  ('statement -> function','statement',1,'p_statement','py_yacc.py',33),
  ('statement -> run_function','statement',1,'p_statement','py_yacc.py',34),
  ('statement -> class','statement',1,'p_statement','py_yacc.py',35),
  ('operation -> VARIABLE = expression','operation',3,'p_operation','py_yacc.py',45),
  ('operation -> self = expression','operation',3,'p_operation','py_yacc.py',46),
  ('operation -> VARIABLE + = expression','operation',4,'p_operation','py_yacc.py',47),
  ('operation -> VARIABLE - = expression','operation',4,'p_operation','py_yacc.py',48),
  ('operation -> VARIABLE [ expression ] = expression','operation',6,'p_operation','py_yacc.py',49),
  ('assignment -> VARIABLE = NUMBER','assignment',3,'p_assignment','py_yacc.py',79),
  ('assignment -> self = VARIABLE','assignment',3,'p_assignment','py_yacc.py',80),
  ('assignment -> VARIABLE = VARIABLE','assignment',3,'p_assignment','py_yacc.py',81),
  ('assignment -> VARIABLE [ expression ] = NUMBER','assignment',6,'p_assignment','py_yacc.py',82),
  ('assignment -> VARIABLE = VARIABLE [ expression ]','assignment',6,'p_assignment','py_yacc.py',83),
  ('assignment -> VARIABLE = VARIABLE ( expressions )','assignment',6,'p_assignment','py_yacc.py',84),
  ('expressions -> <empty>','expressions',0,'p_expressions','py_yacc.py',123),
  ('expressions -> expression','expressions',1,'p_expressions','py_yacc.py',124),
  ('expressions -> expressions , expression','expressions',3,'p_expressions','py_yacc.py',125),
  ('expression -> term','expression',1,'p_expression','py_yacc.py',142),
  ('expression -> expression + term','expression',3,'p_expression','py_yacc.py',143),
  ('expression -> expression - term','expression',3,'p_expression','py_yacc.py',144),
  ('term -> factor','term',1,'p_term','py_yacc.py',158),
  ('term -> term * factor','term',3,'p_term','py_yacc.py',159),
  ('term -> term / factor','term',3,'p_term','py_yacc.py',160),
  ('factor -> STR','factor',1,'p_factor','py_yacc.py',174),
  ('factor -> self','factor',1,'p_factor','py_yacc.py',175),
  ('factor -> NUMBER','factor',1,'p_factor','py_yacc.py',176),
  ('factor -> VARIABLE','factor',1,'p_factor','py_yacc.py',177),
  ('factor -> ( expression )','factor',3,'p_factor','py_yacc.py',178),
  ('factor -> VARIABLE [ expression ]','factor',4,'p_factor','py_yacc.py',179),
  ('print -> PRINT ( variables )','print',4,'p_print','py_yacc.py',209),
  ('function -> DEF VARIABLE ( variables ) { statements }','function',8,'p_function','py_yacc.py',216),
  ('function -> DEF VARIABLE ( SELF ) { statements }','function',8,'p_function','py_yacc.py',217),
  ('function -> DEF VARIABLE ( SELF , variables ) { statements }','function',10,'p_function','py_yacc.py',218),
  ('run_function -> VARIABLE ( expressions )','run_function',4,'p_run_function','py_yacc.py',243),
  ('run_function -> VARIABLE . VARIABLE ( expressions )','run_function',6,'p_run_function','py_yacc.py',244),
  ('variables -> <empty>','variables',0,'p_variables','py_yacc.py',259),
  ('variables -> VARIABLE','variables',1,'p_variables','py_yacc.py',260),
  ('variables -> self','variables',1,'p_variables','py_yacc.py',261),
  ('variables -> variables , VARIABLE','variables',3,'p_variables','py_yacc.py',262),
  ('variables -> variables , self','variables',3,'p_variables','py_yacc.py',263),
  ('class -> CLASS VARIABLE { statements }','class',5,'p_class','py_yacc.py',289),
  ('self -> SELF . VARIABLE','self',3,'p_self','py_yacc.py',297),
]
