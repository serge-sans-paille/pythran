=================
Pythran Internals
=================

This document describes some internals of Pythran compiler.

Pythran pass management is used throughout the document::

    >>> from pythran import passmanager, analysis, passes, optimizations, backend
    >>> pm = passmanager.PassManager('dummy')

To retrieve the code source from a function definition, the ``inspect`` module
is used::

    >>> from inspect import getsource

And to turn source code into an AST(Abstract Syntax tree), Python provides the
``ast`` module::

    >>> import ast
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
    >>> scopes = pm.gather(analysis.Scope, foo_tree)

``n`` is a formal parameter, so it has function scope::

    >>> scopes[foo_tree.body[0]]
    set(['a', 'n'])


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
    >>> scopes = pm.gather(analysis.Scope, foo_tree)

Variable ``a`` is only used in the loop body, so one can declare it inside the
loop::

    >>> scopes[foo_tree.body[0].body[1]]
    set(['i', 'a'])

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
    >>> scopes = pm.gather(analysis.Scope, foo_tree)
    >>> scopes[foo_tree.body[0].body[2]]  # 3rd element: omp is not parsed
    set(['i', 'a'])

But if one adds a
``lastprivate`` clause, as in::

    >>> def foo(n):
    ...     s = 0
    ...     "omp parallel for reduction(*:s) lastprivate(a)"
    ...     for i in __builtin__.range(n):
    ...         if i:
    ...             a = 1
    ...         else:
    ...             a = 2
    ...         s += a
    ...     return s
    >>> foo_tree = getast(foo)

The scope information change. Pythran first needs to understand OpenMP
directives, using a dedicated pass::

    >>> from pythran import openmp
    >>> _ = pm.apply(openmp.GatherOMPData, foo_tree)

Then let's have a look to ::

    >>> scopes = pm.gather(analysis.Scope, foo_tree)
    >>> scopes[foo_tree.body[0].body[1]] # 2nd element: omp got parsed
    set(['i'])
    >>> scopes[foo_tree.body[0]]
    set(['a', 's', 'n'])

``a`` now has function scope, which keeps the OpenMP directive legal.

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
    >>> scopes = pm.gather(analysis.Scope, foo_tree)
    >>> scopes[foo_tree.body[0].body[1].body[0]]
    set(['a'])

Additionnaly, some OpenMP directives, when applied to a single statement, are
treated by Pythran as if they created a bloc, emulated by a dummy
conditionnal::

    >>> def foo(n):
    ...     "omp parallel"
    ...     "omp single"
    ...     s = 1
    ...     return s
    >>> foo_tree = getast(foo)
    >>> _ = pm.apply(openmp.GatherOMPData, foo_tree)
    >>> print pm.dump(backend.Python, foo_tree)
    def foo(n):
        if 1:
            s = 1
        return s

Note that the OpenMP directives are not pretty-printed by the Python backend!
However the additionnal if bloc makes it clear that ``s`` should have function
scope, and the scope is not attached to the first assignment::

    >>> scopes = pm.gather(analysis.Scope, foo_tree)
    >>> scopes[foo_tree.body[0]]
    set(['s'])

Top level stmt support
----------------------

..  Small hack to setup the $PATH in a compatible way
..  >>> import os, pythran, re
..  >>> if 'lib' in pythran.__file__: os.environ['PATH'] = re.sub(r'(.*)/lib/.*', r'\1/bin:', pythran.__file__) + os.environ['PATH']
..  >>> os.environ['PATH'] = './scripts:' + os.environ['PATH']

Pythran supports top-level statements. For example, functions can be called::

    $> printf 'print 1\ndef foo():return 2\nprint 1+foo()' > internal_top_level_print.py
    $> pythran internal_top_level_print.py
    $> python -c 'import internal_top_level_print'
    1
    3

Expression statement can be written at top-level, the example below is just to
show that Pythran can compile it::

    $> printf '1 + (2 + 2) * 3' > internal_top_level_expr.py
    $> pythran internal_top_level_expr.py
    $> python -c 'import internal_top_level_expr'

Assignment and AugAssignment statements at top-level are one of the most common
cases of Python programs::

    $> printf 'a = 1 + (2 + 2) * 3\nprint a\na += 1\nprint a' > internal_top_level_assign.py
    $> pythran internal_top_level_assign.py
    $> python -c 'import internal_top_level_assign'
    13
    14

Then let's test Python's flow control keywords: for, while, if-else:

Loop statement at top-level::

    $> printf 's=0\nfor i in range(10):s+=i\nprint s' > internal_top_level_loop.py
    $> pythran internal_top_level_loop.py
    $> python -c 'import internal_top_level_loop'
    45

While statement at top-level::

    $> printf 'i=0\nwhile i<10:i+=1\nprint i' > internal_top_level_while.py
    $> pythran internal_top_level_while.py
    $> python -c 'import internal_top_level_while'
    10

If-else statement at top-level::

    $> printf 'if True: print 1\nelse:pass' > internal_top_level_ifelse.py
    $> pythran internal_top_level_ifelse.py
    $> python -c 'import internal_top_level_ifelse'
    1

Raise an exception and catch an exception written at top-level can also be
compiled:

Raise an exception ::

    $> printf 'raise Exception()'> internal_top_level_exception.py
    $> pythran internal_top_level_exception.py
    $> python -c 'try:import internal_top_level_exception\nexcept:print 111'
    111

Try-except statement::

    $> printf 'try:raise Exception()\nexcept: print 222'> internal_top_level_exception_tryexcept.py
    $> pythran internal_top_level_exception_tryexcept.py
    $> python -c 'import internal_top_level_exception_tryexcept'
    222

In a word, Pythran supports most kind of Python statements at top-level.

Before leaving, let's clear these examples and you can try out your own
programs!::

    $> rm -f internal_top_level_*

Lazyness
--------

``Expressions templates`` used by numpy internal representation enable lazyness
computation. It means that operations will be computed only during assignation
to avoid intermediate array allocation and improve data locality.
Lazyness analysis enable Expression template even if there is multiple
assignment in some case.

Let's go for some examples.
In ``foo``, no intermediate array are create for ``+`` and ``*`` operations and
for each elements, two operations are apply at once instead of one by one::

    >>> def foo(array):
    ...     return array * 5 + 3

It also apply for other unary operations with numpy array.
In this example, lazyness doesn't change anything as is it a typical case for
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
    >>> lazyness = pm.gather(analysis.LazynessAnalysis, foo_tree)

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
    >>> lazyness = pm.gather(analysis.LazynessAnalysis, foo_tree)
    >>> lazyness
    {'a': 1, 'array': 2, 'b': inf}

We can notice that a reassignment reinit its value so even if ``a`` is used twice,
its counters returns ``1``.
``inf`` also happen in case of subscript use as we need to compute the value to
subscript on it. AugAssigned values can't be lazy too and variables used in
loops too.
Lazyness also cares about aliased values::

    >>> def foo(array):
    ...     a = array * 2
    ...     b = a
    ...     a_ = b * 5
    ...     return a_
    >>> foo_tree = getast(foo)
    >>> lazyness = pm.gather(analysis.LazynessAnalysis, foo_tree)
    >>> lazyness
    {'a': 2, 'array': 1, 'b': 1, 'a_': 1}
