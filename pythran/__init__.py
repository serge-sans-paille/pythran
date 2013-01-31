'''
This package provides three entry points
    * spec_parser looks for code annotations in the form of formatted comments
    * cxx_generator turns a python ast into a c++ string
    * compile generates a native module from a c++ string and code annotations

Basic scenario is to turn a Python AST into C++ code:
>>> from ast import parse
>>> code = "def foo(x): return x * 2"
>>> tree = parse(code)
>>> cxx = cxx_generator('my_module', tree)

To generate a native module, one need to add type information:
>>> cxx = cxx_generator('my_module', tree, {'foo':([[int]],)})

Eventually, the type information can be translated from a string:
>>> spec = spec_parser('#pythran export foo(int list)')
>>> cxx = cxx_generator('my_module', tree, spec)

The C++ code can be compiled into a native module with the proper c++ compiler:
>>> compile('c++', cxx)
'my_module.so'
'''

from interface import cxx_generator, compile
from spec import spec_parser
