"""HandleImport transformation takes care of importing user-defined modules."""
from pythran.passmanager import Transformation
from pythran.tables import cxx_keywords, MODULES, pythran_ward
from pythran.syntax import PythranSyntaxError

import ast
import importlib
import inspect
import logging

logger = logging.getLogger('pythran')


def add_filename_field(node, filename):
    for descendant in ast.walk(node):
        descendant.filename = filename


def mangle_imported_function_name(module_name, func_name):
    """Mangling naming scheme for imported functions."""
    return pythran_ward + "imported__" + module_name + "_" + func_name


def is_builtin_function(func_name):
    """Test if a function is a builtin (like len(), map(), ...)."""
    return (func_name in MODULES["__builtin__"] or
            (func_name in cxx_keywords and
             func_name + "_" in MODULES["__builtin__"]))


def is_builtin_module_name(module_name):
    """Test if a module is a builtin module (numpy, math, ...)."""
    module_name = module_name.split(".")[0]
    return (module_name in MODULES or
            (module_name in cxx_keywords and module_name + "_" in MODULES))


def is_builtin_module(module):
    """Test if a module is a builtin module (numpy, math, ...)."""
    return is_builtin_module_name(module.name)


def filter_builtinIn_import(import_node):
    """Filter out import list to keep only builtin modules."""
    import_node.names = filter(is_builtin_module, import_node.names)
    # Remove the import statement if no builtin module were present.
    return import_node if import_node.names else None


class ImportFunction(ast.NodeTransformer):

    """
    AST transformer that operates on a function that we need to import.

    It visits each call inside the function and recursively import the
    callees. The call site is modified to call the new imported function,
    using name mangling.
    """

    def __init__(self, registry, module, func_name):
        self.registry = registry
        self.module = module
        self.func_name = func_name
        self.nested_functions = dict()

    def visit_FunctionDef(self, func_node):
        """Keep track of nested Function."""
        self.nested_functions[func_node.name] = func_node
        self.generic_visit(func_node)
        return func_node

    def visit_Import(self, import_node):
        """
        Track local import.

        This is "wrong" because we add these import like if they were global.
        """
        for alias in import_node.names:
            asname = alias.asname or alias.name
            self.module.imported_modules[asname] = alias.name
        return filter_builtinIn_import(import_node)

    def visit_ImportFrom(self, importfrom_node):
        """
        Track local import.

        This is "wrong" because we add these import like if they were global.
        """
        module_name = importfrom_node.module
        for alias in importfrom_node.names:
            func_name = alias.name
            asname = alias.asname or func_name
            self.module.imported_functions[asname] = (module_name,
                                                      func_name,
                                                      None)
        if is_builtin_module_name(module_name):
            return importfrom_node

    def visit_Call(self, call_node):
        """Find any non-builtin and non-nested function call to pull the callee
        as part of the import.
        """
        self.generic_visit(call_node)
        if isinstance(call_node.func, ast.Name):
            # Direct call, resolve in the current module.
            # Note: the function is not necessarily locally defined, it could
            # be imported in the form "from bar import foo"
            func_name = call_node.func.id
            if func_name in self.nested_functions:
                # Don't need to do anything in this case, nested function are
                # implicitly imported with the current function
                return call_node

            # Import the function now, imply a recursion to import the callee
            mangled_name = self.module.call_function(self.registry,
                                                     func_name)
            # Patch the call site, replacing with the mangle name
            call_node.func.id = mangled_name
        elif (isinstance(call_node.func, ast.Attribute) and
              isinstance(call_node.func.value, ast.Name)):
            # This is a call in the form of something.function()
            module_alias = call_node.func.value.id
            func_name = call_node.func.attr
            if module_alias not in self.module.imported_modules:
                # This might be an import error, but it can also be that
                # "something" in something.function() is not a module, for
                # instance: list.append(...)
                return call_node

            module_name = self.module.imported_modules[module_alias]
            module = self.registry.import_module(module_name)
            # In case it a builtin module, add import with the correct alias
            if isinstance(module, BuiltinModule):
                self.module.dependent_modules[module_alias] = module_name
            # Import the function from the module now, triggers a recursion
            mangled_name = module.import_function(self.registry, func_name)

            if mangled_name is None:
                return call_node
            # Patch witch mangled name, force it for the main module as we want
            # to tranform calls from main_module.foo() to simply foo()
            if module.to_be_mangled or module.is_main_module:
                # Patch the call, replace with the mangle name
                call_node.func = ast.Name(id=mangled_name, ctx=ast.Load())

        return call_node


class ImportedModule(object):

    """
    Represent a user-defined imported module.

    It offer an interface to import a function from this module, handling
    automatically the import of all callees in the function.
    """

    def __init__(self, name, module=None):
        """Parameters are the name for the module (mandatory), and the
        ast.Module node (optional) in the case the current module is the main
        one. This differentiation is needed to avoid mangling function name for
        functions defined in the main module.
        """
        self.is_main_module = True
        self.node = module
        if self.node is None:
            # Not main module, parse now the imported module
            self.is_main_module = False
            imported_module = importlib.import_module(name)
            self.node = ast.parse(inspect.getsource(imported_module))
            assert isinstance(self.node, ast.Module)

        # Recursively add filename information to all nodes, for debug msg
        add_filename_field(self.node, name + ".py")

        # Mangle function imported, unless it is the main module
        self.to_be_mangled = not self.is_main_module
        self.name = name
        # Functions defined in this module and imported by another one.
        # This dict is used at the end of the process to gather functions to be
        # prepend at the beginning of the main pythran module
        self.exported_functions = dict()
        self.dependent_modules = dict()
        # Top-level function declared in this module
        self.functions = dict()
        # Functions imported as "from somemodule import func as func_alias"
        self.imported_functions = dict()
        # Regular module import. Keys are alias and values are module names
        self.imported_modules = dict()

        # Collect top-level functions and imports
        for decl in self.node.body:
            if isinstance(decl, ast.FunctionDef):  # regular functions
                self.functions[decl.name] = decl
            elif isinstance(decl, ast.Import):  # Module import
                for alias in decl.names:
                    asname = alias.asname or alias.name
                    self.imported_modules[asname] = alias.name
            elif isinstance(decl, ast.ImportFrom):  # Function import
                module_name = decl.module
                for alias in decl.names:
                    func_name = alias.name
                    asname = alias.asname or func_name
                    self.imported_functions[asname] = (module_name, func_name,
                                                       None)
            elif isinstance(decl, ast.Assign):
                # FIXME : We ignore import of globals
                pass
            else:
                raise PythranSyntaxError('Unpythranizable module: %s' % name)

    def call_function(self, registry, func_name):
        """Direct function call from another function of the current module,
        try to find if it was imported from another module in the form of
        "from module_name import foo", if it was not it has to be locally
        defined.
        Return the mangled name to be used at call site.
        """
        if func_name in self.imported_functions:
            module_name, realName, decl = self.imported_functions[func_name]
            if not decl:  # first time we call this function, import it.
                decl = registry.import_module(module_name). \
                    call_function(registry, realName)
                # Cache the fact that it has been imported now
                self.imported_functions[func_name] = (module_name, realName,
                                                      decl)
            if not registry.import_module(module_name).to_be_mangled:
                # No mangling in the main module, nor in builtins
                return realName
            return mangle_imported_function_name(module_name, realName)

        # Function not imported, hopefully it was locally defined, delegate!
        return self.import_function(registry, func_name) or func_name

    def import_function(self, registry, func_name):
        """
        Called to import a function locally defined in this module.

        Return the mangled name to be used at call site.
        """
        if func_name in self.exported_functions:  # Caching: already registered
            return self.exported_functions[func_name].name

        # Function is not defined locally, maybe it is an alias, like
        # c = math.cos
        # c()
        # Just give up here and hope for the best!
        if func_name not in self.functions:
            return None

        func = self.functions[func_name]

        # Mangle function's name here so that module1.foo() and
        # module2.foo() don't conflict
        if self.to_be_mangled:
            # No mangling in the main module
            func.name = mangle_imported_function_name(self.name, func_name)
        # Cache the processed function
        self.exported_functions[func_name] = func

        # Recursively visit the function to handle any callees
        ImportFunction(registry, self, func.name).visit(func)

        return func.name


class BuiltinModule(object):

    """
    Represent a builtin module.

    it offer the same interface as ImportedModule class, but do not try to
    validate function imported from here.
    """

    def __init__(self, name):
        self.name = name
        self.is_main_module = False
        self.to_be_mangled = False
        # For builtins module, exported_functions is only used to keep
        # ImportFrom nodes, see call_function()
        self.exported_functions = dict()
        self.dependent_modules = dict()

    def call_function(self, _, func_name):
        # There was a direct call to a function from this builtin. It means it
        # was imported in the caller module in the form: from builtin import
        # foo. We need to add such node to be imported
        importFrom = ast.ImportFrom(module=self.name,
                                    names=[ast.alias(name=func_name,
                                                     asname=None)],
                                    level=0)  # FIXME what is level?
        self.exported_functions[func_name] = importFrom
        return func_name

    def import_function(self, _, func_name):
        # We could check if the function is supported by Pythran here...
        return func_name


class ImportRegistry(object):

    """
    Keep track of already imported modules.

    It avoid duplication in case of diamond or reflective import. It keeps a
    single ImportedModule() instance per module. Import has to use the
    canonical name (not the aliased one).
    """

    def __init__(self):
        self.modules = dict()  # List of modules already imported

    def import_module(self, name):
        """Keep track of imported modules. Pythran-supported builtin modules
        are handled using a dummy BuiltinModule() type, while user-defined
        modules rely on ImportedModule() to provide an interface to import
        function at call site
        """
        if name in self.modules:  # Caching
            return self.modules[name]

        if is_builtin_module_name(name):
            mod = BuiltinModule(name)
        else:
            mod = ImportedModule(name)

        self.modules[name] = mod
        return mod

    def generate_ImportList(self):
        """List of imported functions to be added to the main module.  """
        import_list = []
        for mod in self.modules.values():
            if mod.is_main_module:
                # don't need to import anything from the main module
                continue
            for alias, module_name in mod.dependent_modules.items():
                import_node = ast.Import(names=[ast.alias(name=module_name,
                                                          asname=alias)])
                import_list.append(import_node)
            # Here we import the function itself (FunctionDef node)
            # In case of builtin module, it is an ImportFrom node.
            import_list += mod.exported_functions.values()
        return import_list


class HandleImport(Transformation):

    """This pass handle user-defined import, mangling name for function from
    other modules and include them in the current module, patching all call
    site accordingly.
    """

    def __init__(self):
        super(HandleImport, self).__init__()
        self.registry = ImportRegistry()

    def visit_Module(self, module):
        """Entry point for the module."""
        # Do not use registry.import_module because this is the main module and
        # ImportedModule takes an extra parameter in this case
        self.module = ImportedModule(self.passmanager.module_name, module)
        self.registry.modules[self.passmanager.module_name] = self.module
        self.generic_visit(module)

        # Patch module body: prepend all imported function and import nodes
        imported = self.registry.generate_ImportList()
        imported_modules = self.module.imported_modules.items()
        external_modules_name = [alias for alias, name in imported_modules
                                 if not is_builtin_module_name(name)]
        if not imported and external_modules_name:
            # We can't raise an exception as it may just be an unused import.
            # FIXME : To improve this, we have to handle aliasing so that we
            # can know sys.stdout is not an attribute of class but a function
            # call from a module even when the function is not defined (.so
            # file for example)
            logger.warn("Module : '" + "', '".join(external_modules_name) +
                        "' is imported but not used or can't be imported by "
                        "Pythran.")
        module.body = imported + module.body
        self.update |= bool(imported)
        return module

    @staticmethod
    def visit_Import(import_node):
        """Filter out import node to keep only builtin modules."""
        return filter_builtinIn_import(import_node)

    @staticmethod
    def visit_ImportFrom(import_node):
        """Filter out import node to keep only builtin modules."""
        module_name = import_node.module
        if is_builtin_module_name(module_name):
            return import_node

    def visit_FunctionDef(self, func):
        """Trigger dependent import for this function's body."""
        self.module.call_function(self.registry, func.name)
        return func
