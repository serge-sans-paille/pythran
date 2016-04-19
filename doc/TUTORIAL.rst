Developer Tutorial
##################

This is a long tutorial to help new Pythran developer discover the Pythran
architecture. This is *not* a developer documentation, but it aims at giving a
good overview of Pythran capacity.

It requires you are comfortable with Python, and eventually with C++11. It also
assumes you have some compilation background, i.e. you know what an AST is and
you don't try to escape when hearing the words alias analysis, memory effect
computations and such.

Parsing Python Code
-------------------

Python ships a standard module, ``ast`` to turn Python code into an AST. For instance::

  >>> import ast
  >>> code = "a=1"
  >>> tree = ast.parse(code)  # turn the code into an AST
  >>> print ast.dump(tree)  # view it as a string
  Module(body=[Assign(targets=[Name(id='a', ctx=Store())], value=Num(n=1))])

Deciphering the above line, one learns that the single assignment is parsed as
a module containing a single statement, which is an assignment to a single
target, a ``ast.Name`` with the identifier ``a``, of the literal value ``1``.

Eventually, one needs to parse more complex codes, and things get a bit more cryptic, but you get the idea::

  >>> fib_src = """
  ... def fib(n):
  ...     return n if n< 2 else fib(n-1) + fib(n-2)"""
  >>> tree = ast.parse(fib_src)
  >>> print ast.dump(tree)
  Module(body=[FunctionDef(name='fib', args=arguments(args=[Name(id='n', ctx=Param())], vararg=None, kwarg=None, defaults=[]), body=[Return(value=IfExp(test=Compare(left=Name(id='n', ctx=Load()), ops=[Lt()], comparators=[Num(n=2)]), body=Name(id='n', ctx=Load()), orelse=BinOp(left=Call(func=Name(id='fib', ctx=Load()), args=[BinOp(left=Name(id='n', ctx=Load()), op=Sub(), right=Num(n=1))], keywords=[], starargs=None, kwargs=None), op=Add(), right=Call(func=Name(id='fib', ctx=Load()), args=[BinOp(left=Name(id='n', ctx=Load()), op=Sub(), right=Num(n=2))], keywords=[], starargs=None, kwargs=None))))], decorator_list=[])])

The idea remains the same. The whole Python syntax is described in
http://docs.python.org/2/library/ast.html and is worth a glance, otherwise
you'll be in serious trouble understanding the following.

Pythran Pass Manager
--------------------

A pass is a code transformation, i.e. a function that turns an AST node into a
new AST node with refined behavior. As a compiler infrastructure, Pythran
proposes a pass manager that (guess what?) manages pass scheduling, that is
the order in which pass is applied to achieve the ultimate goal, world
domination. Oooops, efficient C++11 code generation.

One first need to instantiate a pass manager with a module name::

  >>> from pythran import passmanager
  >>> pm = passmanager.PassManager("tutorial_module")

The pass manager has 3 methods and an attribute::

  >>> [x for x in dir(pm) if not x.startswith('_')]
  ['apply', 'dump', 'gather', 'module_name']

``apply``
    applies a code transformation

``dump``
    dumps a node using a dedicated backend

``gather``
    gathers information about the node

Pythran Backends
----------------

Pythran currently has two backends. The main one is used to dump Pythran AST (a
subset of Python AST) into a C++ AST::

  >>> from pythran import backend
  >>> cxx = pm.dump(backend.Cxx, tree)
  >>> str(cxx)
  '#include <pythonic/include/__builtin__/bool_.hpp>\n#include <pythonic/__builtin__/bool_.hpp>\nnamespace __pythran_tutorial_module\n{\n  ;\n  struct fib\n  {\n    typedef void callable;\n    typedef void pure;\n    template <typename argument_type0 >\n    struct type\n    {\n      typedef typename pythonic::returnable<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>::type result_type;\n    }  \n    ;\n    template <typename argument_type0 >\n    typename type<argument_type0>::result_type operator()(argument_type0 const & n) const\n    ;\n  }  ;\n  template <typename argument_type0 >\n  typename fib::type<argument_type0>::result_type fib::operator()(argument_type0 const & n) const\n  {\n    return (pythonic::__builtin__::functor::bool_{}((n < 2L)) ? n : (fib()((n - 1L)) + fib()((n - 2L))));\n  }\n}'

The above string is understandable by a C++11 compiler, but it quickly reaches the limit of our developer brain, so most of the time, we are more comfortable with the Python backend::

  >>> py = pm.dump(backend.Python, tree)
  >>> print py
  def fib(n):
      return (n if (n < 2) else (fib((n - 1)) + fib((n - 2))))

Passes
------

There are many code transformations in Pythran. Some of them are used to lower
the representation from Python AST to the simpler Pythran AST. For instance
there is no tuple unpacking in Pythran, so Pythran provides an adequate
transformation::

  >>> from pythran import transformations
  >>> tree = ast.parse("def foo(): a,b = 1,3.5")
  >>> _ = pm.apply(transformations.NormalizeTuples, tree)  # in-place
  >>> print pm.dump(backend.Python, tree)
  def foo():
      __tuple0 = (1, 3.5)
      a = __tuple0[0]
      b = __tuple0[1]

Note that Pythran wraps the sequence of assignment into a dummy if condition.
This ensures that a single instruction from the input code maps to a single
instruction in the generated code. This property is enforced everywhere in
Pythran and is used to maintain OpenMP directive semantic without deeply
understanding it.

There are many small passes used iteratively to produce the Pythran AST. For instance the implicit return at the end of every function is made explicit::

  >>> tree = ast.parse('def foo():pass')
  >>> _ = pm.apply(transformations.NormalizeReturn, tree)
  >>> print pm.dump(backend.Python, tree)
  def foo():
      pass
      return __builtin__.None

There are many other passes in Pythran. For instance one can prevent clashes with C++ keywords::

  >>> tree = ast.parse('namespace_ = new = 1\nnamespace = namespace_ + new')
  >>> _ = pm.apply(transformations.NormalizeIdentifiers, tree)  # out is a renaming table
  >>> print pm.dump(backend.Python, tree)
  namespace_ = new_ = 1
  namespace__ = (namespace_ + new_)

More complex ones rely on introspection to implement constant folding::

  >>> code = [fib_src, 'def foo(): print __builtin__.map(fib, [1,2,3])']
  >>> fib_call = '\n'.join(code)
  >>> tree = ast.parse(fib_call)
  >>> from pythran import optimizations as optim
  >>> _ = pm.apply(optim.ConstantFolding, tree)
  >>> print pm.dump(backend.Python, tree)
  def fib(n):
      return (n if (n < 2) else (fib((n - 1)) + fib((n - 2))))
  def foo():
      print [1, 1, 2]

One can also detect some common generator expression patterns to call the itertool module::

  >>> norm = 'def norm(l): return sum(n*n for n in l)'
  >>> tree = ast.parse(norm)
  >>> _ = pm.apply(optim.GenExpToImap, tree)
  >>> print pm.dump(backend.Python, tree)
  import itertools
  def norm(l):
      return sum(itertools.imap((lambda n: (n * n)), l))


Analysis
--------

All Pythran passes are backed up by analysis. Pythran provides three levels of analysis::

  >>> passmanager.FunctionAnalysis
  <class 'pythran.passmanager.FunctionAnalysis'>
  >>> passmanager.ModuleAnalysis
  <class 'pythran.passmanager.ModuleAnalysis'>
  >>> passmanager.NodeAnalysis
  <class 'pythran.passmanager.NodeAnalysis'>

Lets examine the information Pythran can extract from a Pythran-compatible
Python code.

A simple analyse gathers informations concerning used identifiers across the
module. It can be used, for instance, to generate new unique identifiers::

  >>> from pythran import analyses
  >>> code = 'a = b = 1'
  >>> tree = ast.parse(code)
  >>> pm.gather(analyses.Identifiers, tree)
  set(['a', 'b'])

One can also computes the state of ``globals()``::

  >>> code = 'import math\n'
  >>> code += 'def foo(a): b = math.cos(a) ; return [b] * 3'
  >>> tree = ast.parse(code)
  >>> pm.gather(analyses.Globals, tree)
  set(['foo', '__dispatch__', '__builtin__', 'math'])

One can also compute the state of ``locals()`` at any point of the program::

  >>> l = pm.gather(analyses.Locals, tree)
  >>> fdef = tree.body[-1]
  >>> freturn = fdef.body[-1]
  >>> l[freturn]
  set(['a', 'b', 'math'])

The ``ConstantFolding`` pass relies on the eponymous analyse that flags all
constant expressions. In the previous code, there is only two constant
*expressions* but only one can be evaluate::

  >>> ce = pm.gather(analyses.ConstantExpressions, tree)
  >>> sorted(map(ast.dump, ce))
  ["Attribute(value=Name(id='math', ctx=Load()), attr='cos', ctx=Load())", 'Num(n=3)']

One of the most critical analyse of Pythran is the points-to analysis. There
are two flavors of this analyse, one that computes an over-set of the aliased
variable, and one that computes an under set. ``Aliases`` computes an over-set::

  >>> code = 'def foo(c, d): b= c or d ; return b'
  >>> tree = ast.parse(code)
  >>> al = pm.gather(analyses.Aliases, tree)
  >>> returned = tree.body[-1].body[-1].value
  >>> print ast.dump(returned)
  Name(id='b', ctx=Load())
  >>> sorted(a.id for a in al[returned])
  ['c', 'd']

Pythran also implements an inter-procedural analyse to compute which arguments
are updated, for instance using an augmented assign, or the ``append`` method::

  >>> code = 'def foo(l,a): l+=[a]\ndef bar(g): foo(g, 1)'
  >>> tree = ast.parse(code)
  >>> ae = pm.gather(analyses.ArgumentEffects, tree)
  >>> foo, bar = tree.body[0], tree.body[1]
  >>> ae[foo]
  [True, False]
  >>> ae[bar]
  [True]

From this analyse and the ``GlobalEffects`` analyse, one can compute the set of
pure functions, i.e. functions that have no side effects::

  >>> code = 'def foo():pass\ndef bar(l): print l'
  >>> tree = ast.parse(code)
  >>> pf = pm.gather(analyses.PureExpressions, tree)
  >>> foo = tree.body[0]
  >>> bar = tree.body[1]
  >>> foo in pf
  True
  >>> bar in pf
  False

Pure functions are also interesting in the context of ``map``, as the
application of a pure functions using a map results in a parallel ``map``::

  >>> code = 'def foo(x): return x*x\n'
  >>> code += '__builtin__.map(foo, __builtin__.range(100))'
  >>> tree = ast.parse(code)
  >>> pmaps = pm.gather(analyses.ParallelMaps, tree)
  >>> len(pmaps)
  1
