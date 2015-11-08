User Manual
###########

So you want to write algorithms that are easy to maintain as in Python and
you want performance as in FORTRAN or C++? Let give a try to Pythran!
Pythran is a Python-to-c++ translator that turns Python module into native
c++11 module. From a user point of view, you still ``import`` your module, but
under the hood... There is much more happening!

Disclaimer
----------

Pythran is *not* a full Python-to-c++ converter, as in *shedskin*. Instead it
takes a subset of the Python language and turns it into heavily templatized c++
code instantiated for your particular types.

Say hello to:

- polymorphic functions (!)
- lambdas
- list comprehension
- map, reduce and the like
- dictionaries, set, list
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

- GMP: https://gmplib.org/
- ply: http://www.dabeaz.com/ply/
- networkx: https://networkx.github.io/
- numpy: http://www.numpy.org/

You also need a modern C++11 enabled compiler (e.g. g++>=4.9, clang>=3.5), that supports
for instance atomic operations (N3290) or variadic template (N2555).


Manual Installation
-------------------

First get the sources::

    $> git clone https://github.com/serge-sans-paille/pythran

Install *cough* numpy manually::

    $> pip install --user numpy

The from the source directory, run::

    $> python setup.py install --user

And set your path to::

    $> export PATH=$PATH:$HOME/.local/bin

It makes the ``pythran`` command available to you.

Making Sure Everything is working
---------------------------------

The ``setup.py`` scripts automates this. The ``test`` target, as in::

    python setup.py test

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

is perfect. But due to \_o< typing, ``arr0`` and ``arr1`` can be of any type,
so Pythran needs a small hint there. Add the following line somewhere in your
file, say at the top head, or right before the function definition::

    #pythran export dprod(int list, int list)

This basically tells Pythran the type of the forthcoming arguments.


Afterwards, frenetically type::

    $> pythran dprod.py

\o/ a ``dprod.so`` native module has been created and you can play with it
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

This a slightly more complex example, as a few intrinsics such as ``range`` or
``len`` are used, with a function call and even nested list comprehension. But
Pythran can make its way through this. As you only want to export the
``matrix_multiply`` function, you can safely ignore the ``zero`` function and
just add::

    #pythran export matrix_multiply(float list list, float list list)

to the source file. Note how Pythran can combine different types and infers the
resulting type. It also respects the nested list structure of Python, so you
are not limited to matrices...

Enough talk, run::

    $> pythran mm.py

One touch of magic wand and you have your native binary. Be amazed by the
generation of a ``mm.so`` native module that run around 20x faster than the
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
handling such expressions. As you already now, you need to **export** it, giving its
argument type by adding::

    #pythran export arc_distance(float[], float[], float[], float[])

To the input file. You can compile it as the previous code::

    $> pythran arc_distance.py

and you'll get a decent binary. But what you really wanted to do was::

    $> pythran -fopenmp -march=avx arc_distance.py

which basically tells the compiler to parallelize and vectorize loops. Then you'll get **really** fast code!



Concerning Pythran specifications
---------------------------------

The ``#pythran export`` commands are critical to Pythran. In fact if they are
missing, Pythran will complain loudly (and fail miserably). So let us dive into
these complex language!

There is currently only one Pythran command, the ``export`` command. Its syntax is::

    #pythran export function_name(argument_type*)

where ``function_name`` is the name of a function defined in the module, and
``argument_type*`` is a comma separated list of argument types, composed of any
combination of basic types and constructed types. What is a basic type?
Anything that looks like a Python basic type! Constructed types are either
tuples, introduced by parenthesis, like ``(int, (float, str))`` or lists (resp.
set), introduced by the ``list`` (resp. ``set``) keyword::

    argument_type = basic_type
                  | (argument_type+)    # this is a tuple
                  | argument_type list    # this is a list
                  | argument_type set    # this is a set
                  | argument_type []+    # this is a ndarray
                  | argument_type [::]+    # this is a strided ndarray
                  | argument_type:argument_type dict    # this is a dictionary

    basic_type = bool | int | long | float | str
               | uint8 | uint16 | uint32 | uint64
               | int8 | int16 | int32 | int64
               | float32 | float64
               | complex64 | complex128


Easy enough, isn't it?

.. note::

    It is in fact possible to analyse a code without specifications, but you
    cannot go further that generic (a.k.a. heavily templated) c++ code. Use the
    ``-e`` switch!


IPython Integration
-------------------

The magic function ``%%pythran`` is made available to ``ipython`` users through an
extension. The extension is located in the ``extensions/`` directory
and can be loaded using IPython's magic function::

    %load_ext pythranmagic

Once done, you can pythranize your code from the IPython shell::

    %%pythran
    #pythran export foo()
    def foo(): print 'hello'

Distutils Integration
---------------------

When distributing a Python application with Pythran modules, you can either:

* declare the module as a regular Python module. After all, they are 100% Python compatible.

* declare them as a ``PythranExtension`` and Pythran will compile them::

    from distutils.core import setup
    from pythran.dist import PythranExtension
    setup(...,
          ext_modules=[PythranExtension("mymodule", ["mymodule.py"])])

Advanced Usage
--------------

A failing compilation? A lust of c++ tangled code? Give a try to the ``-E``
switch that stops the compilation process right after c++ code generation, so
that you can inspect it.

Want more performance? Big fan of ``-Ofast -march=native``? Pythran
_automagically_ forwards these switches to the underlying compiler! Pythran is
sensible to the ``-DNDEBUG`` switch too.

Tired of typing the same compiler switches again and again? Store them in
``$XDG_CONFIG_HOME/.pythranrc``!

Wants to try your own compiler? Update the `CC` and `CXX` fields from your
`pythranrc`, or set the same env variables to the right compilers.

The careful reader might have noticed the ``-p`` flag from the command line. It
makes it possible to define your own optimization sequence::

    pythran -pConstantFodling -pmy_package.MyOptimization

runs the ``ConstantFolding`` optimization from ``pythran.optimizations``
followed by a custom optimization found in the ``my_package`` package, loaded
from ``PYTHONPATH``.

When importing a Python module, one can check for the presence of the
``__pythran__`` variable at module scope to see if the module has been
pythranized::

    import foo
    if hasattr(foo, '__pythran__'):
        print(r'\_o<')

This variable is a tuble that holds three fields:

1. pythran's version
2. compilation date
3. sha256 value of the input code


Adding OpenMP directives
------------------------

OpenMP is a standard set of directives for C, C++ and FORTRAN that makes it
somehow easier to turn a sequential program into a multi-threaded one. Pythran
translates OpenMP-like code annotation into OpenMP directives::

    r=0
    "omp parallel for reduction(+:r)"
    for x,y in zip(l1,l2):
        r+=x*y

OpenMP directive parsing is enabled by ``-fopenmp`` when using ``g++`` as the
back-end compiler.

Alternatively, one can run the great::

    pythran -ppythran.analysis.ParallelMaps -e as.py

which runs a code analyzer that displays extra information concerning parallel ``map`` found in the code.

You may want a more "OpenMP" way to write annotation with::

    r=0
    #omp parallel for reduction(+:r)
    for x,y in zip(l1,l2):
        r+=x*y

Be careful with the indentation. It has to be correct.


Getting Pure C++
----------------

Pythran can be used to generate raw templated C++ code, without any Python
glue. To do so use the ``-e`` switch. It will turn the Python code into c++
code you can call from a C++ code. In that case there is **no** need for a
particular Pythran specification.

Customizing Your ``.pythranrc``
-------------------------------

Pythran checks for a file named ``.pythranrc`` and use it to *replace* the site
configuration. Here are a few tricks!


``[compiler]``
==============

These sections contains compiler flags configuration. For education purpose, the default linux configuration is

.. literalinclude:: ../pythran/pythran-linux2.cfg

:``CC``:

    Path to the C compiler to use

:``CXX``:

    Path to the C++ compiler to use

:``defines``:

    Preprocessor definitions. Pythran is sensible to ``USE_BOOST_SIMD`` and
    ``PYTHRAN_OPENMP_MIN_ITERATION_COUNT``. The former turns on Boost.simd
    vectorization and the latter controls the mimimal loop trip count to turn a
    sequential loop in a parallel loop. The default is to set ``USE_GMP``, so
    that Python's long are represented using GMP.

:``undefs``:

    Some preprocessor definitions to remove.

:``include_dirs``:

    Additionnal include directories to search for headers.

:``cflags``:

    Additionnal random compiler flags (``-f``, ``-O``). Optimization flags generally
    go there. The default is to set ``-std=c++11`` for C++11 support.

:``libs``:

    Libraries to use during the link process. A typical extension
    is to add ``tcmalloc_minimal`` to use the allocator from
    https://code.google.com/p/gperftools/.

:``library_dirs``:

    Extra libraries directories to search for required libraries.

:``ldflags``:

    Additionnal random linker flags.


``[pythran]``
=============

This one contains internal configuration settings. Play with it at your own risk!

:``optimizations``:

    A list of import path pointing to transformation classes. This contains the
    optimization pipeline of Pythran! If you design your own optimizations,
    register them here!

:``complex_hook``:

    Set this to ``True`` for faster and still numpy-compliant complex
    multiplications. Not very portable, but generally works on Linux.

``[typing]``
============

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

   - `g++` version 4.9

   - `clang++` version 3.5

Troubleshooting
---------------

Plenty of them! Seriously, Pythran is software, so it will crash. You
must make it abort in unusual ways! And more important, you must provide
feedback to serge_sans_paille using its email serge.guelton@telecom-bretagne.eu,
the IRC channel ``#pythran`` on FreeNode, or the mailing list ``pythran@freelists.org``

**glhf!**
