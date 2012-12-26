'''
This module contains all the stuff to make your way from python code to
    a dynamic library
    * cxx_generator transforms a python module to c++ code
    * compile transforms c++ code into a native module
'''
import sys
import os.path
import distutils.sysconfig

from cxxgen import *
import ast
from middlend import refine
from backend import Cxx
from syntax import check_syntax
from passes import NormalizeIdentifiers
from openmp import GatherOMPData

from config import cfg


from passmanager import PassManager
from tables import pytype_to_ctype_table
from numpy import get_include, ndarray

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
    elif isinstance(t, ndarray):
        return 'core::ndarray<{0},{1}>'.format(pytype_to_ctype(t.flat[0]), t.ndim)
    elif t in pytype_to_ctype_table:
        return pytype_to_ctype_table[t]
    else:
        raise NotImplementedError("{0}:{1}".format(type(t), t))


def extract_constructed_types(t):
    if isinstance(t, list) or isinstance(t, ndarray):
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
                + sum(map(extract_constructed_types, t), []))
    elif t == long:
        return ["pythran_long_def"]
    elif t == str:
        return ["core::string"]
    else:
        return []


def extract_all_constructed_types(v):
    return sorted(set(reduce(lambda x, y: x + y,
                            (extract_constructed_types(t) for t in v), [])),
                  key=len)


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
    optimizations = (optimizations or
            cfg.get('pythran', 'optimizations').split())
    optimizations = map(parse_optimization, optimizations)
    refine(pm, ir, optimizations)

    # back-end
    content = pm.dump(Cxx, ir)

    if specs is None:
        class Generable:
            def __init__(self, content):
                self.content = content

            def generate(self):
                return "\n".join("\n".join(l for l in s.generate())
                                 for s in self.content)
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
        mod.add_to_init([
            Statement('import_array()'),
            Statement(
                'boost::python::implicitly_convertible<std::string,'
                + 'pythonic::core::string>()')]
            )

        for function_name, signatures in specs.iteritems():
            internal_func_name = renamings.get(function_name,
                                               function_name)
            for sigid, signature in enumerate(signatures):
                numbered_function_name = "{0}{1}".format(internal_func_name,
                                                         sigid)
                arguments_types = [pytype_to_ctype(t) for t in signature]
                arguments = ["a{0}".format(i)
                             for i in xrange(len(arguments_types))]
                name_fmt = "__{0}::{1}::type{2}"
                args_list = ", ".join(arguments_types)
                specialized_fname = name_fmt.format(module_name,
                                                    internal_func_name,
                                                    "<{0}>".format(args_list)
                                                    if arguments_types else "")
                result_type = ("typename std::remove_reference"
                               + "<typename {0}::result_type>::type".format(
                                 specialized_fname))
                mod.add_to_init(
                    [Statement("python_to_pythran<{0}>()".format(t))
                     for t in extract_all_constructed_types(signature)])
                mod.add_to_init([Statement(
                    "pythran_to_python<{0}>()".format(result_type))])
                mod.add_function(
                    FunctionBody(
                        FunctionDeclaration(
                            Value(
                                result_type,
                                numbered_function_name),
                            [Value(t, a)
                             for t, a in zip(arguments_types, arguments)]),
                        Block([Statement("return {0}()({1})".format(
                            '__{0}::{1}'.format(
                                module_name, internal_func_name),
                            ', '.join(arguments)))])
                    ),
                    function_name
                )
    return mod


class ToolChain(object):
    def __init__(self, **kwargs):
        self.compiler = kwargs.get('cxx', cfg.get('user', 'cxx'))

        self.cppflags = self.python_cppflags()
        self.cppflags += self.pythran_cppflags()
        self.cppflags += cfg.get('sys', 'cppflags').split()
        self.cppflags += kwargs.get('cppflags',
                cfg.get('user', 'cppflags').split())

        self.cxxflags = cfg.get('sys', 'cxxflags').split()
        self.cxxflags += kwargs.get('cxxflags',
                cfg.get('user', 'cxxflags').split())

        self.ldflags = self.python_ldflags()
        self.ldflags += cfg.get('sys', 'ldflags').split()
        self.ldflags += kwargs.get('ldflags',
                cfg.get('user', 'ldflags').split())

    def python_cppflags(self):
        return ["-I" + distutils.sysconfig.get_python_inc()]

    def python_ldflags(self):
        return ["-L{0}/config".format(
            distutils.sysconfig.get_python_lib(0, 1))]

    def pythran_cppflags(self):
        curr_dir = os.path.dirname(os.path.dirname(__file__))
        get = lambda *x: '-I' + os.path.join(curr_dir, *x)
        return [get(), get('pythran', 'pythonic++')]

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


def compile(module, output_filename=None, **kwargs):
    '''c++ code + compiler flags -> native module'''
    tc = ToolChain(**kwargs)
    return tc.compile(module, output_filename=output_filename)
