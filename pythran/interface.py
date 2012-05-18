'''This module contains all the stuff to make your way from python code to a dynamic library
    * cxx_generator transforms a python module to c++ code
    * compile transforms c++ code into a native module
'''
import sys 
import os.path
import distutils.sysconfig
from cxxgen import *
import ast
from pythran import CgenVisitor
from subprocess import check_call
from tempfile import mkstemp, TemporaryFile

pytype_to_ctype_table = {
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

def cxx_generator(module_name, code, specs):
    '''python + pythran spec -> c++ code'''
    ir=ast.parse(code)

    #purity = purity_test(ir)
    #impure_functions = { k.name:v for k,v in purity.iteritems() if isinstance(k,ast.FunctionDef) and v}

    content = CgenVisitor(module_name).visit(ir)

    mod=BoostPythonModule(module_name)
    mod.use_private_namespace=False
    mod.add_to_preamble(content)
    for k,v in specs.iteritems():
        #if k in impure_functions:
        #    print >> sys.stderr, "Warning: exporting function '{0}' that writes into its parameters {1}".format(
        #            k,
        #            ", ".join(["'{0}'".format(n) for n in impure_functions[k] ])
        #            )
        arguments_types = [pytype_to_ctype(t) for t in v ]
        arguments = ["a"+str(i) for i in xrange(len(arguments_types))]
        boost_arguments_types = [ "boost::python::list" if at.startswith("sequence<") else 
                "boost::python::tuple" if at .startswith("std::tuple<") else at
                for at in arguments_types ]
        boost_arguments = [ "from_python<{0}>()({1})".format(at,a) if at.startswith("sequence<") or at.startswith("std::tuple<") else a
            for (a,at) in zip(arguments, arguments_types) ]
        specialized_fname = "__{0}::{1}::type{2}".format( module_name, k,
                ("<"+", ".join(arguments_types)+">") if arguments_types else ""
                )
        return_type = "typename to_python<typename {0}::return_type>::type".format(specialized_fname)
        mod.add_function(
                FunctionBody(
                    FunctionDeclaration( Value(return_type, k), [ Value( t, "a"+str(i) ) for i,t in enumerate(boost_arguments_types) ]),
                    Block([ Statement("return ToPython< {0}, typename {1}::return_type>()({2})".format(
                        '__{0}::{1}'.format(module_name,k),
                        specialized_fname,
                        ', '.join(boost_arguments) ) ) ] )
                    )
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

    tc.cxxflags.append("-std=c++0x")
    tc.cxxflags+=cxxflags

    return tc.compile(module, output_filename=output_filename)
