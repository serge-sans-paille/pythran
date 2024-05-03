""" Base file for all Pythran tests. """

import importlib
from numpy import float32, float64, complex128
try:
    from numpy import float128, complex256
except ImportError:
    float128 = float64
    complex256 = complex128

from numpy import intp, intc, number, bool_
from numpy import ndarray, isnan, isinf, isneginf, complex128, complex64
from textwrap import dedent
from threading import Thread
import copy
import math
import glob
import numpy.testing as npt
import os
import numbers
import sys
import unittest
from functools import reduce
from operator import add
import logging

from pythran import compile_pythrancode, spec_parser, load_specfile, frontend
from pythran.backend import Python
from pythran.middlend import refine
from pythran.passmanager import PassManager
from pythran.toolchain import _parse_optimization
from pythran.spec import Spec

logger = logging.getLogger("pythran")
logger.setLevel(logging.INFO)

def harmonize_containers(value):
    if isinstance(value, list):
        def flatten(l, flat):
            for e in l:
                if isinstance(e, list):
                    flatten(e, flat)
                else:
                    flat.append(e)
        flat = []
        flatten(value, flat)

        if not flat:
            return

        if any(not isinstance(v, numbers.Number) for v in flat):
            return

        common_type = type(reduce(add, flat))

        def rec_visit_values(l):
            for i, e in enumerate(l):
                if isinstance(e, list):
                    rec_visit_values(e)
                else:
                    l[i] = common_type(e)

        rec_visit_values(value)


class TestEnv(unittest.TestCase):

    """ Test environment to validate a pythran execution against python. """

    # default options used for the c++ compiler
    PYTHRAN_CXX_FLAGS = ['-O0', '-UNDEBUG', '-U_FORTIFY_SOURCE',
                        ] if sys.platform != "win32" else []

    TEST_RETURNVAL = "TEST_RETURNVAL"

    def check_type(self, ref, res):
        """ Check if type between reference and result match. """
        print("Type of Pythran res : ", type(res))
        print("Type of Python ref : ", type(ref))

        # cope with subtle situation under Windows where numpy.uint32 have same
        # name but different value
        if type(res).__name__ == type(ref).__name__:
            return

        if isinstance(ref, ndarray):
            # res can be an ndarray of dim 0 because of isneginf call
            if ref.ndim == 0 and (not isinstance(res, ndarray)
                                  or res.ndim != 0):
                self.check_type(ref.item(0), res)
            else:
                self.assertIsInstance(res, type(ref))
        elif isinstance(ref, (float, float64)):
            self.assertIsInstance(res, (float, float64))
        elif isinstance(ref, (complex, complex128)):
            self.assertIsInstance(res, (complex, complex128))
        elif isinstance(ref, (bool, bool_)):
            self.assertIsInstance(res, (bool, bool_))
        elif hasattr(ref, 'dtype'):
            if hasattr(res, 'dtype'):
                self.assertEqual(ref.dtype.itemsize, res.dtype.itemsize)
                self.assertEqual(ref.dtype.type(-1), res.dtype.type(-1))
            else:
                self.assertIsInstance(res, int)
        else:
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
        env = {"builtins": __import__("builtins")}

        # Compare if exception raised in python and in pythran are the same
        err_msg = "Excepected exception but none raise."
        try:
            if isinstance(runas, tuple):
                exec(code, env)
                ret_val = env[runas[0]](*runas[1])
            else:
                exec((code + "\n" + runas), env)
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
        loader = importlib.machinery.ExtensionFileLoader(modname, module_path)
        spec = importlib.machinery.ModuleSpec(name=modname, loader=loader,
                                              origin=module_path)
        pymod = importlib._bootstrap._load(spec)

        err_msg = "Excepected exception but none raise."
        try:
            if isinstance(runas, tuple):
                ret_val = getattr(pymod, runas[0])(*runas[1])
            else:
                # Produce the pythran result, exec in the loaded module ctx
                exec(runas, pymod.__dict__)
                ret_val = getattr(pymod, self.TEST_RETURNVAL)
            if check_exception:
                raise AssertionError(err_msg)
            return ret_val
        except BaseException as e:
            if not check_exception or e.args[0] == err_msg:
                raise
            return type(e)

    def cleanup_pythran(self, module_path):
        # Clean temporary DLL
        # FIXME: We can't remove this file while it is used in an import
        # through the exec statement (Windows constraints...)
        if sys.platform != "win32":
            os.remove(module_path)

    def run_test_case(self, code, module_name, runas, module_dir=None, **interface):
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
           pythran.errors.PythranCompileError if generated code can't be compiled.
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
            exec(code + "\n" + begin, {})
            last = self.TEST_RETURNVAL + '=' + runas_commands[-1]
            runas = begin + "\n" + last

        # We run test for each exported function (not for each possible
        # signature.
        for i, name in enumerate(sorted(interface.keys())):
            # If no module name was provided, create one
            modname = (module_name or ("test_" + name)) + str(i)

            # Compile the code using pythran
            cxx_compiled = compile_pythrancode(
                modname, code, interface, module_dir=module_dir, extra_compile_args=self.PYTHRAN_CXX_FLAGS)

            if not runas:
                continue

            python_ref = self.run_python(code, runas)
            pythran_res = self.run_pythran(modname, cxx_compiled, runas)
            self.cleanup_pythran(cxx_compiled)

            print("Python result: ", python_ref)
            print("Pythran result: ", pythran_res)
            harmonize_containers(python_ref)
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
           pythran.errors.PythranCompileError if generated code can't be compiled.
           ...possibly others...
        """
        # Extract special keys from interface.
        prelude = interface.pop('prelude', None)
        check_exception = interface.pop('check_exception', False)
        thread_count = interface.pop('thread_count', 1)

        assert len(interface) == 1

        name = next(iter(interface.keys()))
        modname = "test_" + name

        code = dedent(code)

        cxx_compiled = compile_pythrancode(
            modname, code, interface, extra_compile_args=self.PYTHRAN_CXX_FLAGS)

        # FIXME Check should be done on input parameters after function call
        python_ref = self.run_python(code, (name, copy.deepcopy(params)),
                                     prelude, check_exception)

        run_pythran_args = (modname, cxx_compiled, (name, params),
                            prelude, check_exception)
        pythran_res = self.run_pythran(*run_pythran_args)

        if check_exception:
            if not issubclass(python_ref, pythran_res):
                raise AssertionError(
                    "expected exception was %s, but received %s" %
                    (python_ref, pythran_res))
            else:
                return

        print("Python result: ", python_ref)
        print("Pythran result: ", pythran_res)
        harmonize_containers(python_ref)
        self.assertAlmostEqual(python_ref, pythran_res)

        if thread_count > 1:
            threads = [Thread(target=self.run_pythran,
                              args=run_pythran_args)
                       for _ in range(1, thread_count)]
            for thread in threads:
                thread.start()
            for thread in threads:
                thread.join()
        self.cleanup_pythran(cxx_compiled)


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

        ir, _ = frontend.parse(pm, dedent(code))

        optimizations = [_parse_optimization(opt) for opt in optimizations]
        refine(pm, ir, optimizations)

        content = pm.dump(Python, ir)

        if content != dedent(ref).strip():
            raise AssertionError(
                "AST is not the one expected. Reference was %s,"
                "but received %s" % (repr(dedent(ref).strip()), repr(content)))


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

        # Look for an extra spec file
        spec_file = os.path.splitext(file_)[0] + '.pythran'
        if os.path.isfile(spec_file):
            return load_specfile(spec_file)
        elif file_ is None:
            return Spec({name: []})
        else:
            with open(file_) as fd:
                return spec_parser(fd.read())

    @staticmethod
    def extract_runas(name, filepath):
        with open(filepath) as runas_fd:
            runas_list = [line for line in runas_fd.readlines()
                          if any(line.startswith(marker) for
                                 marker in TestFromDir.runas_markers)]
            return runas_list or [None]

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

        def __init__(self, test_env, module_name, module_code, module_dir,
                     runas=None, **specs):
            self.test_env = test_env
            self.module_name = module_name
            self.module_code = module_code
            self.module_dir = module_dir
            self.runas = runas
            self.specs = specs

        def __name__(self):
            return self.module_name

        def __call__(self):
            if "unittest.skip" in self.module_code:
                return self.test_env.skipTest("Marked as skippable")

            if "unittest.python3.skip" in self.module_code:
                return self.test_env.skipTest("Marked as skippable")

            # resolve import locally to where the tests are located
            sys.path.insert(0, self.test_env.path)

            self.test_env.run_test_case(self.module_code, self.module_name,
                                        self.runas, module_dir=self.module_dir,
                                        **self.specs)
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
            specs = target.interface(name, filepath).functions

            runas_list = target.extract_runas(name, filepath)
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
                    with open(filepath) as fd:
                        func = TestFromDir.TestFunctor(
                            target, name + suffix + str(n), fd.read(),
                            os.path.dirname(filepath),
                            runas=runas, **specs)
                setattr(target, "test_" + name + suffix + str(n), func)
