'''
This package provides several entry points
    * spec_parser looks for code annotations in the form of formatted comments
    * functions defined in toolchain.py:
       * generate_cxx:    python (str) to c++ code, returns a BoostPythonModule
       * compile_cxxfile: c++ (file) to DLL, returns DLL filename
       * compile_cxxcode: c++ (str) to DLL, returns DLL filename
       * compile_pythrancode: python (str) to so/cpp, returns output filename
       * compile_pythranfile: python (file) to so/cpp, returns output filename
       * test_compile: passthrough compile test, raises CompileError Exception.

Basic scenario is to turn a Python AST into C++ code:
>>> from ast import parse
>>> code = "def foo(x): return x * 2"
>>> tree = parse(code)
>>> cxx = generate_cxx('my_module', tree) # gets a BoostPythonModule
>>> print cxx.generate()

To generate a native module, one need to add type information:
>>> cxx = generate_cxx('my_module', tree, {'foo':([[int]],)})

Eventually, the type information can be translated from a string:
>>> spec = spec_parser('#pythran export foo(int list)')
>>> cxx = generate_cxx('my_module', tree, spec)

Higher level entry points includes:
>>> dll_file = compile_pythranfile("my_python_file.py")
>>> cpp_file = compile_pythranfile("my_python_file.py",cpponly=True)
>>> dll_file = compile_pythrancode("... /* python code here */ ...")
>>> dll_file = compile_cxxfile("my_cpp_file.cpp"):

'''

__version__ = '0.5.0'

from toolchain import (generate_cxx, compile_cxxfile, compile_cxxcode,
                       compile_pythrancode, compile_pythranfile, test_compile,
                       CompileError)
from spec import spec_parser
