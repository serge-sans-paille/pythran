from pythran import compile_pythrancode
from pythran.backend import Python
from pythran.middlend import refine
from pythran.passmanager import PassManager
from pythran.toolchain import _parse_optimization
import pythran.frontend as frontend
from imp import load_dynamic
import unittest
import os
import re
import sys
from numpy import ndarray
import numpy.testing as npt
import ast


class TestEnv(unittest.TestCase):
    """
    Test environment to validate a pythran execution against python
    """

    # default options used for the c++ compiler
    PYTHRAN_CXX_FLAGS = ['-O0', '-fopenmp',
                         '-Wall', '-Wno-unknown-pragmas']
    TEST_RETURNVAL = "TEST_RETURNVAL"

    def assertAlmostEqual(self, ref, res):
        if hasattr(ref, '__iter__'):
            if isinstance(ref, ndarray):
                npt.assert_array_almost_equal(ref, res)
            else:
                self.assertEqual(len(ref), len(res))
                for iref, ires in zip(ref, res):
                    self.assertAlmostEqual(iref, ires)
        else:
            try:
                unittest.TestCase.assertAlmostEqual(self, ref, res)
            except TypeError:
                raise AssertionError("Reference mismatch: pythran return value"
                                     " differs from python.")

    def compare_pythonpythran_results(self, python_ref, pythran_res):
        # Compare pythran result against python ref and raise if mismatch
        try:
            if python_ref != pythran_res:
                print "Python result: ", python_ref
                print "Pythran result: ", pythran_res
                self.assertAlmostEqual(python_ref, pythran_res)
        except ValueError:
            if hasattr(python_ref, '__iter__'):
                self.assertEqual(len(python_ref), len(pythran_res))
                for iref, ires in zip(python_ref, pythran_res):
                    self.assertAlmostEqual(iref, ires)

    def run_test(self, code, *params, **interface):
        """Test if a function call return value is unchanged when
        executed using python eval or compiled with pythran.

        Args:
           code (str):  python (pythran valid) module to test.
           params (tuple): arguments to pass to the function to test.
           prelude (fct): function to call between 'code' and the c++
                          generated code
           interface (dict): pythran interface for the module to test.
                             Each key is the name of a function to call,
                             the value is a list of the arguments' type.
                             Special keys are 'module_name', 'prelude',
                             'runas', 'check_refcount', 'check_exception'
                             and 'check_output'.

        Returns: nothing.

        Raises:
           AssertionError by 'unittest' if return value differ.
           SyntaxError if code is not python valid.
           pythran.CompileError if generated code can't be compiled.
           ...possibly others...
        """

        # Extract special keys from interface.
        module_name = interface.pop('module_name', None)
        prelude = interface.pop('prelude', None)
        check_output = interface.pop('check_output', True)
        runas = interface.pop('runas', None)
        check_refcount = interface.pop('check_refcount', False)
        check_exception = interface.pop('check_exception', False)
        if runas:
            # runas is a python code string to run the test. By convention
            # the last statement of the sequence is the value to test.
            # We insert ourselves a variable to capture this value:
            # "a=1; b=2; myfun(a+b,a-b)" => "a=1; b=2; RES=myfun(a+b,a-b)"
            runas_commands = runas.split(";")
            begin = ";".join(runas_commands[:-1]+[''])
            exec code+"\n"+begin in {}  # this just tests the syntax of runas
            last = self.TEST_RETURNVAL + '=' + runas_commands[-1]
            runas = begin+"\n"+last

        for name in sorted(interface.keys()):
            if not runas:
                # No runas provided, derive one from interface and params
                attributes = []
                runas = ""
                for p in params:
                    if isinstance(p, str):
                        param = "'{0}'".format(p)
                    elif isinstance(p, ndarray):
                        param = "numpy.{0}".format(
                            repr(p).replace("\n", "")
                                   .replace("dtype=", "dtype=numpy."))
                        runas = "import numpy\n"
                    else:
                         # repr preserve the "L" suffix for long
                        param = repr(p)
                    attributes.append(param.replace("nan", "float('nan')")
                                           .replace("inf", "float('inf')"))
                arglist = ",".join(attributes)
                function_call = "{0}({1})".format(name, arglist)
                runas += self.TEST_RETURNVAL + '=' + function_call

            # Caller may requires some cleaning
            prelude and prelude()

            # Produce the reference, python-way, run in an separated 'env'
            env = {'__builtin__': __import__('__builtin__')}
            refcode = code+"\n"+runas

            # Compare if exception raised in python and in pythran are the same
            python_exception_type = None
            pythran_exception_type = None
            try:
                if check_output:
                    exec refcode in env
                    python_ref = env[self.TEST_RETURNVAL]
                    if check_refcount:
                        python_refcount = sys.getrefcount(python_ref)
            except BaseException as e:
                python_exception_type = type(e)
                if not check_exception:
                    raise

            # If no module name was provided, create one
            modname = module_name or ("test_" + name)

            # Compile the code using pythran
            cxx_compiled = compile_pythrancode(modname, code,
                interface, cxxflags=self.PYTHRAN_CXX_FLAGS)

            try:
                if not check_output:
                    return

                # Caller may requires some cleaning
                prelude and prelude()
                pymod = load_dynamic(modname, cxx_compiled)

                try:
                    # Produce the pythran result, exec in the loaded module ctx
                    exec runas in pymod.__dict__
                except BaseException as e:
                    pythran_exception_type = type(e)
                else:
                    pythran_res = getattr(pymod, self.TEST_RETURNVAL)
                    if check_refcount:
                        pythran_refcount = sys.getrefcount(pythran_res)
                        self.assertEqual(python_refcount, pythran_refcount)
                    # Test Results, assert if mismatch
                    if python_exception_type:
                        raise AssertionError(
                                "expected exception was %s, but nothing happend!" %
                                python_exception_type)
                    self.compare_pythonpythran_results(python_ref, pythran_res)

            finally:
                # Clean temporary DLL
                os.remove(cxx_compiled)

            # Only compare the type of exceptions raised
            if pythran_exception_type != python_exception_type:
                if python_exception_type is None:
                    raise e
                else:
                    raise AssertionError(
                    "expected exception was %s, but received %s" %
                    (python_exception_type, pythran_exception_type))

    def check_ast(self, code, ref, optimizations):
        """
            Check if a final node is the same as expected

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

        ir, _ = frontend.parse(pm, code)

        optimizations = map(_parse_optimization, optimizations)
        refine(pm, ir, optimizations)

        content = pm.dump(Python, ir)

        if content != ref:
            raise AssertionError(
            "AST is not the one expected. Reference was %s,"
            "but received %s" % (repr(ref), repr(content)))


class TestFromDir(TestEnv):
    """ This class load test from individual .py in a directory and expose
    them to the unittest framework. Methods are added to the class (not the
    instance object) because py.test will collect tests by introspection before
    eventually instanciating the classe for each test.

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
    runas_marker = '#runas '

    @classmethod
    def interface(cls, name=None, file=None):
        ''' Return Pythran specs.'''
        default_value = {name: []}
        try:
            from pythran import spec_parser
            specs = spec_parser(open(file).read()) if file else default_value
        except SyntaxError:
            specs = default_value
        return specs

    def __init__(self, *args, **kwargs):
        # Dynamically add methods for unittests, second stage (cf populate())
        TestFromDir.populate(self, stub=False)

        super(TestFromDir, self).__init__(*args, **kwargs)

    class TestFunctor(object):
        """ This Functor holds for test_* dynamically added method, one per
        input file. It takes at initialization all the informations required
        for a straightforward dispatch to TestEnv.run_test()

        """

        def __init__(
            self, test_env, module_name, module_code, check_output=True,
                runas=None, **specs):
            self.test_env = test_env
            self.module_name = module_name
            self.module_code = module_code
            self.runas = runas
            self.specs = specs
            self.check_output = check_output

        def __name__(self):
            return self.module_name

        def __call__(self):
            if "unittest.skip" in self.module_code:
                return self.test_env.skipTest("Marked as skippable")
            self.test_env.run_test(self.module_code,
                                   module_name=self.module_name,
                                   check_output=self.check_output,
                                   runas=self.runas,
                                   **self.specs)

    @staticmethod
    def populate(target, stub=True):
        """Add unittests methods to `target`.

        The python unittest framework detect method named test_* by
        introspection on the class before instanciation. Unfortunately to
        access the TestEnv instance from the method the Functor has to be
        initialized after `target` instantiation. Thus there is a two-stage
        initialization: first we populate the class with 'stub' functions, just
        to satisfy python unittest collect, and then at intanciation the stub
        are replace with the Functor properly initialized with a reference to
        "self"

        """
        import glob
        if not target.files:
            # No explicit list of files, default to load the whole directory
            target.files = glob.glob(os.path.join(target.path, "*.py"))

        for filepath in target.files:
            # Module name is file name, also external interface default value
            name, _ = os.path.splitext(os.path.basename(filepath))
            specs = target.interface(name, filepath)
            runas_list = [line for line in file(filepath).readlines()
                          if line.startswith(TestFromDir.runas_marker)]
            runas_list = runas_list or [None]
            runcount = 0
            for n, runas in enumerate(runas_list):
                if runas:
                    runas = runas.replace(TestFromDir.runas_marker, '')
                    runcount = runcount+1
                    suffix = "_run"+str(runcount)
                else:
                    suffix = '_norun'
                if stub:
                    func = lambda: None
                else:
                    func = TestFromDir.TestFunctor(target, name,
                        file(filepath).read(), runas=runas,
                        check_output=(runas is not None), **specs)

                setattr(target, "test_"+name+suffix+str(n), func)
