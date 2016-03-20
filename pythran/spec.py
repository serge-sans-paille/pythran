'''
This module provides a dummy parser for pythran annotations.
    * spec_parser reads the specs from a python module and returns them.
'''

from pythran.types.conversion import pytype_to_pretty_type

from numpy import array, ndarray

import re
import os.path
import ply.lex as lex
import ply.yacc as yacc


class SpecParser:

    """
    A parser that scans a file lurking for lines such as the one below.

    It then generates a pythran-compatible signature to inject into compile.
#pythran export a((float,(int,long),str list) list list)
#pythran export a(str)
#pythran export a( (str,str), int, long list list)
#pythran export a( {str} )
"""

    # lex part
    reserved = {
        '#pythran': 'PYTHRAN',
        'export': 'EXPORT',
        'list': 'LIST',
        'set': 'SET',
        'dict': 'DICT',
        'str': 'STR',
        'bool': 'BOOL',
        'complex': 'COMPLEX',
        'int': 'INT',
        'long': 'LONG',
        'None': 'NONE',
        'float': 'FLOAT',
        'uint8': 'UINT8',
        'uint16': 'UINT16',
        'uint32': 'UINT32',
        'uint64': 'UINT64',
        'int8': 'INT8',
        'int16': 'INT16',
        'int32': 'INT32',
        'int64': 'INT64',
        'float32': 'FLOAT32',
        'float64': 'FLOAT64',
        'complex64': 'COMPLEX64',
        'complex128': 'COMPLEX128',
        }
    tokens = (['IDENTIFIER', 'COMMA', 'COLUMN', 'LPAREN', 'RPAREN', 'CRAP'] +
              list(reserved.values()) +
              ['LARRAY', 'RARRAY'])

    # token <> regexp binding
    t_CRAP = r'.'
    t_COMMA = r','
    t_COLUMN = r':'
    t_LPAREN = r'\('
    t_RPAREN = r'\)'
    t_RARRAY = r'\]'
    t_LARRAY = r'\['

    # regexp to extract pythran specs from comments
    # the first part matches lines with a comment and the pythran keyword
    # the second part matches lines with comments following the pythran ones
    FILTER = re.compile(r'^\s*#\s*pythran[^\n\r]*[\n\r]+'
                        r'^(?:\s*#[^\n\r]*[\n\r]+)*', re.MULTILINE)

    def t_IDENTIFER(self, t):
        r'\#?[a-zA-Z_][a-zA-Z_0-9]*'
        t.type = SpecParser.reserved.get(t.value, 'IDENTIFIER')
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

    # yacc part

    def p_exports(self, p):
        '''exports :
                   | PYTHRAN EXPORT export_list opt_craps exports'''

    def p_export_list(self, p):
        '''export_list : export
                  | export COMMA export_list'''

    def p_export(self, p):
        '''export : IDENTIFIER LPAREN opt_types RPAREN
                  | IDENTIFIER
                  | EXPORT LPAREN opt_types RPAREN'''
        # handle the unlikely case where the IDENTIFIER is ...
        # export :-)
        if len(p) > 2:
            self.exports[p[1]] = self.exports.get(p[1], ()) + (p[3],)
        else:
            self.exports[p[1]] = ()

    def p_opt_craps(self, p):
        '''opt_craps :
                     | crap opt_craps'''

    def p_crap(self, p):
        '''crap : CRAP
                | IDENTIFIER
                | EXPORT
                | LPAREN
                | RPAREN
                | LARRAY
                | RARRAY
                | COLUMN
                | COMMA
                | DICT
                | SET
                | LIST
                | STR
                | BOOL
                | COMPLEX
                | INT
                | LONG
                | NONE
                | FLOAT
                | UINT8
                | UINT16
                | UINT32
                | UINT64
                | INT8
                | INT16
                | INT32
                | INT64
                | FLOAT32
                | FLOAT64
                | COMPLEX64
                | COMPLEX128'''

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
                | type LARRAY array_indices RARRAY
                | type COLUMN type DICT
                | LPAREN types RPAREN'''

        if len(p) == 2:
            p[0] = p[1]
        elif len(p) == 3 and p[2] == 'list':
            p[0] = [p[1]]
        elif len(p) == 3 and p[2] == 'set':
            p[0] = {p[1]}
        elif len(p) == 5 and p[4] == ']':
            p[0] = reduce(lambda x, y: array([x])[::y], p[3], p[1])
        elif len(p) == 5:
            p[0] = {p[1]: p[3]}
        elif len(p) == 4 and p[3] == ')':
            p[0] = tuple(p[2])
        else:
            raise SyntaxError("Invalid Pythran spec. "
                              "Unknown text '{0}'".format(p.value))

    def p_array_indices(self, p):
        '''array_indices : array_index
                         | array_index COMMA array_indices'''
        if len(p) == 2:
            p[0] = p[1],
        else:
            p[0] = (p[1],) + p[3]

    def p_array_index(self, p):
        '''array_index :
                       | COLUMN
                       | COLUMN COLUMN'''
        if len(p) == 3:
            p[0] = -1
        else:
            p[0] = 1

    def p_term(self, p):
        '''term : STR
                | BOOL
                | COMPLEX
                | INT
                | LONG
                | NONE
                | FLOAT
                | UINT8
                | UINT16
                | UINT32
                | UINT64
                | INT8
                | INT16
                | INT32
                | INT64
                | FLOAT32
                | FLOAT64
                | COMPLEX64
                | COMPLEX128'''
        # these imports are used indirectly by the eval
        from numpy import complex64, complex128
        from numpy import float32, float64
        from numpy import int8, int16, int32, int64
        from numpy import uint8, uint16, uint32, uint64

        p[0] = eval(p[1])
        if p[0] is None:
            p[0] = type(None)

    def p_error(self, p):
        p_val = p.value if p else ''
        err = SyntaxError("Invalid Pythran spec near '" + str(p_val) + "'")
        err.lineno = self.lexer.lineno
        if self.input_file:
            err.filename = self.input_file
        raise err

    def __init__(self):
        self.lexer = lex.lex(module=self, debug=0)
        # Do not write the table for better compatibility across ply version
        self.parser = yacc.yacc(module=self,
                                debug=0,
                                write_tables=False)

    def __call__(self, path_or_text):
        self.exports = dict()
        self.input_file = None
        if os.path.isfile(path_or_text):
            self.input_file = path_or_text
            with file(path_or_text) as fd:
                data = fd.read()
        else:
            data = path_or_text

        raw = "\n".join(SpecParser.FILTER.findall(data))
        pythran_data = (re.sub(r'#\s*pythran', '\_o< pythran >o_/', raw)
                        .replace('#', '')
                        .replace('\_o< pythran >o_/', '#pythran'))
        self.parser.parse(pythran_data, lexer=self.lexer)
        if not self.exports:
            import logging
            logging.warn("No pythran specification, "
                         "no function will be exported")
        return self.exports


def expand_specs(specs):
    '''
    Expand a spec in its various variant

    for a generic spec description, generate the possible variants,
    esp. for ndarrays
    '''
    def spec_expander(args):
        n = len(args)
        if n == 0:
            return [[]]
        elif n == 1:
            arg = args[0]
            # handle f_contiguous storage as a transpose of two elements
            # currently only supported by pythonic for 2D matrices :-/
            # the trick is to use an array of two elements and transpose it
            # so that its storage becomes f_contiguous only
            if isinstance(arg, ndarray) and arg.ndim == 2:
                return [[arg], [arg.repeat(2, axis=0).T]]
            else:
                return [[arg]]
        else:
            return [x + y for x in spec_expander(args[:1])
                    for y in spec_expander(args[1:])]
    all_specs = {}
    for function, signatures in specs.items():
        expanded_signatures = []
        for signature in signatures:
            expanded_signatures.extend(spec_expander(signature))
        all_specs[function] = tuple(expanded_signatures)
    return all_specs


def specs_to_docstrings(specs, docstrings):
    for function_name, signatures in specs.iteritems():
        sigdocs = []
        for sigid, signature in enumerate(signatures):
            arguments_types = [pytype_to_pretty_type(t) for t in signature]
            function_signatures = '{}({})'.format(
                function_name,
                ', '.join(arguments_types)
            )
            sigdocs.append(function_signatures)
        docstrings[function_name] = "Supported prototypes:{}\n{}".format(
            "".join("\n    - " + sigdoc for sigdoc in sigdocs),
            docstrings.get(function_name, '')
        )


def spec_parser(path):
    return SpecParser()(path)
