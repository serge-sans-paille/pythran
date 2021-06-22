User Manual
###########

So you want to write algorithms that are easy to maintain as in Python and
you want performance as in FORTRAN or C++? Lets give a try to Pythran!
Pythran is a Python-to-c++ translator that turns Python modules into native
c++11 modules. From a user point of view, you still ``import`` your module, but
under the hood... There is much more happening!

Disclaimer
----------

Pythran is *not* a full Python-to-c++ converter, as is *shedskin*. Instead it
takes a subset of the Python language and turns it into heavily templatized c++
code instantiated for your particular types.

Say hello to:

- polymorphic functions (!)
- lambdas
- list comprehension
- map, reduce and the like
- dictionary, set, list
- exceptions
- file handling
- (partial) `numpy` support

Say bye bye to:

- classes
- polymorphic variables [ but not all of them :-) ]

In a nutshell, Pythran makes it possible to write numerical algorithms in
Python and to have them run faster. Nuff said.


Prerequisite
------------

Pythran depends on the following packages:

.. include:: ../requirements.txt
    :literal:

You also need a modern C++11 enabled compiler (e.g. g++>=5, clang>=3.5), that supports
atomic operations (N3290) and variadic template (N2555).


Installation from Sources
-------------------------

The prefered way to install Pythran is using ``pip install pythran`` or
``conda install pythran``. Yet if you want to install from sources,
here is the procedure.

First get the sources::

    $> git clone https://github.com/serge-sans-paille/pythran

From the source directory, run::

    $> pip install .

``pythran`` should now be on your ``PATH``. If not, it's possible ``pip``
installed to ``.local`` (this happens if the default ``site-packages``
location requires elevated permissions) - fix this by setting your path to::

    $> export PATH=$PATH:$HOME/.local/bin

It makes the ``pythran`` command available to you.

Making Sure Everything is working
---------------------------------

The ``setup.py`` scripts automates this. The ``test`` target, as in::

    $> python setup.py test

runs a whole (and long) validation suite (you will need to install the
``pytest`` module first to use it).

If these tests fail, you are likely missing some of the requirements. You can
set site specific flags in your ``~/.pythranrc``, read the doc a bit further!

First Steps
-----------

To begin with, you need... a Python function in a module. Something like::

    <<dprod.py>>
    def dprod(arr0, arr1):
        return sum([x*y for x,y in zip(arr0, arr1)])

is perfect. But due to ``\_o<`` typing, ``arr0`` and ``arr1`` can be of any type,
so Pythran needs a small hint there. Add the following line somewhere in your
file, say at the top head, or right before the function definition::

    #pythran export dprod(int list, int list)

This basically tells Pythran the type of the forthcoming arguments.


Afterwards, frenetically type::

    $> pythran dprod.py

``\o/`` a ``dprod.so`` native module has been created and you can play with it
right *now*, as if it where a normal module::

    >>> import dprod # this imports the native version if available
    >>> dprod.dprod([1,2], [3,4])
    11

The speedup will not be terrific because of the conversion cost
from Python to C++.

So let's try again with a well-known example. Let me
introduce the almighty *matrix multiply*!::

    <<mm.py>>
    def zero(n,m): return [[0]*n for col in range(m)]
    def matrix_multiply(m0, m1):
        new_matrix = zero(len(m0),len(m1[0]))
        for i in range(len(m0)):
            for j in range(len(m1[0])):
                for k in range(len(m1)):
                    new_matrix[i][j] += m0[i][k]*m1[k][j]
        return new_matrix

This is a slightly more complex example, as a few intrinsics such as ``range`` and
``len`` are used, with a function call and even nested list comprehension. But
Pythran can make its way through this. As you only want to export the
``matrix_multiply`` function, you can safely ignore the ``zero`` function and
just add::

    #pythran export matrix_multiply(float list list, float list list)

to the source file. Note how Pythran can combine different types and infer the
resulting type. It also respects the nested list structure of Python, so you
are not limited to matrices...

Enough talk, run::

    $> pythran mm.py

One touch of magic wand and you have your native binary. Be amazed by the
generation of a ``mm.so`` native module that runs around 20x faster than the
original one. ``timeit`` approved!

But scientific computing in Python usually means Numpy. Here is a well-known Numpy snippet::

    <<arc_distance.py>>
    import numpy as np
    def arc_distance(theta_1, phi_1, theta_2, phi_2):
        """
        Calculates the pairwise arc distance
        between all points in vector a and b.
        """
        temp = (np.sin((theta_2-theta_1)/2)**2
               + np.cos(theta_1)*np.cos(theta_2) * np.sin((phi_2-phi_1)/2)**2)
        distance_matrix = 2 * np.arctan2(np.sqrt(temp), np.sqrt(1-temp))
        return distance_matrix

This example uses a lot of Numpy `ufunc`. Pythran is reasonably good at
handling such expressions. As you already know, you need to **export** it, giving its
argument types by adding::

    #pythran export arc_distance(float[], float[], float[], float[])

To the input file. You can compile it as the previous code::

    $> pythran arc_distance.py

and you'll get a decent binary. But what you really want to do is::

    $> pythran -DUSE_XSIMD -fopenmp -march=native arc_distance.py

which basically tells the compiler to parallelize and vectorize loops using
whatever hardware available on your machine. Then you'll get **really** fast
code!


Concerning Pythran specifications
---------------------------------

The ``#pythran export`` commands are critical to Pythran. In fact if they are
missing, Pythran will complain loudly (and fail miserably). So let us dive into
this complex language!

There is currently only one Pythran command, the ``export`` command. Its syntax is::

    #pythran export function_name(argument_type* [, argument_type ? *])

where ``function_name`` is the name of a function defined in the module, and
``argument_type*`` is a comma separated list of argument types, composed of any
combination of basic types and constructed types. ``argument_type ? *`` is a
comma separated list of optional argument types, similar to ``argument_type``
but followed by a ``?``.

What is an ``argument_type``? Anything that looks like a Python basic type!
Constructed types are either tuples, introduced by parenthesis, like ``(int,
(float, str))`` or lists (resp.  set), introduced by the ``list`` (resp.
``set``) keyword::

    argument_type = basic_type
                  | (argument_type+)    # this is a tuple
                  | argument_type list    # this is a list
                  | argument_type set    # this is a set
                  | argument_type []+    # this is a ndarray, C-style
                  | argument_type [::]+    # this is a strided ndarray
                  | argument_type [:,...,:]+ # this is a ndarray, Cython style
                  | argument_type [:,...,3]+ # this is a ndarray, some dimension fixed
                  | argument_type:argument_type dict    # this is a dictionary

    basic_type = bool | byte | int | float | str | None | slice
               | uint8 | uint16 | uint32 | uint64 | uintp
               | int8 | int16 | int32 | int64 | intp
               | float32 | float64 | float128
               | complex64 | complex128 | complex256

.. note::

    When using a 2D array, overloads of the function involved are created to accept both C-style and Fortran-style arrays.
    To avoid generating too many functions, one can force the memory layout using ``order(C)`` or ``order(F)`` after the
    array decalaration, as in ``int[:,:] order(C)``.

The same syntax can be used to export global variable (in read only mode)::

    #pythran export var_name


In a similar manner to the Python import statement, it's possible to chain the export, as in::

    #pythran export var_name0, var_name1, function_name(argument_type0)

Multiple overloads can be specified for the same Python function::

    #pythran export function_name(argument_type0)
    #pythran export function_name(argument_type1)

In the case of function with default parameters, you can either omit the
parameter, and in that case it uses the default one, or explicitly state it's
argument type::

    #pythran export function_name()
    #pythran export function_name(argument_type0)
    #pythran export function_name(argument_type0, argument_type1)
    def function_name(a0=1, a1=True):
       pass

When specifying multiple overloads, instead of listing them, you can use the ``or`` operator to list the alternatives, as in::

    #pythran export function_name(type0 or type1, type2, type3 or type4)

which is exactly equivalent to::

    #pythran export function_name(type0, type2, type3)
    #pythran export function_name(type0, type2, type4)
    #pythran export function_name(type1, type2, type3)
    #pythran export function_name(type1, type2, type4)

Easy enough, isn't it?



.. note::

    Multiline exports are supported, just use comments to protect them, as in::

        #pythran export river_boa(int,
        #                         float,
        #                         bool)

.. note::

    It is in fact possible to analyse a code without specifications, but you
    cannot go further that generic (a.k.a. heavily templated) c++ code. Use the
    ``-e`` switch!


.pythran files
**************

Instead of writing the export lines in the ``.py`` file, it is possible to
write them, **without the #pythran** prefix, inside a file that has the same
path has the ``.py`` file, but with the ``.pythran`` extension. For instance,
file ``I_love.py`` can have its export lines in the ``I_love.pythran`` file, using the syntax::

    export function_name(argument_type*)

Limitations
***********

Pythran tries hard to produce code that has the same observable behavior as the original Python code.
Unfortunately it's not always possible:

- Pythran does not support heterogeneous containers (except tuples).

- There is no BigInt support. All integer operations are performed on ``long``
  (probably ``int64_t`` on a 64 bit machine.)

- In most cases (with the notable exception of ``numpy.ndarray``), Pythran is
  working on a deep copy of the original Python arguments. This copy shares no memory
  relationship with the original object, which means that modifying the
  argument content in Pythran won't modify the original argument content.
  Likewise, objects generated by Pythran cannot share reference (in the sense
  of ``is``) with one of the input argument.
  Of curse, this limitation doesn't apply to non exported functions.


GIL Interaction
---------------

As Pythran translates the Python code in native code that only depends on
``libpython`` for data translation, it can release the GIL during the actual
function run. And that's what it does :-) Put an another way, you can rip some
speedup at the Python level just by spawning multiple ``threading.Thread``.


IPython Integration
-------------------

The magic function ``%%pythran`` is made available to ``ipython`` users through an
extension. The extension is located in the ``extensions/`` directory
and can be loaded using IPython's magic function::

    %load_ext pythran.magic

Once done, you can pythranize your code from the IPython shell::

    %%pythran
    #pythran export foo()
    def foo(): print 'hello'

You can pass arguments to this magic, as in::

    %%pythran(-O2 -fopenmp)
    #pythran export foo()
    def foo(): print 'hello'


Distutils Integration
---------------------

When distributing a Python application with Pythran modules, you can either:

* declare the module as a regular Python module. After all, they are 100% Python compatible.

* declare them as a ``PythranExtension`` and Pythran will compile them::

    from distutils.core import setup

    # These two lines are required to be able to use pythran in the setup.py
    import setuptools
    setuptools.dist.Distribution(dict(setup_requires='pythran'))

    from pythran.dist import PythranExtension, PythranBuildExt
    setup(...,
          ext_modules=[PythranExtension("mymodule", ["mymodule.py"])],
          cmdclass={"build_ext": PythranBuildExt})

``PythranBuildExt`` is optional, but necessary to build extensions with
different C++ compilers. It derives from distuil's ``build_ext`` by default, but
you can change its base class by using ``PythranBuildExt[base_cls]`` instead.

* all configuration options supported in ``.pythranrc`` can also be passed
  through the optional ``config`` argument, in the form of a list, e.g.
  ``config=['compiler.blas=openblas']``

.. note::

    There's no strong compatibility guarantee between Pythran version at C++ level. As a
    consequence, a code distrubuted under pythran version 0.x should depend on that exact
    version, as version 0.y may introduce some changes.

    This behavior is likely to change with revisions >= 1.


Capsule Corp
------------

Instead of creating functions that can be used from Python code, Pythran can
produce native functions to be used by other Python extension, using the
``Capsule`` mechanism. To do so, just add the ``capsule`` keyword to the export
line::

    #pythran export capsule foo(double*, double)

Note that pointer types are only supported within the context of a capsule, as
they don't match any real Python type. **Any** Pythran type is valid as capsule
parameter, but beware that non scalar or pointer types only make sense withing
the Pythran context.

Debug Mode
----------

Pythran honors the ``NDEBUG`` macro. If set through ``-DNDEBUG`` (which should
be the default, check ``python-config --cflags``), it disables all ``assert
statement`` and doesn't perform any runtime check for indexing bounds etc.
However, if unset through ``-UNDEBUG``, all ``assert`` are executed and
eventually raise an ``AssertionError``. Additionnaly, many internal checks are
done and may fail with a C-ish assertion.

Thread safety
-------------

By default Pythran does not generate thread-safe code for non-OpenMP code: reference
counting for automatic deletion of objects is not done atomically by default. It's
still possible to force pythran to generate thread-safe reference counting by defining
the flag ``THREAD_SAFE_REF_COUNT`` via ``-DTHREAD_SAFE_REF_COUNT``. There is a small
performance penalty associated with this.

Advanced Usage
--------------

One can use ``-o <filename>`` or ``--output=<filename>`` to control the name of
the generated file. If ``<filename>`` contains the ``%{ext}`` pattern, it is
replaced by the extension that matches your current platform.

A failing compilation? A lust for c++ tangled code? Give a try to the ``-E``
switch that stops the compilation process right after c++ code generation, so
that you can inspect it.

Want more performance? Big fan of ``-Ofast -march=native``? Pythran
_automagically_ forwards these switches to the underlying compiler!

Tired of typing the same compiler switches again and again? Store them in
``$XDG_CONFIG_HOME/.pythranrc``!

Wants to try your own compiler? Update the ``CC`` and ``CXX`` fields from your
``pythranrc``, or set the same environment variables to the right compilers. Environment
variables have greater precedence than configuration file.

Pythran also honors the ``CXXFLAGS`` and ``LDFLAGS`` environment variables.

The careful reader might have noticed the ``-p`` flag from the command line. It
makes it possible to define your own optimization sequence::

    pythran -pConstantFolding -pmy_package.MyOptimization

runs the ``ConstantFolding`` optimization from ``pythran.optimizations``
followed by a custom optimization found in the ``my_package`` package, loaded
from ``PYTHONPATH``.

When importing a Python module, one can check for the presence of the
``__pythran__`` variable at the module scope to see if the module has been
pythranized::

    import foo
    if hasattr(foo, '__pythran__'):
        print(r'\_o<')

This variable is a tuple that holds three fields:

1. pythran's version
2. compilation date
3. sha256 value of the input code


Adding OpenMP directives
------------------------

OpenMP is a standard set of directives for C, C++ and FORTRAN that makes it
easier to turn a sequential program into a multi-threaded one. Pythran
translates OpenMP-like code annotation into OpenMP directives::

    r=0
    #omp parallel for reduction(+:r)
    for x,y in zip(l1,l2):
        r+=x*y

OpenMP directive parsing is enabled by ``-fopenmp`` when using ``g++`` as the
back-end compiler. Be careful with the indentation. It has to be correct!

Alternatively, one can run the great::

    $> pythran -ppythran.analyses.ParallelMaps -e as.py

which runs a code analyzer that displays extra information concerning parallel ``map`` found in the code.


Getting Pure C++
----------------

Pythran can be used to generate raw templated C++ code, without any Python
glue. To do so use the ``-e`` switch. It will turn the Python code into C++
code you can call from a C++ program. In that case there is **no** need for a
particular Pythran specification.


Read the optimized Python code
------------------------------

Curious Python developers might want to study how Pythran transforms their
codes.  With the ``-P`` switch, Pythran optimizes the Python code, prints the
result and stops there.  Pythran does not care about PEP 8, so a Python
formatter is often useful::

    $> pythran -P arc_distance.py | yapf


Customizing Your ``.pythranrc``
-------------------------------

Pythran checks for a file named ``.pythranrc`` and use it to *replace* the site
configuration. Here are a few tricks!

You can change the default location of the pythran configuration file using the
environment variable ``PYTHRANRC``::

    PYTHRANRC=/opt/company/pythran/config.pythranrc pythran arc_distance.py

All the options in the ``.pythranrc`` file can be specified when running pythran by using the command line argument --config= .
For example::

    pythran --config compiler.blas=pythran-openblas this_file.py

would specify that pythran-openblas is the blas library to use.

Options specified using command-line arguments override the options found in the ``.pythranrc`` file


``[compiler]``
**************

This section contains compiler flags configuration. For education purpose, the default linux configuration is

.. literalinclude:: ../pythran/pythran-linux2.cfg

:``CC``:

    Path to the C compiler to use

:``CXX``:

    Path to the C++ compiler to use

:``defines``:

    Preprocessor definitions. Pythran is sensible to ``USE_XSIMD`` and
    ``PYTHRAN_OPENMP_MIN_ITERATION_COUNT``. The former turns on `xsimd <https://github.com/QuantStack/xsimd>`_
    vectorization and the latter controls the minimal loop trip count to turn a
    sequential loop into a parallel loop.

:``undefs``:

    Some preprocessor definitions to remove.

:``include_dirs``:

    Additional include directories to search for headers.

:``cflags``:

    Additional random compiler flags (``-f``, ``-O``). Optimization flags generally
    go there. The default is to set ``-std=c++11`` for C++11 support.

:``libs``:

    Libraries to use during the link process. A typical extension
    is to add ``tcmalloc_minimal`` to use the allocator from
    https://code.google.com/p/gperftools/.

:``library_dirs``:

    Extra directories to search for required libraries.

:``ldflags``:

    Additional random linker flags.

:``blas``:

    BLAS library to use. ``none``, ``pythran-openblas``, ``blas``,
    ``openblas``, ``atlas`` or ``mkl`` are viable choices.
    ``none`` prevents from linking with blas.
    ``pythran-openblas`` requires the `pythran-openblas
    <https://pypi.org/project/pythran-openblas/>`_ package, which provides a
    statically linked version of `OpenBLAS <https://www.openblas.net/>`_. Other
    options are system dependant. Depending on your setup, you *may* need to
    update ``include_dirs`` to point to the location of the BLAS headers, e.g.
    ``/usr/include/openblas``.

:``ignoreflags``:

    Space-separated list of compiler flags that should not be forwarded to the
    pythran backend compiler when inherited, for instance, from
    ``python-config``. For instance ``-Wstrict-prototypes`` is a C-only option
    that should be pruned.


``[pythran]``
*************

This one contains internal configuration settings. Play with it at your own risk!

:``optimizations``:

    A list of import paths pointing to transformation classes. This contains the
    optimization pipeline of Pythran! If you design your own optimizations,
    register them here!

:``complex_hook``:

    Set this to ``True`` for faster and still Numpy-compliant complex
    multiplications. Not very portable, but generally works on Linux.

``[typing]``
************

Another internal setting stuff. This controls the accuracy of the typing phase. An extract from the default setting file should convince you not to touch it::

    [typing]

    # maximum number of container access taken into account during type inference
    # increasing this value inreases typing accuracy
    # but slows down compilation time, to the point of making g++ crash
    max_container_type = 2

    # maximum number of combiner per user function
    # increasing this value inreases typing accuracy
    # but slows down compilation time, to the point of making g++ crash
    max_combiner = 2

    # set this to true to enable a costly yet more accurate type inference algorithm
    # This algorithms generates code difficult to compile for g++, but not clang++
    enable_two_steps_typing = False


F.A.Q.
------

1. Supported compiler versions:

   - `g++` version 4.9 and above

   - `clang++` version 3.5 and above

Troubleshooting
---------------

Plenty of them! Seriously, Pythran is software, so it will crash. You
may make it abort in unusual ways! And more importantly, please provide
feedback to serge_sans_paille using its email ``serge.guelton@telecom-bretagne.eu``,
the IRC channel ``#pythran`` on FreeNode, or the mailing list ``pythran@freelists.org``

**glhf!**
