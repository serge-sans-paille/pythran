from pythran import cxx_generator
from pythran import compile as pythran_compile
from imp import load_dynamic
import unittest
import os


class TestEnv(unittest.TestCase):
    """
    
    Test environment to validate a pythran execution against python
    
    """

    PYTHRAN_CXX_FLAGS = ["-O0", "-fno-implicit-inline-templates", "-fopenmp"]
    """The default options used for the c++ compiler"""

    def assertAlmostEqual(self, ref, res):
        if hasattr(ref, '__iter__'):
            self.assertEqual(len(ref), len(res))
            for iref, ires in zip(ref, res):
                self.assertAlmostEqual(iref, ires)
        else:
            unittest.TestCase.assertAlmostEqual(self, ref, res)

    def run_test(self, code, *params, **interface):
        """Test if a function call return value is unchanged when
        executed using python eval or compiled with pythran.

        Args:
           code (str):  python (pythran valid) module to test.
           params (tuple): arguments to pass to the function to test.
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
            env = {}
            eval(compiled_code, env)

            python_ref = eval(function_call, env)  # Produce the reference

            # Compile the code using pythran
            cxx_code = cxx_generator(modname, code, interface)
            cxx_compiled = pythran_compile(os.environ.get("CXX", "c++"),
                                           cxx_code,
                                           cxxflags=TestEnv.PYTHRAN_CXX_FLAGS,
                                           check=False)
            pymod = load_dynamic(modname, cxx_compiled)

            # Produce the pythran result
            pythran_res = getattr(pymod, name)(*params)

            # Compare pythran result against python ref and raise if mismatch
            if python_ref != pythran_res:
                print python_ref, pythran_res
                self.assertAlmostEqual(python_ref, pythran_res)
