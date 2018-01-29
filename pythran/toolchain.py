'''
This module contains all the stuff to make your way from python code to
a dynamic library, see __init__.py for exported interfaces.
'''

from pythran.backend import Cxx
from pythran.config import cfg, make_extension
from pythran.cxxgen import PythonModule, Define, Include, Line, Statement
from pythran.cxxgen import FunctionBody, FunctionDeclaration, Value, Block
from pythran.cxxgen import ReturnStatement
from pythran.middlend import refine
from pythran.passmanager import PassManager
from pythran.tables import pythran_ward
from pythran.types import tog
from pythran.types.types import extract_constructed_types
from pythran.types.type_dependencies import pytype_to_deps
from pythran.types.conversion import pytype_to_ctype
from pythran.spec import load_specfile, Spec
from pythran.spec import spec_to_string
from pythran.syntax import check_specs
from pythran.version import __version__
import pythran.frontend as frontend

from datetime import datetime
from distutils.errors import CompileError
from numpy.distutils.core import setup
from numpy.distutils.extension import Extension
import numpy.distutils.ccompiler

from tempfile import mkstemp, mkdtemp
import gast as ast
import logging
import os.path
import shutil
import sys
import glob
import hashlib
from functools import reduce

logger = logging.getLogger('pythran')


# hook taken from numpy.distutils.compiler
# with useless steps  and warning removed
def CCompiler_customize(self, _, need_cxx=0):
    logger.info('customize %s', self.__class__.__name__)
    numpy.distutils.ccompiler.customize_compiler(self)
    if need_cxx:
        # In general, distutils uses -Wstrict-prototypes, but this option is
        # not valid for C++ code, only for C.  Remove it if it's there to
        # avoid a spurious warning on every compilation.
        try:
            self.compiler_so.remove('-Wstrict-prototypes')
        except (AttributeError, ValueError):
            pass

numpy.distutils.ccompiler.replace_method(numpy.distutils.ccompiler.CCompiler,
                                         'customize', CCompiler_customize)


def _extract_all_constructed_types(v):
    return sorted(set(reduce(lambda x, y: x + y,
                             (extract_constructed_types(t) for t in v), [])),
                  key=len)


def _extract_specs_dependencies(specs):
    """ Extract types dependencies from specs for each exported signature. """
    deps = set()
    # for each function
    for signatures in specs.functions.values():
        # for each signature
        for signature in signatures:
            # for each argument
            for t in signature:
                deps.update(pytype_to_deps(t))
    # and each capsule
    for signature in specs.capsules.values():
        # for each argument
        for t in signature:
            deps.update(pytype_to_deps(t))
    # Keep "include" first
    return sorted(deps, key=lambda x: "include" not in x)


def _parse_optimization(optimization):
    '''Turns an optimization of the form
        my_optim
        my_package.my_optim
        into the associated symbol'''
    splitted = optimization.split('.')
    if len(splitted) == 1:
        splitted = ['pythran', 'optimizations'] + splitted
    return reduce(getattr, splitted[1:], __import__(splitted[0]))


def _get_temp(content, suffix=".cpp"):
    '''Get a temporary file for given content, default extension is .cpp
       It is user's responsability to delete when done.'''
    fd, fdpath = mkstemp(suffix)
    with os.fdopen(fd, "w") as cpp:
        cpp.write(content)
    return fd, fdpath


class HasArgument(ast.NodeVisitor):
    '''Checks if a given function has arguments'''
    def __init__(self, fname):
        self.fname = fname

    def visit_Module(self, node):
        for n in node.body:
            if isinstance(n, ast.FunctionDef) and n.name == self.fname:
                return [arg.id for arg in n.args.args]
        return []

# PUBLIC INTERFACE STARTS HERE


def generate_cxx(module_name, code, specs=None, optimizations=None):
    '''python + pythran spec -> c++ code
    returns a PythonModule object and an error checker

    the error checker can be used to print more detailed info on the origin of
    a compile error (e.g. due to bad typing)

    '''

    pm = PassManager(module_name)

    # front end
    ir, renamings, docstrings = frontend.parse(pm, code)

    # middle-end
    optimizations = (optimizations or
                     cfg.get('pythran', 'optimizations').split())
    optimizations = [_parse_optimization(opt) for opt in optimizations]
    refine(pm, ir, optimizations)

    # back-end
    content = pm.dump(Cxx, ir)

    # instantiate the meta program
    if specs is None:

        class Generable(object):
            def __init__(self, content):
                self.content = content

            def __str__(self):
                return str(self.content)

            generate = __str__

        mod = Generable(content)

        def error_checker():
            tog.typecheck(ir)

    else:

        # uniform typing
        if isinstance(specs, dict):
            specs = Spec(specs, {})

        def error_checker():
            types = tog.typecheck(ir)
            check_specs(ir, specs, renamings, types)

        specs.to_docstrings(docstrings)

        if isinstance(code, bytes):
            code_bytes = code
        else:
            code_bytes = code.encode('ascii', 'ignore')
        metainfo = {'hash': hashlib.sha256(code_bytes).hexdigest(),
                    'version': __version__,
                    'date': datetime.now()}

        mod = PythonModule(module_name, docstrings, metainfo)
        mod.add_to_preamble(Define("BOOST_SIMD_NO_STRICT_ALIASING", "1"))
        mod.add_to_includes(
            Include("pythonic/core.hpp"),
            Include("pythonic/python/core.hpp"),
            # FIXME: only include these when needed
            Include("pythonic/types/bool.hpp"),
            Include("pythonic/types/int.hpp"),
            Line("#ifdef _OPENMP\n#include <omp.h>\n#endif")
        )
        mod.add_to_includes(*[Include(inc) for inc in
                              _extract_specs_dependencies(specs)])
        mod.add_to_includes(*content.body)
        mod.add_to_includes(
            Include("pythonic/python/exception_handler.hpp"),
        )

        def warded(module_name, internal_name):
            return pythran_ward + '{0}::{1}'.format(module_name, internal_name)

        for function_name, signatures in specs.functions.items():
            internal_func_name = renamings.get(function_name,
                                               function_name)
            # global variables are functions with no signatures :-)
            if not signatures:
                mod.add_global_var(function_name,
                                   "{}()()".format(warded(module_name,
                                                          internal_func_name)))

            for sigid, signature in enumerate(signatures):
                numbered_function_name = "{0}{1}".format(internal_func_name,
                                                         sigid)
                arguments_types = [pytype_to_ctype(t) for t in signature]
                arguments_names = HasArgument(internal_func_name).visit(ir)
                arguments = [n for n, _ in
                             zip(arguments_names, arguments_types)]
                name_fmt = pythran_ward + "{0}::{1}::type{2}"
                args_list = ", ".join(arguments_types)
                specialized_fname = name_fmt.format(module_name,
                                                    internal_func_name,
                                                    "<{0}>".format(args_list)
                                                    if arguments_names else "")
                result_type = "typename %s::result_type" % specialized_fname
                mod.add_pyfunction(
                    FunctionBody(
                        FunctionDeclaration(
                            Value(
                                result_type,
                                numbered_function_name),
                            [Value(t + '&&', a)
                             for t, a in zip(arguments_types, arguments)]),
                        Block([Statement("""
                            PyThreadState *_save = PyEval_SaveThread();
                            try {{
                                auto res = {0}()({1});
                                PyEval_RestoreThread(_save);
                                return res;
                            }}
                            catch(...) {{
                                PyEval_RestoreThread(_save);
                                throw;
                            }}
                            """.format(warded(module_name,
                                              internal_func_name),
                                       ', '.join(arguments)))])
                    ),
                    function_name,
                    arguments_types
                )

        for function_name, signature in specs.capsules.items():
            internal_func_name = renamings.get(function_name,
                                               function_name)

            arguments_types = [pytype_to_ctype(t) for t in signature]
            arguments_names = HasArgument(internal_func_name).visit(ir)
            arguments = [n for n, _ in
                         zip(arguments_names, arguments_types)]
            name_fmt = pythran_ward + "{0}::{1}::type{2}"
            args_list = ", ".join(arguments_types)
            specialized_fname = name_fmt.format(module_name,
                                                internal_func_name,
                                                "<{0}>".format(args_list)
                                                if arguments_names else "")
            result_type = "typename %s::result_type" % specialized_fname
            docstring = spec_to_string(function_name, signature)
            mod.add_capsule(
                FunctionBody(
                    FunctionDeclaration(
                        Value(result_type, function_name),
                        [Value(t, a)
                         for t, a in zip(arguments_types, arguments)]),
                    Block([ReturnStatement("{0}()({1})".format(
                        warded(module_name, internal_func_name),
                        ', '.join(arguments)))])
                ),
                function_name,
                docstring
            )

    return mod, error_checker


def compile_cxxfile(module_name, cxxfile, output_binary=None, **kwargs):
    '''c++ file -> native module
    Return the filename of the produced shared library
    Raises CompileError on failure

    '''

    builddir = mkdtemp()
    buildtmp = mkdtemp()

    extension_args = make_extension(**kwargs)

    extension = Extension(module_name,
                          [cxxfile],
                          language="c++",
                          **extension_args)

    try:
        setup(name=module_name,
              ext_modules=[extension],
              # fake CLI call
              script_name='setup.py',
              script_args=['--verbose'
                           if logger.isEnabledFor(logging.INFO)
                           else '--quiet',
                           'build_ext',
                           '--build-lib', builddir,
                           '--build-temp', buildtmp,
                           ]
              )
    except SystemExit as e:
        raise CompileError(str(e))

    [target] = glob.glob(os.path.join(builddir, module_name + "*"))
    if not output_binary:
        output_binary = os.path.join(os.getcwd(),
                                     module_name + os.path.splitext(target)[1])
    shutil.move(target, output_binary)
    shutil.rmtree(builddir)
    shutil.rmtree(buildtmp)

    logger.info("Generated module: " + module_name)
    logger.info("Output: " + output_binary)

    return output_binary


def compile_cxxcode(module_name, cxxcode, output_binary=None, keep_temp=False,
                    **kwargs):
    '''c++ code (string) -> temporary file -> native module.
    Returns the generated .so.

    '''

    # Get a temporary C++ file to compile
    _, fdpath = _get_temp(cxxcode)
    output_binary = compile_cxxfile(module_name, fdpath,
                                    output_binary, **kwargs)
    if not keep_temp:
        # remove tempfile
        os.remove(fdpath)
    else:
        logger.warn("Keeping temporary generated file:" + fdpath)

    return output_binary


def compile_pythrancode(module_name, pythrancode, specs=None,
                        opts=None, cpponly=False, output_file=None,
                        **kwargs):
    '''Pythran code (string) -> c++ code -> native module
    Returns the generated .so (or .cpp if `cpponly` is set to true).

    '''

    # Autodetect the Pythran spec if not given as parameter
    from pythran.spec import spec_parser
    if specs is None:
        specs = spec_parser(pythrancode)

    # Generate C++, get a PythonModule object
    module, error_checker = generate_cxx(module_name, pythrancode, specs, opts)

    if 'ENABLE_PYTHON_MODULE' in kwargs.get('undef_macros', []):
        module.preamble.insert(0, Line('#undef ENABLE_PYTHON_MODULE'))

    if cpponly:
        # User wants only the C++ code
        _, tmp_file = _get_temp(str(module))
        if not output_file:
            output_file = module_name + ".cpp"
        shutil.move(tmp_file, output_file)
        logger.info("Generated C++ source file: " + output_file)
    else:
        # Compile to binary
        try:
            output_file = compile_cxxcode(module_name,
                                          str(module),
                                          output_binary=output_file,
                                          **kwargs)
        except CompileError as ce:
            logger.warn("Compilation error, trying hard to find its origin...")
            error_checker()
            logger.warn("Nop, I'm going to flood you with C++ errors!")
            raise

    return output_file


def compile_pythranfile(file_path, output_file=None, module_name=None,
                        cpponly=False, **kwargs):
    """
    Pythran file -> c++ file -> native module.

    Returns the generated .so (or .cpp if `cpponly` is set to true).

    Usage without an existing spec file

    >>> with open('pythran_test.py', 'w') as fd:
    ...    fd.write('def foo(i): return i ** 2')
    >>> cpp_path = compile_pythranfile('pythran_test.py', cpponly=True)

    Usage with an existing spec file:
    >>> with open('pythran_test.pythran', 'w') as fd:
    ...    fd.write('export foo(int)')
    >>> so_path = compile_pythranfile('pythran_test.py')
    """
    if not output_file:
        # derive module name from input file name
        _, basename = os.path.split(file_path)
        module_name = module_name or os.path.splitext(basename)[0]

    else:
        # derive module name from destination output_file name
        _, basename = os.path.split(output_file)
        module_name = module_name or os.path.splitext(basename)[0]

    # Add compiled module path to search for imported modules
    sys.path.append(os.path.dirname(file_path))

    # Look for an extra spec file
    spec_file = os.path.splitext(file_path)[0] + '.pythran'
    if os.path.isfile(spec_file):
        specs = load_specfile(open(spec_file).read())
        kwargs.setdefault('specs', specs)

    output_file = compile_pythrancode(module_name, open(file_path).read(),
                                      output_file=output_file,
                                      cpponly=cpponly,
                                      **kwargs)

    return output_file


def test_compile():
    '''Simple passthrough compile test.
    May raises CompileError Exception.

    '''
    code = '''
        #define BOOST_PYTHON_MAX_ARITY 4
        #include <pythonic/core.hpp>
    '''

    output_file = compile_cxxcode('test', code)
    output_file and os.remove(output_file)
