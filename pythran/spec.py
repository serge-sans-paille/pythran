'''
This module provides a dummy parser for pythran annotations.
    * spec_parser reads the specs from a python module and returns them.
'''

from pythran.types.conversion import pytype_to_pretty_type

from collections import defaultdict
from itertools import product
import re
import sys
import os.path
import ply.lex as lex
import ply.yacc as yacc

from pythran.typing import List, Set, Dict, NDArray, Tuple, Pointer, Fun
from pythran.syntax import PythranSyntaxError


def ambiguous_types(ty0, ty1):
    from numpy import complex64, complex128
    from numpy import float32, float64
    from numpy import int8, int16, int32, int64
    from numpy import uint8, uint16, uint32, uint64

    if isinstance(ty0, tuple):
        if len(ty0) != len(ty1):
            return False
        return all(ambiguous_types(t0, t1) for t0, t1 in zip(ty0, ty1))

    ambiguous_float_types = float, float32, float64
    if ty0 in ambiguous_float_types and ty1 in ambiguous_float_types:
        return True

    ambiguous_cplx_types = complex, complex64, complex128
    if ty0 in ambiguous_cplx_types and ty1 in ambiguous_cplx_types:
        return True

    ambiguous_int_types = (int8, int16, int32, int64,
                           uint8, uint16, uint32, uint64,
                           int,)
    if ty0 in ambiguous_int_types and ty1 in ambiguous_int_types:
        return True

    if type(ty0) is not type(ty1):
        return False

    if not hasattr(ty0, '__args__'):
        return False

    if type(ty0) is NDArray:
        # no ambiguity for dtype
        return ambiguous_types(ty0.__args__[1:], ty1.__args__[1:])
    else:
        return ambiguous_types(ty0.__args__, ty1.__args__)


class Spec(object):
    '''
    Result of spec parsing.

    ``functions'' is a mapping from function name to a tuple of signatures
    ``capsule'' is a mapping from function name to signature
    '''

    def __init__(self, functions, capsules=None):
        self.functions = dict(functions)
        self.capsules = capsules or dict()

        # normalize function signatures
        for fname, signatures in functions.items():
            if not isinstance(signatures, tuple):
                self.functions[fname] = (signatures,)

        self._expand_specs()

        if not self:
            import logging
            logging.warn("No pythran specification, nothing will be exported")

    def __nonzero__(self):
        return bool(self.functions or self.capsules)

    def to_docstrings(self, docstrings):
        for func_name, signatures in self.functions.items():
            sigdocs = [spec_to_string(func_name, sig) for sig in signatures]
            docstrings[func_name] = "Supported prototypes:{}\n{}".format(
                "".join("\n    - " + sigdoc for sigdoc in sigdocs),
                docstrings.get(func_name, '')
            )

    def _expand_specs(self):
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
                if isinstance(arg, NDArray) and len(arg.__args__) - 1 == 2:
                    return [[arg], [NDArray[arg.__args__[0], -1::, -1::]]]
                else:
                    return [[arg]]
            else:
                return [x + y for x in spec_expander(args[:1])
                        for y in spec_expander(args[1:])]

        all_specs = {}
        for function, signatures in self.functions.items():
            expanded_signatures = []
            for signature in signatures:
                expanded_signatures.extend(spec_expander(signature))
            all_specs[function] = tuple(expanded_signatures)
        self.functions = all_specs


class SpecParser(object):

    """
    A parser that scans a file lurking for lines such as the one below.

    It then generates a pythran-compatible signature to inject into compile.
#pythran export a((float,(int,long),str list) list list)
#pythran export a(str)
#pythran export a( (str,str), int, long list list)
#pythran export a( {str} )
"""

    # lex part
    dtypes = {
        'bool': 'BOOL',
        'complex': 'COMPLEX',
        'int': 'INT',
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

    reserved = {
        '#pythran': 'PYTHRAN',
        'export': 'EXPORT',
        'capsule': 'CAPSULE',
        'or': 'OR',
        'list': 'LIST',
        'set': 'SET',
        'dict': 'DICT',
        'str': 'STR',
        'long': 'LONG',
        'None': 'NONE',
        }
    reserved.update(dtypes)

    tokens = ('IDENTIFIER', 'COMMA', 'COLUMN', 'LPAREN', 'RPAREN', 'CRAP',
              'LARRAY', 'RARRAY', 'STAR') + tuple(reserved.values())

    crap = [tok for tok in tokens if tok != 'PYTHRAN']
    some_crap = [tok for tok in crap if tok not in ('LPAREN', 'COMMA')]

    # token <> regexp binding
    t_CRAP = r'[^,:\(\)\[\]*]'
    t_COMMA = r','
    t_COLUMN = r':'
    t_LPAREN = r'\('
    t_RPAREN = r'\)'
    t_RARRAY = r'\]'
    t_LARRAY = r'\['
    t_STAR = r'\*'

    precedence = (
        ('left', 'OR'),
        ('left', 'LIST', 'DICT', 'SET'),
    )

    # regexp to extract pythran specs from comments
    # the first part matches lines with a comment and the pythran keyword
    # the second part matches lines with comments following the pythran ones
    FILTER = re.compile(r'^\s*#\s*pythran[^\n\r]*[\n\r]*'
                        r'^(?:\s*#[^\n\r]*[\n\r]*)*', re.MULTILINE)

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
                   | PYTHRAN EXPORT export_list opt_craps exports
                   | PYTHRAN EXPORT CAPSULE export_list opt_craps exports'''
        if len(p) > 1:
            target = self.exports if len(p) == 6 else self.native_exports
            for key, val in p[len(p)-3]:
                target[key] += val

    def p_export_list(self, p):
        '''export_list : export
                  | export_list COMMA export'''
        p[0] = (p[1],) if len(p) == 2 else (p[1] + (p[3],))

    def p_export(self, p):
        '''export : IDENTIFIER LPAREN opt_types RPAREN
                  | IDENTIFIER
                  | EXPORT LPAREN opt_types RPAREN'''
        # in the unlikely case where the IDENTIFIER is... export
        if len(p) > 2:
            sigs = p[3] or ((),)
        else:
            sigs = ()
        p[0] = p[1], sigs

    def p_opt_craps(self, p):
        '''opt_craps :
                     | some_crap opt_all_craps'''

    def p_opt_all_craps(self, p):
        '''opt_all_craps :
                     | crap opt_all_craps'''

    def p_crap(self, p):
        'crap : '

    def p_some_crap(self, p):
        'some_crap : '

    p_crap.__doc__ += '\n| '.join(crap)
    p_some_crap.__doc__ += '\n| '.join(some_crap)

    def p_dtype(self, p):
        'dtype : '
        # these imports are used indirectly by the eval
        from numpy import complex64, complex128
        from numpy import float32, float64
        from numpy import int8, int16, int32, int64
        from numpy import uint8, uint16, uint32, uint64

        p[0] = eval(p[1]),

    p_dtype.__doc__ += '\n| '.join(dtypes.values())

    def p_opt_types(self, p):
        '''opt_types :
                     | types'''
        p[0] = p[1] if len(p) == 2 else tuple()

    def p_types(self, p):
        '''types : type
                 | type COMMA types'''
        if len(p) == 2:
            p[0] = tuple((t,) for t in p[1])
        else:
            p[0] = tuple((t,) + ts for t in p[1] for ts in p[3])

    def p_array_type(self, p):
        '''array_type : dtype
                | array_type LARRAY array_indices RARRAY'''
        if len(p) == 2:
            p[0] = p[1][0],
        elif len(p) == 5 and p[4] == ']':
            def args(t):
                return t.__args__ if isinstance(t, NDArray) else (t,)
            p[0] = tuple(NDArray[args(t) + p[3]] for t in p[1])

    def p_type(self, p):
        '''type : term
                | array_type
                | pointer_type
                | type LIST
                | type SET
                | type LPAREN opt_types RPAREN
                | type COLUMN type DICT
                | LPAREN types RPAREN
                | LARRAY type RARRAY
                | type OR type
                '''

        if len(p) == 2:
            if isinstance(p[1], tuple):
                p[0] = p[1]
            else:
                p[0] = p[1],
        elif len(p) == 3 and p[2] == 'list':
            p[0] = tuple(List[t] for t in p[1])
        elif len(p) == 3 and p[2] == 'set':
            p[0] = tuple(Set[t] for t in p[1])
        elif len(p) == 5 and p[4] == ')':
            p[0] = tuple(Fun[args, r]
                         for r in p[1]
                         for args in (product(*p[3])
                                      if len(p[3]) > 1 else p[3]))
        elif len(p) == 5:
            p[0] = tuple(Dict[k, v] for k in p[1] for v in p[3])
        elif len(p) == 4 and p[2] == 'or':
            p[0] = p[1] + p[3]
        elif len(p) == 4 and p[3] == ')':
            p[0] = tuple(Tuple[t] for t in p[2])
        elif len(p) == 4 and p[3] == ']':
            p[0] = p[2]
        else:
            raise PythranSyntaxError("Invalid Pythran spec. "
                                     "Unknown text '{0}'".format(p.value))

    def p_pointer_type(self, p):
        '''pointer_type : dtype STAR'''
        p[0] = Pointer[p[1][0]]

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
            p[0] = slice(0, -1, -1)
        else:
            p[0] = slice(0, -1, 1)

    def p_term(self, p):
        '''term : STR
                | NONE
                | LONG
                | dtype'''
        if p[1] == 'str':
            p[0] = str
        elif p[1] == 'None':
            p[0] = type(None)
        elif p[1] == 'long':
            if sys.version_info.major == 3:
                p[0] = int
            else:
                p[0] = long
        else:
            p[0] = p[1][0]

    def p_error(self, p):
        p_val = p.value if p else ''
        err = PythranSyntaxError(
            "Invalid Pythran spec near '{}'".format(p_val))
        err.lineno = self.lexer.lineno
        if self.input_file:
            err.filename = self.input_file
        raise err

    def __init__(self):
        self.lexer = lex.lex(module=self, debug=False)
        # Do not write the table for better compatibility across ply version
        self.parser = yacc.yacc(module=self,
                                debug=False,
                                write_tables=False)

    def read_path_or_text(self, path_or_text):
        if os.path.isfile(path_or_text):
            self.input_file = path_or_text
            with open(path_or_text) as fd:
                data = fd.read()
        else:
            data = path_or_text
        return data

    def __call__(self, path_or_text):
        self.exports = defaultdict(tuple)
        self.native_exports = defaultdict(tuple)
        self.input_file = None

        data = self.read_path_or_text(path_or_text)

        raw = "\n".join(SpecParser.FILTER.findall(data))
        pythran_data = (re.sub(r'#\s*pythran', '\_o< pythran >o_/', raw)
                        .replace('#', '')
                        .replace('\_o< pythran >o_/', '#pythran'))
        self.parser.parse(pythran_data, lexer=self.lexer, debug=False)

        for key, overloads in self.native_exports.items():
            if len(overloads) > 1:
                raise PythranSyntaxError(
                    "Overloads not supported for capsule '{}'".format(key))
            self.native_exports[key] = overloads[0]

        for key, overloads in self.exports.items():
            for i, ty_i in enumerate(overloads):
                sty_i = spec_to_string(key, ty_i)
                for ty_j in overloads[i+1:]:
                    sty_j = spec_to_string(key, ty_j)
                    if sty_i == sty_j:
                        raise PythranSyntaxError(
                            "Duplicate export entry {}.".format(sty_i))
                    if ambiguous_types(ty_i, ty_j):
                        msg = "Ambiguous overloads\n\t{}\n\t{}.".format(sty_i,
                                                                        sty_j)
                        raise PythranSyntaxError(msg)

        return Spec(self.exports, self.native_exports)


class ExtraSpecParser(SpecParser):
    '''
    Extension of SpecParser that works on extra .pythran files
    '''

    def read_path_or_text(self, path_or_text):
        data = super(ExtraSpecParser, self).read_path_or_text(path_or_text)
        # make the code looks like a regular pythran file
        data = re.sub(r'^\s*export', '#pythran export', data,
                      flags=re.MULTILINE)
        return data


def spec_to_string(function_name, spec):
    arguments_types = [pytype_to_pretty_type(t) for t in spec]
    return '{}({})'.format(function_name, ', '.join(arguments_types))


def spec_parser(path_or_text):
    return SpecParser()(path_or_text)


def load_specfile(path_or_text):
    return ExtraSpecParser()(path_or_text)
