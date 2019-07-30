Internals
#########

This document describes some internals of Pythran compiler.

Pythran pass management is used throughout the document::

    >>> from pythran import passmanager, analyses, optimizations, backend
    >>> pm = passmanager.PassManager('dummy')

To retrieve the code source from a function definition, the ``inspect`` module
is used::

    >>> from inspect import getsource

And to turn source code into an AST(Abstract Syntax tree), Python provides the
``ast`` module::

    >>> import gast as ast
    >>> getast = lambda f: ast.parse(getsource(f))

Scoping
-------

There are only two scopes in Python: ``globals()`` and ``locals()``. When
generating C++ code, Pythran tries its best not to declare variables at the
function level, but using the deepest scope. This provides two benefits:

1. It makes writing OpenMP clauses easier, as local variables are automatically
   marked as private;
2. It avoids to build variables with the empty constructor then assigning them a
   value.

Let's illustrate this with two simple examples. In the following function,
variable ``a`` has to be declared outside of the ``if`` statement::

    >>> def foo(n):
    ...     if n:
    ...         a = 1
    ...     else:
    ...         a = 2
    ...     return n*a

When computing variable scope, one gets a dictionary binding nodes to variable names::

    >>> foo_tree = getast(foo)
    >>> scopes = pm.gather(analyses.Scope, foo_tree)

``n`` is a formal parameter, so it has function scope::

    >>> scopes[foo_tree.body[0]] == set(['a', 'n'])
    True


``a`` is used at the function scope (in the ``return`` statement), so even if
it's declared in an ``if`` it has function scope too.

Now let's see what happen if we add a loop to the function::

    >>> def foo(n):
    ...     s = 0
    ...     for i in __builtin__.range(n):
    ...         if i:
    ...             a = 1
    ...         else:
    ...             a = 2
    ...         s *= a
    ...     return s
    >>> foo_tree = getast(foo)
    >>> scopes = pm.gather(analyses.Scope, foo_tree)

Variable ``a`` is only used in the loop body, so one can declare it inside the
loop::

    >>> scopes[foo_tree.body[0].body[1]] == set(['i', 'a'])
    True

In a similar manner, the iteration variable ``i`` gets a new value at each
iteration step, and is declared at the loop level.

OpenMP directives interacts a lot with scoping. In C or C++, variables declared
inside a parallel region are automatically marked as private. Pythran emulates
this whenever possible::

    >>> def foo(n):
    ...     s = 0
    ...     "omp parallel for reduction(*:s)"
    ...     for i in __builtin__.range(n):
    ...         if i:
    ...             a = 1
    ...         else:
    ...             a = 2
    ...         s += a
    ...     return s

Without scoping directive, both ``i`` and ``a`` are private::

    >>> foo_tree = getast(foo)
    >>> scopes = pm.gather(analyses.Scope, foo_tree)
    >>> scopes[foo_tree.body[0].body[2]] == set(['i', 'a'])  # 3rd element: omp is not parsed
    True

But if one adds a
``lastprivate`` clause, as in::

    >>> def foo(n):
    ...     s = 0
    ...     a = 0
    ...     "omp parallel for reduction(*:s) lastprivate(a)"
    ...     for i in __builtin__.range(n):
    ...         if i:
    ...             a = 1
    ...         else:
    ...             a = 2
    ...         s += a
    ...     return s, a
    >>> foo_tree = getast(foo)

The scope information change. Pythran first needs to understand OpenMP
directives, using a dedicated pass::

    >>> from pythran import openmp
    >>> _ = pm.apply(openmp.GatherOMPData, foo_tree)

Then let's have a look to ::

    >>> scopes = pm.gather(analyses.Scope, foo_tree)
    >>> list(scopes[foo_tree.body[0].body[2]])  # 3nd element: omp got parsed
    ['i']
    >>> list(scopes[foo_tree.body[0]])
    ['n']
    >>> list(scopes[foo_tree.body[0].body[0]])
    ['s']
    >>> list(scopes[foo_tree.body[0].body[1]])
    ['a']

``a`` now has function body scope, which keeps the OpenMP directive legal.

When the scope can be attached to an assignment, Pythran uses this piece of information::

    >>> def foo(n):
    ...     s = 0
    ...     "omp parallel for reduction(*:s)"
    ...     for i in __builtin__.range(n):
    ...         a = 2
    ...         s *= a
    ...     return s
    >>> foo_tree = getast(foo)
    >>> _ = pm.apply(openmp.GatherOMPData, foo_tree)
    >>> scopes = pm.gather(analyses.Scope, foo_tree)
    >>> scopes[foo_tree.body[0].body[1].body[0]] == set(['a'])
    True

Additionally, some OpenMP directives, when applied to a single statement, are
treated by Pythran as if they created a bloc, emulated by a dummy
conditional::

    >>> def foo(n):
    ...     "omp parallel"
    ...     "omp single"
    ...     s = 1
    ...     return s
    >>> foo_tree = getast(foo)
    >>> _ = pm.apply(openmp.GatherOMPData, foo_tree)
    >>> print(pm.dump(backend.Python, foo_tree))
    def foo(n):
        'omp parallel'
        'omp single'
        if 1:
            s = 1
        return s

However the additional if bloc makes it clear that ``s`` should have function
scope, and the scope is not attached to the first assignment::

    >>> scopes = pm.gather(analyses.Scope, foo_tree)
    >>> scopes[foo_tree.body[0]] == set(['s'])
    True


Lazyness
--------

``Expressions templates`` used by numpy internal representation enable laziness
computation. It means that operations will be computed only during assignation
to avoid intermediate array allocation and improve data locality.
Laziness analysis enable Expression template even if there is multiple
assignment in some case.

Let's go for some examples.
In ``foo``, no intermediate array are create for ``+`` and ``*`` operations and
for each elements, two operations are apply at once instead of one by one::

    >>> def foo(array):
    ...     return array * 5 + 3

It also apply for other unary operations with numpy array.
In this example, laziness doesn't change anything as is it a typical case for
Expression templates but peoples may write::

    >>> def foo(array):
    ...     a = array * 5
    ...     return a + 3

Result is the same but there is a temporary array. This case is detected as
lazy and instead of saving the result of ``array * 5`` in ``a``, we save an
Expression template type ``numpy_expr<operator*, ndarray, int>`` instead of an
evaluated ``ndarray``.

Now, have a look at the lazyness analysis's result::

    >>> foo_tree = getast(foo)
    >>> lazyness = pm.gather(analyses.LazynessAnalysis, foo_tree)

``array`` is a parameter so even if we count use, it can't be lazy::

    >>> lazyness['a']
    1

It returns the number of use of a variable.

Special case is for intermediate use::

    >>> def foo(array):
    ...     a = array * 2
    ...     b = a + 2
    ...     a = array * 5
    ...     return a, b

In this case, ``b`` is only use once BUT ``b`` depend on ``a`` and ``a`` change
before the use of ``b``.
In this case, ``b`` can't be lazy so its values is ``inf``::

    >>> foo_tree = getast(foo)
    >>> lazyness = pm.gather(analyses.LazynessAnalysis, foo_tree)
    >>> sorted(lazyness.items())
    [('a', 1), ('array', 2), ('b', inf)]

We can notice that a reassignment reinitializes its value so even if ``a`` is
used twice, its counters returns ``1``.  ``inf`` also happen in case of
subscript use as we need to compute the value to subscript on it. Updated
values can't be lazy too and variables used in loops too. Laziness also cares
about aliased values::

    >>> def foo(array):
    ...     a = array * 2
    ...     b = a
    ...     a_ = b * 5
    ...     return a_
    >>> foo_tree = getast(foo)
    >>> lazyness = pm.gather(analyses.LazynessAnalysis, foo_tree)
    >>> sorted(lazyness.items())
    [('a', 1), ('a_', 1), ('array', 1), ('b', 1)]



Doc Strings
-----------

Pythran preserves docstrings::

    $> printf '#pythran export foo()\n\"top-level-docstring\"\n\ndef foo():\n  \"function-level-docstring\"\n  return 2' > docstrings.py
    $> pythran docstrings.py
    $> python -c 'import docstrings; print(docstrings.__doc__); print(docstrings.foo.__doc__)'
    top-level-docstring
    function-level-docstring
    <BLANKLINE>
        Supported prototypes:
    <BLANKLINE>
        - foo()
    $> rm -f docstrings.*

Integration with Scipy LowLevelCallable
---------------------------------------

Use Pythran exported capsule to interact with SciPy's ``LowLevelCallable``::

    $> printf '#pythran export capsule llc(float)\ndef llc(n):\n  return n + 1' > llc.py
    $> pythran llc.py
    $> python -c 'import llc; from scipy import LowLevelCallable, integrate; capsule = llc.llc; c = LowLevelCallable(capsule, signature=\"double (double)\"); print(integrate.quad(c, 0, 10))'
    (60.0, 6.661338147750939e-13)
    $> rm -f llc.*

When using a pointer type as argument, one can rely on ``numpy.ctypeslib.as_array``::

    $> printf '#pythran export capsule transform(intp*, float64*, int32, int32, float64*)\nfrom numpy.ctypeslib import as_array\ndef transform(output_coordinates, input_coordinates, output_rank, input_rank, user_data):\n  shift = user_data[0]\n  input_data = as_array(input_coordinates, input_rank)\n  output_data = as_array(output_coordinates, output_rank)\n  input_data[:] = output_data - shift\n  return 1' > llc2.py
    $> pythran llc2.py
    $> python -c 'import ctypes; import numpy as np; from scipy import ndimage, LowLevelCallable; from llc2 import transform; shift = 0.5; user_data = ctypes.c_double(shift); ptr = ctypes.cast(ctypes.pointer(user_data), ctypes.c_void_p); callback = LowLevelCallable(transform, ptr, \"int (npy_intp *, double *, int, int, void *)\"); im = np.arange(12).reshape(4, 3).astype(np.float64); print(int(np.sum(ndimage.geometric_transform(im, callback))))'
    33
    $> rm -f llc2.*

