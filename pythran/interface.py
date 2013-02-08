'''
This module contains all the stuff to make your way from python code to
    a dynamic library
    * cxx_generator transforms a python module to c++ code
    * compile transforms c++ code into a native module
'''
import sys
import errno
import os.path
import distutils.sysconfig

from cxxgen import *
import ast
from middlend import refine, default_optimization_sequence
from backend import Cxx
from syntax import check_syntax
from passes import NormalizeIdentifiers
from openmp import GatherOMPData


from passmanager import PassManager
from tables import pytype_to_ctype_table

from subprocess import check_output, STDOUT, CalledProcessError
from tempfile import mkstemp, NamedTemporaryFile


def pytype_to_ctype(t):
    '''python -> c++ type binding'''
    if isinstance(t, list):
        return 'core::list<{0}>'.format(pytype_to_ctype(t[0]))
    if isinstance(t, set):
        return 'core::set<{0}>'.format(pytype_to_ctype(list(t)[0]))
    elif isinstance(t, dict):
        tkey, tvalue = t.items()[0]
        return 'core::dict<{0},{1}>'.format(pytype_to_ctype(tkey),
                                        pytype_to_ctype(tvalue))
    elif isinstance(t, tuple):
        return 'std::tuple<{0}>'.format(", ".join(pytype_to_ctype(_)
                                    for _ in t))
    elif t in pytype_to_ctype_table:
        return pytype_to_ctype_table[t]
    else:
        raise NotImplementedError("{0}:{1}".format(type(t), t))


def extract_constructed_types(t):
    if isinstance(t, list):
        return [pytype_to_ctype(t)] + extract_constructed_types(t[0])
    elif isinstance(t, set):
        return [pytype_to_ctype(t)] + extract_constructed_types(list(t)[0])
    elif isinstance(t, dict):
        tkey, tvalue = t.items()[0]
        return ([pytype_to_ctype(t)]
                + extract_constructed_types(tkey)
                + extract_constructed_types(tvalue))
    elif isinstance(t, tuple):
        return ([pytype_to_ctype(t)]
                + reduce(
                    lambda x, y: x + y,
                    (extract_constructed_types(e) for e in t))
                )
    elif t == long:
        return ["pythran_long_def"]
    elif t == str:
        return ["core::string"]
    else:
        return []


def extract_all_constructed_types(v):
    return sorted(set(reduce(lambda x, y: x + y,
                (extract_constructed_types(t) for t in v), [])), key=len)


def parse_optimization(optimization):
    '''Turns an optimization of the form
        my_optim
        my_package.my_optim
        into the associated symbol'''
    splitted = optimization.split('.')
    if len(splitted) == 1:
        splitted = ['pythran', 'optimizations'] + splitted
    return reduce(getattr, splitted[1:], __import__(splitted[0]))


def cxx_generator(module_name, code, specs=None, optimizations=None):
    '''python + pythran spec -> c++ code'''
    pm = PassManager(module_name)
    # font end
    ir = ast.parse(code)

    # parse openmp directive
    pm.apply(GatherOMPData, ir)

    # avoid conflicts with cxx keywords
    renamings = pm.apply(NormalizeIdentifiers, ir)
    check_syntax(ir)

    # middle-end
    if not optimizations:
        optimizations = default_optimization_sequence
    else:
        optimizations = [parse_optimization(optim) for optim in optimizations]
    refine(pm, ir, optimizations)
    # back-end
    content = pm.dump(Cxx, ir)

    if specs is None:
        class Generable:
            def __init__(self, content):
                self.content = content

            def generate(self):
                return "\n".join("\n".join(l
                            for l in s.generate()) for s in self.content)
        mod = Generable(content)
    else:
        # uniform typing
        for fname, signatures in specs.items():
            if not isinstance(signatures, tuple):
                specs[fname] = (signatures,)

        mod = BoostPythonModule(module_name)
        mod.use_private_namespace = False
        # very low value for max_arity leads to various bugs
        max_arity = max(4, max(max(map(len, s)) for s in specs.itervalues()))
        mod.add_to_preamble([Define("BOOST_PYTHON_MAX_ARITY", max_arity)])
        mod.add_to_preamble(content)
        mod.add_to_init([Statement(
'boost::python::numeric::array::set_module_and_type("numpy", "ndarray")')])
        mod.add_to_init([Statement(
            'boost::python::implicitly_convertible<std::string,'
            + 'pythonic::core::string>()')])

        for function_name, signatures in specs.iteritems():
            internal_function_name = renamings.get(function_name,
                                                            function_name)
            for sigid, signature in enumerate(signatures):
                numbered_function_name = "{0}{1}".format(
                                        internal_function_name, sigid)
                arguments_types = [pytype_to_ctype(t) for t in signature]
                arguments = ["a{0}".format(i)
                            for i in xrange(len(arguments_types))]
                specialized_fname = "__{0}::{1}::type{2}".format(
                    module_name, internal_function_name, "<{0}>".format(
                    ", ".join(arguments_types)) if arguments_types else "")
                result_type = ("typename std::remove_reference"
                         + "<typename {0}::result_type>::type".format(
                             specialized_fname))
                mod.add_to_init([Statement("python_to_pythran<{0}>()".format(
                t)) for t in extract_all_constructed_types(signature)])
                mod.add_to_init([Statement(
                    "pythran_to_python<{0}>()".format(result_type))])
                mod.add_function(
                        FunctionBody(
                            FunctionDeclaration(
                                Value(
                                    result_type,
                                    numbered_function_name),
                                [Value(t, a) for t, a in zip(
                                            arguments_types, arguments)]),
                            Block([Statement("return {0}()({1})".format(
                                '__{0}::{1}'.format(
                                    module_name, internal_function_name),
                                ', '.join(arguments)))])
                            ),
                        function_name
                        )
    return mod


class ToolChain(object):
    def __init__(self, compiler, cppflags=None,
                cxxflags=None, ldflags=None, check=True):
        self.compiler = compiler
        self.cppflags = cppflags or list()
        self.cxxflags = cxxflags or list()
        self.ldflags = ldflags or list()
        self.check = check

    def compile(self, module, output_filename=None):
        fd, fdpath = mkstemp(suffix=".cpp")
        with os.fdopen(fd, "w") as cpp:
            content = str(module.generate())
            cpp.write(content)
        module_cpp = fdpath
        module_so = output_filename or "{0}.so".format(module.name)
        check_output([self.compiler, module_cpp]
                     + self.cppflags
                     + self.cxxflags
                     + ["-shared", "-o", module_so]
                     + self.ldflags,
                     stderr=STDOUT)
        os.remove(fdpath)
        return module_so

    def check_compile(self, msg, code, cppflags=list(),
                    cxxflags=list(), ldflags=list(), optional=False):
        try:
            if optional or self.check:
                tmpfile = NamedTemporaryFile(suffix=".cpp")
                tmpfile.write(code)
                tmpfile.flush()
                check_output([self.compiler]
                                + self.cppflags
                                + cppflags
                                + self.cxxflags
                                + cxxflags
                                + [tmpfile.name]
                                + self.ldflags
                                + ldflags,
                                stderr=STDOUT)
            self.cppflags.extend(cppflags)
            self.cxxflags.extend(cxxflags)
            self.ldflags.extend(ldflags)
        except CalledProcessError as e:
            raise EnvironmentError(errno.ENOPKG, msg + '\n\n' + e.output)

    def check_package(self, pkg, code, cppflags=list(),
                    cxxflags=list(), ldflags=list(), optional=False):
        return self.check_compile(
            pkg + ' not found, try to add -I or -L flags?',
            code, cppflags, cxxflags, ldflags, optional)

    def configure(self):
        """Look for the many dependencies of pythran and add them to the
           relevant path.
           Raise an EnvironmentError exception otherwise"""

        # basic c++ compiler
        self.check_compile('no valid c++ compiler found',
                """#include <iostream>
int main(int argc, char *argv[])
{
    std::cout << "hello " << (argc>1?argv[1]:"world") << std::endl;
    return 0;
}
""", ldflags=['-fPIC'])
        # c++2011
        self.check_compile(
            'no c++ 2011 support found, try to add compiler specific flags?',
"""#include <utility>
decltype(std::declval<int>() + 1) main()
{
    void * p = nullptr;
    return 0;
}""", cppflags=['-std=c++0x'])

        # python-dev
        self.check_package('python development environment',
                '#include <Python.h>\nint main() { return 0; }',
                cppflags=["-I{0}".format(
                                distutils.sysconfig.get_python_inc())],
                ldflags=['-L{0}/config'.format(
                                distutils.sysconfig.get_python_lib(0, 1)),
                        '-lpython{0}'.format(sys.version[:3])]
                )

        # boost python
        self.check_package('boost::python',
                '#include <boost/python.hpp>\nint main() { return 0; }',
                ldflags=['-lboost_python']
                )

        # GMP
        self.check_package('GNU Multiprecision arithmetic library',
                '#include <gmpxx.h>\nint main() { return 0; }',
                ldflags=['-lgmpxx', '-lgmp']
                )

        # tcmalloc only if available
        try:
            self.check_package('tcmalloc', 'int main() { return 0; }',
                                ldflags=['-ltcmalloc_minimal'],
                                optional=True)
        except EnvironmentError:
            pass

        # pythonic++
        self.check_package('pythonic++',
                '#include <pythonic++.h>\nint main() { return 0; }',
                cppflags=['-I.', '-DENABLE_PYTHON_MODULE']
                         + ['-I{0}'.format(
                            os.path.join(p, "pythran", "pythonic++"))
                            for p in sys.path if os.path.exists(
                                os.path.join(p,
                                    "pythran", "pythonic++", "pythonic++.h"))]
                         + ['-I{0}'.format(p)
                            for p in sys.path if p if os.path.exists(
                                os.path.join(p, "pythran", "pythran.h"))]
        )


def compile(compiler, module, output_filename=None, cppflags=list(),
            cxxflags=list(), check=True):
    '''c++ code + compiler flags -> native module'''
    tc = ToolChain(compiler, cppflags=cppflags, cxxflags=cxxflags, check=check)
    tc.configure()
    return tc.compile(module, output_filename=output_filename)
