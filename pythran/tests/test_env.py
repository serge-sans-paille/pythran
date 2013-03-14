from pythran import cxx_generator
from pythran import compile as pythran_compile
from imp import load_dynamic
import unittest
import os


class TestEnv(unittest.TestCase):
    """
    Test environment to validate a pythran execution against python
    """

    # default options used for the c++ compiler
    PYTHRAN_CXX_FLAGS = ["-O0", "-fno-implicit-inline-templates", "-fopenmp"]

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

    def run_test_with_prelude(self, code, prelude, *params, **interface):
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

        Returns: nothing.

        Raises:
           AssertionError by 'unittest' if return value differ.
           SyntaxError if code is not python valid.
           CalledProcessError if pythran generated code cannot be compiled.
           ...possible others...
        """
        for name in sorted(interface.keys()):

            # Build the python function call.
            modname = "test_" + name
            arglist = ",".join(("'{0}'".format(p) if isinstance(p, str)
                              else str(p)) for p in params)
            function_call = "{0}({1})".format(name, arglist)

            # Compile the python module, python-way, 'env' contains the module
            # and allow to call functions.
            # This may be done once before the loop, but the context might
            # need to be reset.
            compiled_code = compile(code, "", "exec")
            env = {'__builtin__' : __import__('__builtin__')}
            prelude and prelude()
            eval(compiled_code, env)

            python_ref = eval(function_call, env)  # Produce the reference

            # Compile the code using pythran
            cxx_code = cxx_generator(modname, code, interface)
            cxx_compiled = pythran_compile(os.environ.get("CXX", "c++"),
                                           cxx_code,
                                           cxxflags=TestEnv.PYTHRAN_CXX_FLAGS,
                                           check=False)
            prelude and prelude()
            pymod = load_dynamic(modname, cxx_compiled)

            # Produce the pythran result
            pythran_res = getattr(pymod, name)(*params)

            # Compare pythran result against python ref and raise if mismatch
            if python_ref != pythran_res:
                print "Python result: ", python_ref
                print "Pythran result: ", pythran_res
                self.assertAlmostEqual(python_ref, pythran_res)
    def run_test(self, code, *params, **interface):
        return self.run_test_with_prelude(code, None, *params, **interface)

