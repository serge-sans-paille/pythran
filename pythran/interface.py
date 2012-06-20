'''This module contains all the stuff to make your way from python code to a dynamic library
    * cxx_generator transforms a python module to c++ code
    * compile transforms c++ code into a native module
'''
import sys 
import os.path
import distutils.sysconfig
from cxxgen import *
import ast
from middlend import refine
from backend import cxx_backend
from subprocess import check_call
from tempfile import mkstemp, TemporaryFile
from syntax import check_syntax

pytype_to_ctype_table = {
        complex       : 'std::complex<double>',
        bool          : 'bool',
        int           : 'long',
        float         : 'double',
        str           : 'std::string',
        None          : 'void',
        }

def pytype_to_ctype(t):
    '''python -> c++ type binding'''
    if isinstance(t,list):
        return 'sequence<{0}>'.format(pytype_to_ctype(t[0]))
    elif isinstance(t,tuple):
        return 'std::tuple<{0}>'.format(", ".join(pytype_to_ctype(_) for _ in t))
    elif t in pytype_to_ctype_table:
        return pytype_to_ctype_table[t]
    else:
        raise NotImplementedError("{0}:{1}".format(type(t),t))

def extract_constructed_types(t):
    if isinstance(t, list):
        return [ pytype_to_ctype(t) ] + extract_constructed_types(t[0])
    elif isinstance(t,tuple):
        return [ pytype_to_ctype(t) ] + reduce(lambda x,y:x+y, (extract_constructed_types(e) for e in t))
    else:
        return []

def extract_all_constructed_types(v):
    return sorted(set(reduce(lambda x,y:x+y,(extract_constructed_types(t) for t in v),[])),key=len)

def cxx_generator(module_name, code, specs):
    '''python + pythran spec -> c++ code'''
    # font end
    ir=ast.parse(code)
    check_syntax(ir)
    # middle-end
    refine(ir)
    # backend
    content = cxx_backend(module_name,ir)

    mod=BoostPythonModule(module_name)
    mod.use_private_namespace=False
    mod.add_to_preamble(content)

    for function_name,signatures in specs.iteritems():
        if not isinstance(signatures, tuple): signatures = (signatures,)
        for sigid,signature in enumerate(signatures):
            numbered_function_name="{0}{1}".format(function_name,sigid)
            arguments_types = [pytype_to_ctype(t) for t in signature ]
            arguments = ["a{0}".format(i) for i in xrange(len(arguments_types))]
            specialized_fname = "__{0}::{1}::type{2}".format( module_name, function_name, "<{0}>".format(", ".join(arguments_types)) if  arguments_types else "")
            return_type = "typename {0}::return_type".format(specialized_fname)
            mod.add_to_init([Statement("python_to_pythran<{0}>()".format(t)) for t in extract_all_constructed_types(signature)])
            mod.add_to_init([Statement("pythran_to_python<{0}>()".format(return_type))])
            mod.add_function(
                    FunctionBody(
                        FunctionDeclaration( Value(return_type, numbered_function_name), [ Value( t, "a"+str(i) ) for i,t in enumerate(arguments_types) ]),
                        Block([ Statement("return {0}()({1})".format(
                            '__{0}::{1}'.format(module_name,function_name),
                            ', '.join(arguments) ) ) ] )
                        ),
                    function_name
                    )

    return mod

class ToolChain(object):

    def __init__(self):
        self.compiler="g++"
        self.include_dirs=list()
        self.cppflags=list()
        self.cxxflags=list()
        self.ldflags=list()

    def compile(self, module, output_filename=None):
        fd, fdpath=mkstemp(suffix=".cpp")
        tmperr=TemporaryFile()
        with os.fdopen(fd,"w") as cpp:
            content=str(module.generate())
            cpp.write(content)
        module_cpp=fdpath
        module_so = output_filename if output_filename else "{0}.so".format(module.name) 
        check_call([self.compiler, module_cpp] + self.cxxflags + [  "-shared", "-o", module_so ] + [ "-I{0}".format(d) for d in self.include_dirs ]  + self.cppflags + self.ldflags, stderr=tmperr)
        os.remove(fdpath)
        return module_so



def compile(module, output_filename=None, cppflags=list(), cxxflags=list()):
    '''c++ code + compiler flags -> native module'''
    tc = ToolChain()
    tc.include_dirs.append(".")
    tc.include_dirs.append(distutils.sysconfig.get_python_inc())
    tc.cppflags=cppflags

    tc.include_dirs+=[ os.path.join(p,"pythran", "pythonic++") for p in sys.path if os.path.exists(os.path.join(p,"pythran","pythonic++","pythonic++.h")) ]
    tc.include_dirs+=[ p for p in sys.path if os.path.exists(os.path.join(p,"pythran","pythran.h")) ]

    tc.ldflags.append('-L{0}/config'.format(distutils.sysconfig.get_python_lib(0,1)))
    tc.ldflags.append('-lpython{0}'.format(sys.version[:3]))
    tc.ldflags.append('-lboost_python')
    tc.ldflags.append('-fPIC')

    tc.cxxflags.append("-std=c++0x")
    tc.cxxflags+=cxxflags

    return tc.compile(module, output_filename=output_filename)
