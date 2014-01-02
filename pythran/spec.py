'''
This module provides a dummy parser for pythran annotations.
    * spec_parser reads the specs from a python module and returns them.
'''
import ply.lex as lex
import ply.yacc as yacc
import os.path
from numpy import array


class SpecParser:
    """ A parser that scans a file lurking for lines such as the one below.
    It then generates a pythran-compatible signature to inject into compile.
#pythran export a((float,(int,long),str list) list list)
#pythran export a(str)
#pythran export a( (str,str), int, long list list)
#pythran export a( {str} )
"""

    ## lex part
    reserved = {
            'pythran': 'PYTHRAN',
            'export': 'EXPORT',
            'list': 'LIST',
            'set': 'SET',
            'dict': 'DICT',
            'str': 'STR',
            'bool': 'BOOL',
            'complex': 'COMPLEX',
            'int': 'INT',
            'long': 'LONG',
            'float': 'FLOAT',
            }
    tokens = (['IDENTIFIER', 'SHARP', 'COMMA', 'COLUMN', 'LPAREN', 'RPAREN']
            + list(reserved.values())
            + ['LARRAY', 'RARRAY'])

    # token <> regexp binding
    t_SHARP = r'\#'
    t_COMMA = r','
    t_COLUMN = r':'
    t_LPAREN = r'\('
    t_RPAREN = r'\)'
    t_RARRAY = r'\]'
    t_LARRAY = r'\['

    def t_IDENTIFER(self, t):
        r'[a-zA-Z_][a-zA-Z_0-9]*'
        t.type = SpecParser.reserved.get(t.value, 'IDENTIFIER')
        return t

    def t_NUMBER(self, t):
        r'[0-9]+'
        t.type = 'NUMBER'
        return t

    # skipped characters
    t_ignore = ' \t\r'

    # error handling
    def t_error(self, t):
        t.lexer.skip(1)

    # Define a rule so we can track line numbers
    def t_newline(self, t):
        r'\n+'
        t.lexer.lineno += len(t.value)

    ## yacc part

    def p_exports(self, p):
        '''exports :
                   | export exports'''
        p[0] = self.exports

    def p_export(self, p):
        '''export : SHARP PYTHRAN EXPORT IDENTIFIER LPAREN opt_types RPAREN
                  | SHARP PYTHRAN EXPORT EXPORT LPAREN opt_types RPAREN'''
        # handle the unlikely case where a function name is ... export :-)
        self.exports[p[4]] = self.exports.get(p[4], ()) + (p[6],)

    def p_opt_types(self, p):
        '''opt_types :
                     | types'''
        p[0] = p[1] if len(p) == 2 else []

    def p_types(self, p):
        '''types : type
                 | type COMMA types'''
        p[0] = [p[1]] + ([] if len(p) == 2 else p[3])

    def p_type(self, p):
        '''type : term
                | type LIST
                | type SET
                | type LARRAY RARRAY
                | type COLUMN type DICT
                | LPAREN types RPAREN'''
        if len(p) == 2:
            p[0] = p[1]
        elif len(p) == 3 and p[2] == 'list':
            p[0] = [p[1]]
        elif len(p) == 3 and p[2] == 'set':
            p[0] = {p[1]}
        elif len(p) == 4 and p[3] == ')':
            p[0] = tuple(p[2])
        elif len(p) == 4 and p[3] == ']':
            p[0] = array([p[1]])
        elif len(p) == 5:
            p[0] = {p[1]: p[3]}
        else:
            raise SyntaxError("Invalid Pythran spec. "
                    "Unknown text '{0}'".format(p.value))

    def p_term(self, p):
        '''term : STR
                | BOOL
                | COMPLEX
                | INT
                | LONG
                | FLOAT'''
        p[0] = eval(p[1])

    def p_error(self, p):
        p_val = p.value if p else ''
        err = SyntaxError("Invalid Pythran spec near '" + str(p_val) + "'")
        err.lineno = self.lexer.lineno
        if self.input_file:
            err.filename = self.input_file
        raise err

    def __init__(self, **kwargs):
        self.lexer = lex.lex(module=self, debug=0)
        self.parser = yacc.yacc(
                module=self,
                debug=0,
                tabmodule='pythran.parsetab')

    def __call__(self, path):
        self.exports = dict()
        self.input_file = None
        if os.path.isfile(path):
            self.input_file = path
            with file(path) as fd:
                data = fd.read()
        else:
            data = path
        # filter out everything that does not start with a #pythran
        pythran_data = "\n".join((line if line.startswith('#pythran') else ''
                                  for line in data.split('\n')))
        self.parser.parse(pythran_data, lexer=self.lexer)
        if not self.exports:
            import logging
            logger = logging.getLogger("pythran")
            logger.warn("No pythran specification, "
                        "no function will be exported")
        return self.exports


def spec_parser(input):
    return SpecParser()(input)
