# parsetab.py
# This file is automatically generated. Do not edit.
_tabversion = '3.2'

_lr_method = 'LALR'

_lr_signature = 'Li5-\x8b+j.\xdf\x84\x1c\x1e&_\x05c'
    
_lr_action_items = {'FLOAT':([9,10,11,25,27,],[20,20,20,20,20,]),'RPAREN':([9,10,12,13,14,15,16,17,18,19,20,21,22,23,24,26,31,33,34,35,],[-5,-5,-17,-19,-7,-15,-16,-6,-9,29,-20,-18,30,31,-11,-10,-14,-8,-12,-13,]),'STR':([9,10,11,25,27,],[15,15,15,15,15,]),'INT':([9,10,11,25,27,],[21,21,21,21,21,]),'PYTHRAN':([3,],[5,]),'LIST':([12,13,14,15,16,18,20,21,24,26,31,32,34,35,],[-17,-19,26,-15,-16,-9,-20,-18,-11,-10,-14,26,-12,-13,]),'RARRAY':([28,],[34,]),'LONG':([9,10,11,25,27,],[13,13,13,13,13,]),'COLUMN':([12,13,14,15,16,18,20,21,24,26,31,32,34,35,],[-17,-19,25,-15,-16,-9,-20,-18,-11,-10,-14,25,-12,-13,]),'LARRAY':([12,13,14,15,16,18,20,21,24,26,31,32,34,35,],[-17,-19,28,-15,-16,-9,-20,-18,-11,-10,-14,28,-12,-13,]),'COMPLEX':([9,10,11,25,27,],[12,12,12,12,12,]),'EXPORT':([5,6,],[6,7,]),'BOOL':([9,10,11,25,27,],[16,16,16,16,16,]),'LPAREN':([7,8,9,10,11,25,27,],[9,10,11,11,11,11,11,]),'SET':([12,13,14,15,16,18,20,21,24,26,31,32,34,35,],[-17,-19,24,-15,-16,-9,-20,-18,-11,-10,-14,24,-12,-13,]),'SHARP':([0,2,29,30,],[3,3,-4,-3,]),'IDENTIFIER':([6,],[8,]),'DICT':([12,13,15,16,18,20,21,24,26,31,32,34,35,],[-17,-19,-15,-16,-9,-20,-18,-11,-10,-14,35,-12,-13,]),'COMMA':([12,13,14,15,16,18,20,21,24,26,31,34,35,],[-17,-19,27,-15,-16,-9,-20,-18,-11,-10,-14,-12,-13,]),'$end':([0,1,2,4,29,30,],[-1,0,-1,-2,-4,-3,]),}

_lr_action = { }
for _k, _v in _lr_action_items.items():
   for _x,_y in zip(_v[0],_v[1]):
      if not _x in _lr_action:  _lr_action[_x] = { }
      _lr_action[_x][_k] = _y
del _lr_action_items

_lr_goto_items = {'exports':([0,2,],[1,4,]),'opt_types':([9,10,],[19,22,]),'term':([9,10,11,25,27,],[18,18,18,18,18,]),'export':([0,2,],[2,2,]),'type':([9,10,11,25,27,],[14,14,14,32,14,]),'types':([9,10,11,27,],[17,17,23,33,]),}

_lr_goto = { }
for _k, _v in _lr_goto_items.items():
   for _x,_y in zip(_v[0],_v[1]):
       if not _x in _lr_goto: _lr_goto[_x] = { }
       _lr_goto[_x][_k] = _y
del _lr_goto_items
_lr_productions = [
  ("S' -> exports","S'",1,None,None,None),
  ('exports -> <empty>','exports',0,'p_exports','/home/serge/sources/pythran/pythran/spec.py',67),
  ('exports -> export exports','exports',2,'p_exports','/home/serge/sources/pythran/pythran/spec.py',68),
  ('export -> SHARP PYTHRAN EXPORT IDENTIFIER LPAREN opt_types RPAREN','export',7,'p_export','/home/serge/sources/pythran/pythran/spec.py',72),
  ('export -> SHARP PYTHRAN EXPORT EXPORT LPAREN opt_types RPAREN','export',7,'p_export','/home/serge/sources/pythran/pythran/spec.py',73),
  ('opt_types -> <empty>','opt_types',0,'p_opt_types','/home/serge/sources/pythran/pythran/spec.py',78),
  ('opt_types -> types','opt_types',1,'p_opt_types','/home/serge/sources/pythran/pythran/spec.py',79),
  ('types -> type','types',1,'p_types','/home/serge/sources/pythran/pythran/spec.py',83),
  ('types -> type COMMA types','types',3,'p_types','/home/serge/sources/pythran/pythran/spec.py',84),
  ('type -> term','type',1,'p_type','/home/serge/sources/pythran/pythran/spec.py',88),
  ('type -> type LIST','type',2,'p_type','/home/serge/sources/pythran/pythran/spec.py',89),
  ('type -> type SET','type',2,'p_type','/home/serge/sources/pythran/pythran/spec.py',90),
  ('type -> type LARRAY RARRAY','type',3,'p_type','/home/serge/sources/pythran/pythran/spec.py',91),
  ('type -> type COLUMN type DICT','type',4,'p_type','/home/serge/sources/pythran/pythran/spec.py',92),
  ('type -> LPAREN types RPAREN','type',3,'p_type','/home/serge/sources/pythran/pythran/spec.py',93),
  ('term -> STR','term',1,'p_term','/home/serge/sources/pythran/pythran/spec.py',108),
  ('term -> BOOL','term',1,'p_term','/home/serge/sources/pythran/pythran/spec.py',109),
  ('term -> COMPLEX','term',1,'p_term','/home/serge/sources/pythran/pythran/spec.py',110),
  ('term -> INT','term',1,'p_term','/home/serge/sources/pythran/pythran/spec.py',111),
  ('term -> LONG','term',1,'p_term','/home/serge/sources/pythran/pythran/spec.py',112),
  ('term -> FLOAT','term',1,'p_term','/home/serge/sources/pythran/pythran/spec.py',113),
]
