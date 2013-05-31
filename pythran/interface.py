'''
This module contains all the stuff to make your way from python code to
    a dynamic library
    * cxx_generator transforms a python module to c++ code
    * compile transforms c++ code into a native module
'''
import sys
import os.path
import sysconfig
import shutil

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
        return 'core::ndarray<{0},{1}>'.format(pytype_to_ctype(t.flat[0]),
                                               t.ndim)
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

    if not specs:  # Match "None" AND empty specs
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
            Statement('boost::python::implicitly_convertible<std::string,'
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

    class CompileError(Exception):

        def __init__(self, cmdline, output):
            self.cmdline = "'"+("' '".join(cmdline))+"'"
            self.output = output
            self._message = "\n".join(["Compile error!\n",
                                       "******** Command line was: ********",
                                       self.cmdline,
                                       "\n******** Output :  ********\n",
                                       self.output])

            super(ToolChain.CompileError, self).__init__(self._message)

    @classmethod
    def cxxflags(cls):
        return (cfg.get('user', 'cxxflags').split() +
                cfg.get('sys', 'cxxflags').split())

    @classmethod
    def cppflags(cls):
        return (cls.python_cppflags() +
                cls.numpy_cppflags() +
                cls.pythran_cppflags() +
                cfg.get('sys', 'cppflags').split() +
                cfg.get('user', 'cppflags').split())

    @classmethod
    def python_cppflags(cls):
        return ["-I" + sysconfig.get_config_var("INCLUDEPY")]

    @classmethod
    def numpy_cppflags(cls):
        return ["-I" + os.path.join(get_include(), 'numpy')]

    @classmethod
    def pythran_cppflags(cls):
        curr_dir = os.path.dirname(os.path.dirname(__file__))
        get = lambda *x: '-I' + os.path.join(curr_dir, *x)
        return [get('.'), get('pythran'), get('pythran', 'pythonic++')]

    @classmethod
    def python_ldflags(cls):
        return ["-L" + sysconfig.get_config_var("LIBPL"),
                "-lpython" + sysconfig.get_config_var('VERSION')]

    @classmethod
    def ldflags(cls):
        return (cls.python_ldflags() +
                cfg.get('sys', 'ldflags').split() +
                cfg.get('user', 'ldflags').split())

    @classmethod
    def get_temp(cls, content, suffix=".cpp"):
        '''Get a temporary file for given content, default extension is .cpp
           It is user's responsability to delete when done.'''
        fd, fdpath = mkstemp(suffix)
        with os.fdopen(fd, "w") as cpp:
            cpp.write(content)
        return fd, fdpath

    @classmethod
    def compile_cxxfile(cls, cxxfile, module_so=None, **kwargs):
        '''c++ file -> native module'''
        # FIXME: I'm not sure about overriding the user defined compiler here...
        compiler = kwargs.get('cxx', cfg.get('user', 'cxx'))

        cppflags = cls.cppflags() + kwargs.get('cppflags', [])
        cxxflags = cls.cxxflags() + kwargs.get('cxxflags', [])
        ldflags = cls.ldflags() + kwargs.get('ldflags', [])

        # Get output filename from input filename if not set
        module_so = module_so or (os.path.splitext(cxxfile)[0] + ".so")
        try:
            cmd = ([compiler, cxxfile]
                   + cppflags
                   + cxxflags
                   + ["-shared", "-o", module_so]
                   + ldflags)
            output = check_output(cmd, stderr=STDOUT)
        except CalledProcessError as e:
            raise ToolChain.CompileError(e.cmd, e.output)

        return module_so
    '''c++ file -> native module'''

    @classmethod
    def compile_cxxcode(cls, cxxcode, module_so=None, keep_temp=False,
                        **kwargs):
        '''c++ code (string) -> temporary file -> native module.
           Return the generated .so.'''

        # Get a temporary C++ file to compile
        fd, fdpath = cls.get_temp(cxxcode)
        try:
            module_so = cls.compile_cxxfile(fdpath, module_so, **kwargs)
        finally:
            if not keep_temp:
                # remove tempfile
                os.remove(fdpath)

        return module_so

    @classmethod
    def compile_pythrancode(cls, module_name, pythrancode, specs=None,
                            opts=None, cpponly=False, module_so=None,
                            **kwargs):
        '''Pythran code (string) -> c++ code -> native module'''

        # Autodetect the Pythran spec if not given as parameter
        from spec import spec_parser
        specs = spec_parser(pythrancode) if specs is None else specs

        # Generate C++
        module = cxx_generator(module_name, pythrancode, specs, opts)

        if cpponly:
            # User want only the C++ code
            _, output_file = cls.get_temp(str(module.generate()))
            if module_so:
                shutil.move(output_file, module_so)
        else:
            # Compile to binary
            output_file = cls.compile_cxxcode(str(module.generate()),
                                              module_so=module_so,
                                              **kwargs)

        return output_file

    @classmethod
    def compile_pythranfile(cls, file_path, module_so=None, module_name=None,
                            **kwargs):
        '''Pythran file -> c++ file -> native module'''
        # derive module name from fgile name
        basedir, basename = os.path.split(file_path)
        module_name = module_name or os.path.splitext(basename)[0]

        # derive destination from file name
        module_so = module_so or os.path.join(basedir, module_name + ".so")
        dl = cls.compile_pythrancode(module_name, file(file_path).read(),
                                     module_so=module_so, **kwargs)
        return module_so

    @classmethod
    def test_compile(cls):
        """ Simple passthrough compile test.
        May raises ToolChain.CompileError Exception.
        """
        module_so = cls.compile_cxxcode("\n".join([
            "#define BOOST_PYTHON_MAX_ARITY 4",
            "#include <pythran/pythran.h>",
            "#include <pythran/pythran_gmp.h>"]))
        module_so and os.remove(module_so)
