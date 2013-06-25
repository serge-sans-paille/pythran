'''
This module contains all the stuff to make your way from python code to
a dynamic library, see __init__.py for exported interfaces.
'''
import sys
import os.path
import sysconfig
import shutil
import logging
logger = logging.getLogger(__name__)

from cxxgen import *
import ast
from middlend import refine
from backend import Cxx
from syntax import check_syntax
from passes import NormalizeIdentifiers
from openmp import GatherOMPData
from config import cfg
from passmanager import PassManager
from numpy import get_include
from typing import extract_constructed_types, pytype_to_ctype
from tables import pythran_ward

from subprocess import check_output, STDOUT, CalledProcessError
from tempfile import mkstemp, NamedTemporaryFile


def _format_cmdline(cmd):
    """No comma when printing a command line allows for copy/paste"""
    return "'" + "' '".join(cmd) + "'"


def _extract_all_constructed_types(v):
    return sorted(set(reduce(lambda x, y: x + y,
                            (extract_constructed_types(t) for t in v), [])),
                  key=len)


def _parse_optimization(optimization):
    '''Turns an optimization of the form
        my_optim
        my_package.my_optim
        into the associated symbol'''
    splitted = optimization.split('.')
    if len(splitted) == 1:
        splitted = ['pythran', 'optimizations'] + splitted
    return reduce(getattr, splitted[1:], __import__(splitted[0]))


def _python_cppflags():
    return ["-I" + sysconfig.get_config_var("INCLUDEPY")]


def _numpy_cppflags():
    return ["-I" + os.path.join(get_include(), 'numpy')]


def _pythran_cppflags():
    curr_dir = os.path.dirname(os.path.dirname(__file__))
    get = lambda *x: '-I' + os.path.join(curr_dir, *x)
    return [get('.'), get('pythran'), get('pythran', 'pythonic++')]


def _python_ldflags():
    return ["-L" + sysconfig.get_config_var("LIBPL"),
            "-lpython" + sysconfig.get_config_var('VERSION')]


def _get_temp(content, suffix=".cpp"):
    '''Get a temporary file for given content, default extension is .cpp
       It is user's responsability to delete when done.'''
    fd, fdpath = mkstemp(suffix)
    with os.fdopen(fd, "w") as cpp:
        cpp.write(content)
    return fd, fdpath


# PUBLIC INTERFACE STARTS HERE


class CompileError(Exception):
    """ Holds an exception when the C++ compilation failed"""

    def __init__(self, cmdline, output):
            self.cmdline = _format_cmdline(cmdline)
            self.output = output
            self._message = "\n".join(["Compile error!\n",
                                       "******** Command line was: ********",
                                       self.cmdline,
                                       "\n******** Output :  ********\n",
                                       self.output])
            super(CompileError, self).__init__(self._message)


def cxxflags():
    """The C++ flags to compile a Pythran generated cpp file"""
    return (cfg.get('user', 'cxxflags').split() +
            cfg.get('sys', 'cxxflags').split())


def cppflags():
    """The C++ flags to preprocess a Pythran generated cpp file"""
    return (_python_cppflags() +
            _numpy_cppflags() +
            _pythran_cppflags() +
            cfg.get('sys', 'cppflags').split() +
            cfg.get('user', 'cppflags').split())


def ldflags():
    """The linker flags to link a Pythran code into a shared library"""
    return (_python_ldflags() +
            cfg.get('sys', 'ldflags').split() +
            cfg.get('user', 'ldflags').split())


def generate_cxx(module_name, code, specs=None, optimizations=None):
    '''python + pythran spec -> c++ code
    returns a BoostPythonModule object

    '''
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
    optimizations = map(_parse_optimization, optimizations)
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
                name_fmt = pythran_ward + "{0}::{1}::type{2}"
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
                     for t in _extract_all_constructed_types(signature)])
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
                            pythran_ward + '{0}::{1}'.format(
                                module_name, internal_func_name),
                            ', '.join(arguments)))])
                    ),
                    function_name
                )
    return mod


def compile_cxxfile(cxxfile, module_so=None, **kwargs):
    '''c++ file -> native module
    Return the filename of the produced shared library
    Raises CompileError on failure

    '''
    # FIXME: not sure about overriding the user defined compiler here...
    compiler = kwargs.get('cxx', cfg.get('user', 'cxx'))

    _cppflags = cppflags() + kwargs.get('cppflags', [])
    _cxxflags = cxxflags() + kwargs.get('cxxflags', [])
    _ldflags = ldflags() + kwargs.get('ldflags', [])

    # Get output filename from input filename if not set
    module_so = module_so or (os.path.splitext(cxxfile)[0] + ".so")
    try:
        cmd = ([compiler, cxxfile]
               + _cppflags
               + _cxxflags
               + ["-shared", "-o", module_so]
               + _ldflags)
        logger.info("Command line: " + _format_cmdline(cmd))
        output = check_output(cmd, stderr=STDOUT)
    except CalledProcessError as e:
        raise CompileError(e.cmd, e.output)
    logger.info("Generated module: " + module_so)
    logger.info("Output: " + output)

    return module_so


def compile_cxxcode(cxxcode, module_so=None, keep_temp=False,
                    **kwargs):
    '''c++ code (string) -> temporary file -> native module.
    Returns the generated .so.

    '''

    # Get a temporary C++ file to compile
    fd, fdpath = _get_temp(cxxcode)
    try:
        module_so = compile_cxxfile(fdpath, module_so, **kwargs)
    finally:
        if not keep_temp:
            # remove tempfile
            os.remove(fdpath)
        else:
            logger.warn("Keeping temporary generated file:" + fdpath)

    return module_so


def compile_pythrancode(module_name, pythrancode, specs=None,
                        opts=None, cpponly=False, module_so=None,
                        **kwargs):
    '''Pythran code (string) -> c++ code -> native module
    Returns the generated .so (or .cpp if `cpponly` is set to true).

    '''

    # Autodetect the Pythran spec if not given as parameter
    from spec import spec_parser
    specs = spec_parser(pythrancode) if specs is None else specs

    # Generate C++, get a BoostPythonModule object
    module = generate_cxx(module_name, pythrancode, specs, opts)

    if cpponly:
        # User wants only the C++ code
        _, output_file = _get_temp(str(module.generate()))
        if module_so:
            shutil.move(output_file, module_so)
            output_file = module_so
        logger.info("Generated C++ source file: " + output_file)
    else:
        # Compile to binary
        output_file = compile_cxxcode(str(module.generate()),
                                      module_so=module_so,
                                      **kwargs)

    return output_file


def compile_pythranfile(file_path, module_so=None, module_name=None,
                        cpponly=True, **kwargs):
    '''Pythran file -> c++ file -> native module
    Returns the generated .so (or .cpp if `cpponly` is set to true).

    '''

    # derive module name from file name
    basedir, basename = os.path.split(file_path)
    module_name = module_name or os.path.splitext(basename)[0]

    # derive destination from file name
    module_so = module_so or os.path.join(basedir, module_name + ".so")
    dl = compile_pythrancode(module_name, file(file_path).read(),
                             module_so=module_so, cpponly=cpponly, **kwargs)
    return module_so


def test_compile():
    '''Simple passthrough compile test.
    May raises CompileError Exception.

    '''
    module_so = compile_cxxcode("\n".join([
        "#define BOOST_PYTHON_MAX_ARITY 4",
        "#include <pythran/pythran.h>",
        "#include <pythran/pythran_gmp.h>"]))
    module_so and os.remove(module_so)
