from pythran import cxx_generator, ToolChain
from imp import load_dynamic
import unittest
import os
from numpy import ndarray, array
from numpy import any as npany


class TestEnv(unittest.TestCase):
    """
    Test environment to validate a pythran execution against python
    """

    # default options used for the c++ compiler
    PYTHRAN_CXX_FLAGS = ["-O0", "-fno-implicit-inline-templates", "-fopenmp",
                         '-Wall', '-Wno-unknown-pragmas']

    def assertAlmostEqual(self, ref, res):
        if hasattr(ref, '__iter__'):
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
            # Element-wise comparison because with numpy array... FIXME (Pierrick)
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
                             Special keys are 'module_name', 'prelude', and
                             'check_output'.

        Returns: nothing.

        Raises:
           AssertionError by 'unittest' if return value differ.
           SyntaxError if code is not python valid.
           pythran.ToolChain.CompileError if generated code can't be compiled.
           ...possible others...
        """

        # Extract special keys from interface.
        module_name = interface.pop('module_name', None)
        prelude = interface.pop('prelude', None)
        check_output = interface.pop('check_output', True)

        for name in sorted(interface.keys()):
            # Build the python function call.
            modname = module_name or ("test_" + name)
            attributes = []
            for p in params:
                if isinstance(p, str):
                    attributes.append("'{0}'".format(p))
                elif isinstance(p, ndarray):
                    attributes.append("numpy.{0}".format(
                        repr(p).replace("\n", "")))
                else:
                    attributes.append(str(p))
            arglist = ",".join(attributes)
            function_call = "{0}({1})".format(name, arglist)

            # Compile the python module, python-way, 'env' contains the module
            # and allow to call functions.
            # This may be done once before the loop, but the context might
            # need to be reset.
            compiled_code = compile(code, "", "exec")
            env = {'__builtin__': __import__('__builtin__')}
            prelude and prelude()
            eval(compiled_code, env)

            python_ref = eval(function_call, env)  # Produce the reference

            # Compile the code using pythran
            cxx_code = cxx_generator(modname, code, interface)
            cxx_compiled = ToolChain.compile_module(cxx_code,
                                                    cxxflags=TestEnv.PYTHRAN_CXX_FLAGS)
            if not check_output:
                return

            try:
                prelude and prelude()
                pymod = load_dynamic(modname, cxx_compiled)

                # Produce the pythran result
                pythran_res = getattr(pymod, name)(*params)

                # Test Results
                self.compare_pythonpythran_results(python_ref, pythran_res)
            finally:
                os.remove(cxx_compiled)


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

    @classmethod
    def interface(cls, name=None, file=None):
        ''' Return Pythran specs. By default try '''
        default_value = {name: []}
        try:
            from pythran.spec import spec_parser
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
            self, test_env, module_name, module_code, check_output=False,
                **specs):
            self.test_env = test_env
            self.module_name = module_name
            self.module_code = module_code
            self.specs = specs
            self.check_output = check_output

        def __name__(self):
            return self.module_name

        def __call__(self):
            if "unittest.skip" in self.module_code:
                return self.test_env.skipTest("Marked as skipable")
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
            if stub:
                func = lambda: None
            else:
                func = TestFromDir.TestFunctor(
                    target, name, file(filepath).read(), **specs)
            setattr(target, "test_"+name, func)
