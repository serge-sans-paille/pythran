'''
This module provides a way to JIT compile functions, based on runtime types.

'''
import ast
import inspect
import pythran
import os
import imp
import hashlib
import logging
logger = logging.getLogger(__name__)

from pythran.config import cfg
from pythran.typing import pytype_to_ctype
import pythran.toolchain as toolchain

# Initialize destination directory, system temp by default
try:
    dest_dir = cfg.get('user', 'jit_dir')
except:
    import tempfile
    dest_dir = tempfile.gettempdir()

# Initialize hash function, md5 by default
try:
    hash_func = hashlib.__dict__[cfg.get('user', 'jit_hash_func')]
except:
    hash_func = hashlib.md5


class Stats:
    def __init__(self):
        self.called = 0
        self.overloads = 0
        self.loaded_from_disk = 0
        self.compiled = 0

    def __str__(self):
        return ("Called {0} times, loaded {1} overloads, {2} were loaded from "
                "disk and {3} were JIT-compiled".format(self.called,
                                                        self.loaded_from_disk +
                                                        self.compiled,
                                                        self.loaded_from_disk,
                                                        self.compiled))

    def __repr__(self):
        return self.__str__()


class jit(object):
    ''' This class is intended to be instanciated as a decorator, for example:

    @pythran.jit
    def foobar(myarg1,myarg2):
       ....

    It is instanciated once when the function is parsed. At that time Pythran
    will be invoked to generate the C++ file for the function, independently of
    the argument types. Later, at call time, the argument types are used to
    specialized the templated C++ and compile a ".so". A unique signature
    combining the function indepent C++ and the argument type is used for the
    ".so" filename. It can then be reused accross different runs and save
    useless recompilation.

    Calling a jitted function involves:

    1) listing argument types
    2) hashing a string representing the argument types
    3) retrieving the overload for the function in a dict using the hash
    4) if not found in the dict, then imp.load_dynamic(...) is tried
    5) if not found on disk (ImportError exception), then the C++ is
       specialized for this overload and the C++ compiler is involved

    Keep in mind that there is an overhead for a simple "Passthrough" function,
    I can time 1000 native python calls to a dummy function to take 0.1ms while
    the same 1000 calls to the jitted version takes 7.7ms.

    Take care that the decorator must be the last one attached to a given
    function since it will recover the source code of the fonction attached to.
    This will NOT work:

    @pythran.jit
    @another_decorator
    def foobar(myarg1,myarg2):
       ....

    The JIT can be traced by activating the logging in the client code, i.e.

    import logging
    logging.basicConfig(format='%(levelname)s %(name)s: %(message)s',
                        level=logging.DEBUG)

    Stats are kept and can be displayed at any time:

    @pythran.jit
    def foobar(myarg1,myarg2):
       ....

    # after a few calls...
    print foobar.stats
    # displays :
    # Called 15 times, loaded 5 overloads, 2 were loaded from disk and 3 were
    # JIT-compiled

    A Current limitation is that it does not allow any call to user defined
    function in the "jitted" function

    '''

    ''' Fake module name used to generate and load the .so jitted module.'''
    modName = "jitted"

    def hash(self, value):
        '''Helper function, return hash for a value'''
        return hash_func(value).hexdigest()

    def __init__(self, func):
        '''Attach a JIT to a function'''
        self.func = func
        self.func_name = func.func_name

        # Retrieve the python source for the function
        src = os.linesep.join([l for l in inspect.getsource(func).splitlines()
                               if not l.strip().startswith("@")])

        # Get the generic C++ code for the function
        (self.cxx,
         self.renamings,
         self.ir) = toolchain.generate_generic_cxx(self.modName,
                                                   src)

        # Hash the C++ code, get a unique hash for this function
        self.func_hashed = self.hash(self.cxx.generate())

        # Map "my_file.so" to a loaded module, avoid trying to reload from disk
        self.loaded = dict()

        # Statistic
        self.stats = Stats()

        logger.debug("JIT Initialized for func '{0}',"
                     "hash is {1}, cache dir is '{2}'".format(self.func_name,
                                                              self.func_hashed,
                                                              dest_dir))

    def __call__(self, *args):
        '''Call the function, it will be jitted if not already done'''
        # Get a signature for the arguments types
        args_sig = "".join([pytype_to_ctype(type(i)) for i in args])
        try:
            pass
            # maybe already loaded?
            mod = self.loaded[args_sig]
        except KeyError:
            try:
                # DLL file
                module_so = "_".join([self.func_hashed,
                                      self.hash(args_sig)])+".so"
                # It seems it is not, try to load it from disk
                logger.debug("Loading from '{0}'".format(module_so))
                path = os.path.join(dest_dir, module_so)
                mod = imp.load_dynamic(self.modName, path)
                # Keep stats
                self.stats.loaded_from_disk += 1
                logger.debug("JIT call '{0}' "
                             "reloaded from disk ({1})".format(self.func_name,
                                                               path))
            except ImportError:
                # No luck, has to take the very slow path of compiling...
                logger.debug("JIT call '{0}' "
                             "has to be compiled ({1})".format(self.func_name,
                                                               path))
                args_type = [type(i) for i in args]
                mod = self.compile(args_type, module_so)

            # Save for reuse
            self.loaded[args_sig] = mod

        # Keep stats FIXME cost!
        self.stats.called += 1

        # Forward the call now
        jitted_func = mod.__dict__[self.func_name]
        return jitted_func(*args)

    def compile(self, args_type, module_so):
        '''Compile function for args_type spec and store into module_so.'''
        # Pythran spec
        specs = {self.func_name: args_type}
        # Generate the specialized C++
        cxx = toolchain.specialize_cxx_with_specs(self.modName,
                                                  self.cxx.content,
                                                  specs,
                                                  self.renamings,
                                                  self.ir)
        # Compile the C++ code to module_so (may throw...)
        path = os.path.join(dest_dir, module_so)
        toolchain.compile_cxxcode(cxx, module_so=path)
        # Load the generated module
        mod = imp.load_dynamic(self.modName, path)
        # Stats
        self.stats.compiled += 1
        return mod

    def clear_cache(self):
        '''Delete all generated .so for this function'''
        import glob
        modules_so = "{0}_*.so".format(self.func_hashed)
        for filename in glob.glob(os.path.join(dest_dir, modules_so)):
            os.remove(filename)

    def __str__(self):
        return ("Pythran JIT instance for function "
                "{0}: {1}".format(str(self.func_name) + self.stats))

    def __repr__(self):
        return self.__str__()
