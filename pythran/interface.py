import sys 
import os.path
import shutil
from subprocess import check_call, check_output
from cgen import *
from codepy.bpl import BoostPythonModule
import ast
from pythran import CgenVisitor

pytype_to_ctype_table = {
        bool          : 'bool',
        int           : 'long',
        float         : 'double',
        str           : 'std::string',
        None          : 'void',
        }

def pytype_to_ctype(t):
    if isinstance(t,list):
        return 'sequence<{0}>'.format(pytype_to_ctype(t[0]))
    elif isinstance(t,tuple):
        return 'std::tuple<{0}>'.format(", ".join(pytype_to_ctype(_) for _ in t))
    elif t in pytype_to_ctype_table:
        return pytype_to_ctype_table[t]
    else:
        raise NotImplementedError("{0}:{1}".format(type(t),t))

def cxx_generator(module_name, code, specs):

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
        specialized_fname = "{0}::{1}::type{2}".format( module_name, k,
                ("<"+", ".join(arguments_types)+">") if arguments_types else ""
                )
        return_type = "typename to_python<typename {0}::return_type>::type".format(specialized_fname)
        mod.add_function(
                FunctionBody(
                    FunctionDeclaration( Value(return_type, k), [ Value( t, "a"+str(i) ) for i,t in enumerate(boost_arguments_types) ]),
                    Block([ Statement("return ToPython< {0}, typename {1}::return_type>()({2})".format(
                        '{0}::{1}'.format(module_name,k),
                        specialized_fname,
                        ', '.join(boost_arguments) ) ) ] )
                    )
                )

    return mod

def compile(module, output_filename=None, cppflags=list(), cxxflags=list()):
    from codepy.jit import guess_toolchain
    tc = guess_toolchain()
    tc.include_dirs.append(".")
    tc.cflags.append("-std=c++0x")
    tc.cflags+=cppflags
    tc.include_dirs+=[ p for p in sys.path if os.path.exists(os.path.join(p,"pythran.h")) ]

    check_call(["pkg-config", "pythonic++", "--exists"])
    cflags = check_output(["pkg-config", "pythonic++", "--cflags"]).strip()
    tc.cflags.append(cflags)
    tc.cflags+=cxxflags

    #print module.generate()

    try: pymod = module.compile(tc, wait_on_error=True)
    except:
        print module.generate()
        raise
    if output_filename:
        shutil.copyfile(pymod.__file__, output_filename)
    return pymod
