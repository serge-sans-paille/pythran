""" Base file for all Pythran tests. """

from imp import load_dynamic
from numpy import float32, float64
from numpy import int8, int16, int32, int64, uint8, uint16, uint32, uint64
from numpy import ndarray, isnan, isinf, isneginf, complex128, complex64, bool_
from textwrap import dedent
import copy
import math
import glob
import numpy.testing as npt
import os
import sys
import unittest

import pytest

from pythran import compile_pythrancode, spec_parser, frontend
from pythran.config import have_gmp_support
from pythran.backend import Python
from pythran.middlend import refine
from pythran.passmanager import PassManager
from pythran.toolchain import _parse_optimization


class TestEnv(unittest.TestCase):

    """ Test environment to validate a pythran execution against python. """

    module = pytest.mark.module
    # default options used for the c++ compiler
    PYTHRAN_CXX_FLAGS = ['-O0', '-Wall', '-Wno-unknown-pragmas',
                         '-Wno-mismatched-tags', '-Wno-unused-local-typedefs',
                         '-Wno-unknown-warning-option'] +\
        ([] if sys.platform != "win32" else ["-Werrror"])
    # -Werror can't be use because of boost.Python warning for Windows version

    TEST_RETURNVAL = "TEST_RETURNVAL"

    def check_type(self, ref, res):
        """ Check if type between reference and result match. """
        print "Type of Pythran res : ", type(res)
        print "Type of Python ref : ", type(ref)
        type_matching = (((list, tuple), (list, tuple)),
                         ((float, float64), (int, long, float, float32,
                                             float64)),
                         (float32, (int, long, float, float32)),
                         ((uint64, int64, long), (int, long, uint64, int64)),
                         (bool, (bool, bool_)),
                         # FIXME combiner for boolean doesn't work
                         (int, (int, bool, bool_, int8, int16, int32, int64,
                                uint8, uint16, uint32, uint64, long)))
        if isinstance(ref, ndarray):
            # res can be an ndarray of dim 0 because of isneginf call
            if ref.ndim == 0 and (not isinstance(res, ndarray)
                                  or res.ndim != 0):
                self.check_type(ref.item(0), res)
            else:
                self.assertIsInstance(res, type(ref))
        elif isinstance(res, complex):
            if res.imag == 0:
                self.assertIsInstance(ref, (int, float, complex))
            else:
                self.assertIsInstance(ref, complex)
        else:
            for res_type, ref_type in type_matching:
                if isinstance(res, res_type):
                    self.assertIsInstance(ref, ref_type)
                    return

            self.assertIsInstance(res, type(ref))

    def assertAlmostEqual(self, ref, res):
        """
        Improved version of assertAlmostEqual.

        This new version supports nan, complex and ndarray.
        """
        self.check_type(ref, res)
        if isinstance(res, (list, tuple)):
            self.assertEqual(len(res), len(ref))
            for res_v, ref_v in zip(res, ref):
                self.assertAlmostEqual(ref_v, res_v)
        elif isinstance(ref, ndarray):
            npt.assert_array_almost_equal(ref, res)
        elif isinstance(ref, float):
            if isinf(ref) or isinf(res):
                self.assertEqual(isinf(ref), isinf(res))
                self.assertEqual(isneginf(ref), isneginf(res))
            elif isnan(ref) or isnan(res):
                self.assertEqual(isnan(ref), isnan(res))
            elif ref == res:
                pass
            else:
                # Check float equality using upl :
                # http://numscale.github.io/nstest/design_rationale.html
                (m_ref, e_ref) = math.frexp(ref)
                (m_res, e_res) = math.frexp(res)
                expo = max(e_ref, e_res)
                n_ref = math.ldexp(ref, -expo)
                n_res = math.ldexp(res, -expo)
                e = (m_ref - m_res) if e_ref == e_res else (n_ref - n_res)
                self.assertLessEqual(abs(e) / sys.float_info.epsilon, 3.)
        elif isinstance(ref, (complex, complex64, complex128)):
            self.assertAlmostEqual(ref.real, res.real)
            self.assertAlmostEqual(ref.imag, res.imag)
        else:
            self.assertEqual(ref, res)

    def run_python(self, code, runas, prelude=None, check_exception=False):
        """
        Run test with Python to have a reference to compare.

        runas may be a string to run or a
        tuple : (function name, list of parameters).
        """
        # Caller may requires some cleaning
        prelude and prelude()

        # Produce the reference, python-way, run in an separated 'env'
        env = {"__builtin__": __import__("__builtin__")}

        # Compare if exception raised in python and in pythran are the same
        err_msg = "Excepected exception but none raise."
        try:
            if isinstance(runas, tuple):
                exec code in env
                ret_val = env[runas[0]](*runas[1])
            else:
                exec (code + "\n" + runas) in env
                ret_val = env[self.TEST_RETURNVAL]
            if check_exception:
                raise AssertionError(err_msg)
            return ret_val
        except BaseException as e:
            if not check_exception or (e.args and e.args[0] == err_msg):
                raise
            return type(e)

    def run_pythran(self, modname, module_path, runas, prelude=None,
                    check_exception=False):
        """
        Run Pythran code and clean Pythran dynamic library.

        runas may be a string to run or a
        tuple : (function name, list of parameters).
        """
        # Caller may requires some cleaning
        prelude and prelude()
        pymod = load_dynamic(modname, module_path)

        err_msg = "Excepected exception but none raise."
        try:
            if isinstance(runas, tuple):
                ret_val = getattr(pymod, runas[0])(*runas[1])
            else:
                # Produce the pythran result, exec in the loaded module ctx
                exec runas in pymod.__dict__
                ret_val = getattr(pymod, self.TEST_RETURNVAL)
            if check_exception:
                raise AssertionError(err_msg)
            return ret_val
        except BaseException as e:
            if not check_exception or e.args[0] == err_msg:
                raise
            return type(e)
        finally:
            # Clean temporary DLL
            #FIXME: We can't remove this file while it is used in an import
            # through the exec statement (Windows constraints...)
            if sys.platform != "win32":
                os.remove(module_path)
            pass

    def run_test_case(self, code, module_name, runas, **interface):
        """
        Test if a function call return value is equal for Pythran and Pythran.

        Args:
           code (str):  python (pythran valid) module to test.
           module_name (str): name of the compiled module
           runas (str): command line to run to check output
           interface (dict): pythran interface for the module to test.
                             Each key is the name of a function to call,
                             the value is a list of the arguments' type.

        Returns: nothing.

        Raises:
           AssertionError by 'unittest' if return value differ.
           SyntaxError if code is not python valid.
           pythran.CompileError if generated code can't be compiled.
           ...possibly others...
        """
        # Extract special keys from interface.
        if runas:
            # runas is a python code string to run the test. By convention
            # the last statement of the sequence is the value to test.
            # We insert ourselves a variable to capture this value:
            # "a=1; b=2; myfun(a+b,a-b)" => "a=1; b=2; RES=myfun(a+b,a-b)"
            runas_commands = runas.split(";")
            begin = ";".join(runas_commands[:-1])
            # this tests the runas initialisation syntax
            exec code + "\n" + begin in {}
            last = self.TEST_RETURNVAL + '=' + runas_commands[-1]
            runas = begin + "\n" + last

        # We run test for each exported function (not for each possible
        # signature.
        for i, name in enumerate(sorted(interface.keys())):
            # If no module name was provided, create one
            modname = (module_name or ("test_" + name)) + str(i)

            # Compile the code using pythran
            cxx_compiled = compile_pythrancode(
                modname, code, None, extra_compile_args=self.PYTHRAN_CXX_FLAGS)

            if not runas:
                continue

            python_ref = self.run_python(code, runas)
            pythran_res = self.run_pythran(modname, cxx_compiled, runas)

            print "Python result: ", python_ref
            print "Pythran result: ", pythran_res
            self.assertAlmostEqual(python_ref, pythran_res)

    def run_test(self, code, *params, **interface):
        """
        Test if a function call return value is equal for Pythran and Pythran.

        Args:
           code (str):  python (pythran valid) module to test.
           params (tuple): arguments to pass to the function to test.
           prelude (fct): function to call between 'code' and the c++
                          generated code
           interface (dict): pythran interface for the module to test.
                             Each key is the name of a function to call,
                             the value is a list of the arguments' type.
                             Special keys are 'prelude' and 'check_exception'.

        Returns: nothing.

        Raises:
           AssertionError by 'unittest' if return value differ.
           SyntaxError if code is not python valid.
           pythran.CompileError if generated code can't be compiled.
           ...possibly others...
        """
        # Extract special keys from interface.
        prelude = interface.pop('prelude', None)
        check_exception = interface.pop('check_exception', False)

        assert len(interface) == 1

        name = interface.keys()[0]
        modname = "test_" + name

        code = dedent(code)

        cxx_compiled = compile_pythrancode(
            modname, code, interface, extra_compile_args=self.PYTHRAN_CXX_FLAGS)

        # FIXME Check should be done on input parameters after function call
        python_ref = self.run_python(code, (name, copy.deepcopy(params)),
                                     prelude, check_exception)
        pythran_res = self.run_pythran(modname, cxx_compiled, (name, params),
                                       prelude, check_exception)

        if check_exception:
            if pythran_res != python_ref:
                raise AssertionError(
                    "expected exception was %s, but received %s" %
                    (python_ref, pythran_res))

        print "Python result: ", python_ref
        print "Pythran result: ", pythran_res
        self.assertAlmostEqual(python_ref, pythran_res)

    @staticmethod
    def check_ast(code, ref, optimizations):
        """
        Check if a final node is the same as expected.

        Parameters
        ----------
        code : str
            code we want to check after refine and optimizations
        ref : str
            The expected dump for the AST
        optimizations : [optimization]
            list of optimisation to apply

        Raises
        ------
        is_same : AssertionError
            Raise if the result is not the one expected.
        """
        pm = PassManager("testing")

        ir, _, _, _ = frontend.parse(pm, code)

        optimizations = map(_parse_optimization, optimizations)
        refine(pm, ir, optimizations)

        content = pm.dump(Python, ir)

        if content != ref:
            raise AssertionError(
                "AST is not the one expected. Reference was %s,"
                "but received %s" % (repr(ref), repr(content)))


class TestFromDir(TestEnv):

    """
    Enable tests for a full test cases directory.

    This class load test from individual .py in a directory and expose
    them to the unittest framework. Methods are added to the class (not the
    instance object) because py.test will collect tests by introspection before
    eventually instantiating the class for each test.

    It is intended to be subclassed and then initialized using the static
    populate() method.

    A few class attributes defined the behavior:

    check_output -- Trigger code execution and match return value for Pythran
                    compiled code against pure python. If set to False, only
                    the compilation step is checked.
    files        -- list of files to load, if empty path is used (see below)
    path         -- path where every .py will be loaded
    interface    -- method returning the Pythran interface to use (dict)

    """

    check_output = True
    files = None
    path = "defined_by_subclass"
    runas_markers = ('#runas ', '# runas')

    @staticmethod
    def interface(name=None, file_=None):
        """ Return Pythran specs."""
        default_value = {name: []}
        return spec_parser(open(file_).read()) if file_ else default_value

    def __init__(self, *args, **kwargs):
        """ Dynamically add methods for unittests, second stage. """
        TestFromDir.populate(self, stub=False)

        super(TestFromDir, self).__init__(*args, **kwargs)

    class TestFunctor(object):

        """
        Class to holds test information for a given test file.

        This Functor holds for test_* dynamically added method, one per
        input file. It takes at initialization all the informations required
        for a straightforward dispatch to TestEnv.run_test()
        """

        def __init__(self, test_env, module_name, module_code, runas=None,
                     **specs):
            self.test_env = test_env
            self.module_name = module_name
            self.module_code = module_code
            self.runas = runas
            self.specs = specs

        def __name__(self):
            return self.module_name

        def __call__(self):
            if "unittest.skip" in self.module_code:
                return self.test_env.skipTest("Marked as skippable")

            if ("unittest.gmp.skip" in self.module_code
                    and not have_gmp_support(
                        extra_compile_args=self.test_env.PYTHRAN_CXX_FLAGS)):
                return self.test_env.skipTest("Marked as skippable")

            # resolve import locally to where the tests are located
            sys.path.insert(0, self.test_env.path)

            self.test_env.run_test_case(self.module_code, self.module_name,
                                        self.runas, **self.specs)
            # restore import path
            sys.path.pop(0)

    @staticmethod
    def populate(target, stub=True):
        """
        Add unittests methods to `target`.

        The python unittest framework detect method named test_* by
        introspection on the class before instantiation. Unfortunately to
        access the TestEnv instance from the method the Functor has to be
        initialized after `target` instantiation. Thus there is a two-stage
        initialization: first we populate the class with 'stub' functions, just
        to satisfy python unittest collect, and then at instantiation the stub
        are replace with the Functor properly initialized with a reference to
        "self".
        """
        if not target.files:
            # No explicit list of files, default to load the whole directory
            target.files = glob.glob(os.path.join(target.path, "*.py"))

        for filepath in target.files:
            # Module name is file name and external interface is default value
            name, _ = os.path.splitext(os.path.basename(filepath))
            specs = target.interface(name, filepath)
            runas_list = [line for line in file(filepath).readlines()
                          if any(line.startswith(marker) for
                                 marker in TestFromDir.runas_markers)]
            runas_list = runas_list or [None]
            for n, runas in enumerate(runas_list):
                if runas:
                    # Remove the runas marker
                    runas = runas[runas.find(' ', 2) + 1:]
                    suffix = "_run"
                else:
                    suffix = '_norun'

                if stub:
                    # First stage, we add dummy function.
                    def func():
                        """ Useless function to populate TestCase. """
                        return
                else:
                    # Second stage, we change dummy function by real one.
                    func = TestFromDir.TestFunctor(
                        target, name + suffix + str(n), file(filepath).read(),
                        runas=runas, **specs)

                setattr(target, "test_" + name + suffix + str(n), func)
