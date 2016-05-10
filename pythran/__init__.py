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
>>> code = "def foo(x): return x * 2"
>>> cxx_generator = generate_cxx('my_module', code) # gets a BoostPythonModule
>>> cxx = cxx_generator.generate()

To generate a native module, one need to add type information:
>>> cxx = generate_cxx('my_module', code, {'foo':([[int]],)})

Eventually, the type information can be translated from a string:
>>> spec = spec_parser('#pythran export foo(int list)')
>>> cxx = generate_cxx('my_module', code, spec)

Higher level entry points include:
>>> open('my_module.py', 'w').write(code)
>>> dll_file = compile_pythranfile("my_module.py")
>>> cpp_file = compile_pythranfile("my_module.py",cpponly=True)
>>> dll_file = compile_pythrancode("my_module", code)
>>> dll_file = compile_cxxfile("my_module", cpp_file)

Cleanup
>>> import os, glob
>>> for target in glob.glob('my_module.*'):
...     os.remove(target)

'''

import pythran.log
from pythran.toolchain import (generate_cxx, compile_cxxfile, compile_cxxcode,
                               compile_pythrancode, compile_pythranfile,
                               test_compile)
from pythran.spec import spec_parser
from pythran.dist import PythranExtension
from pythran.version import __version__

try:
    import pythran.magic
except ImportError:
    pass  # ipython magic disabled
