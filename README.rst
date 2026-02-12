Pythran
#######

https://pythran.readthedocs.io

What is it?
-----------

Pythran is an ahead of time compiler for a subset of the Python language, with a
focus on scientific computing. It takes a Python module annotated with a few
interface descriptions and turns it into a native Python module with the same
interface, but (hopefully) faster.

It is meant to efficiently compile **scientific programs**, and takes advantage
of multi-cores and SIMD instruction units.

Until 0.9.5 (included), Pythran was supporting Python 3 and Python 2.7.
It now only supports Python **3.7** and upward.

Installation
------------

Pythran sources are hosted on https://github.com/serge-sans-paille/pythran.

Pythran releases are hosted on https://pypi.python.org/pypi/pythran.

Pythran is available on conda-forge on https://anaconda.org/conda-forge/pythran.

Debian/Ubuntu
=============

Using ``pip``
*************

1. Gather dependencies:

   Pythran depends on a few Python modules and several C++ libraries. On a debian-like platform, run::

        $> sudo apt-get install libatlas-base-dev
        $> sudo apt-get install python-dev python-ply python-numpy

2. Install with ``pip``::

        $> pip install pythran

Using ``mamba`` or ``conda``
****************************

1. Using ``mamba`` (https://github.com/conda-forge/miniforge) or ``conda`` (https://github.com/conda-forge/miniforge)
 
2. Run::

       $> mamba install -c conda-forge pythran

   or::

       $> conda install -c conda-forge pythran

Mac OSX
=======

Using brew (https://brew.sh/)::

    $> pip install pythran
    $> brew install openblas
    $> printf '[compiler]\nblas=openblas\ninclude_dirs=/usr/local/opt/openblas/include\nlibrary_dirs=/usr/local/opt/openblas/lib' > ~/.pythranrc

Depending on your setup, you may need to add the following to your ``~/.pythranrc`` file::

    [compiler]
    CXX=g++-4.9
    CC=gcc-4.9

ArchLinux
=========

Using ``pacman``::

    $> pacman -S python-pythran


Fedora
======

Using ``dnf``::

    $> dnf install pythran

Windows
=======

Windows support is on going and only targets Python 3.5+ with clang-cl::

    $> pip install pythran

Note that using ``clang-cl.exe`` is the default setting. It can be changed through the ``CXX`` and ``CC`` environment variables, but should be left as-is.  
Visual Studio 2019 Build Tools has an option to install the latest stable Clang through the ``C++ Clang tools for Windows`` option, which makes binaries 
with ``clang-cl.exe`` that are compatible with ``cl.exe``, but can handle Pythran code far better than the MSVC compiler.  These directions assume you are using
the Visual Studio 2019 Build Tools, since they are compatible with CPython 3.5+ and have the latest Clang libraries, free and easy to use.  The current link,
which may change, is here: https://my.visualstudio.com/Downloads?q=Build%20Tools%202019

On Windows, the Pythran configuration file is in: 
``[python]/Lib/site-packages/pythran/pythran-win32.cfg``

How you set this up depends on if you are using an ``Intel MKL`` linked NumPy/SciPy (such as in the Anaconda3 distribution), or if you're using pip installed NumPy/SciPy
(which is linked to ``OpenBLAS``).  There are some interesting differences in the setup files for each distribution - note the purpose here is to use the right OpenMP library:

Basic setup, ``Intel MKL`` (Anaconda3 users primarily)::

    include_dirs='C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\Llvm\x64\lib', 'C:\Users\[user_name]\Anaconda3\Library\include'
    cflags=/std:c++14 /w -Xclang -fopenmp
    ldflags=\libomp.lib
    blas=mkl
    CC=clang-cl.exe
    CXX=clang-cl.exe

In some cases, using ``Intel MKL`` will require a substitute ``cblas.h`` which isn't present with MKL.  This is not an elegant solution -
one can install the full library + headers from Intel OneAPI and create a dummy include file ``cblas.h`` which states: ``#include "mkl_cblas.h"``
When compiling, the way to include it is a: ``pythran -I"path_to_MKL_includes" scipt_to_compile.py``
The current download link for Intel OneAPI (where you can choose to only install MKL) is here: https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl.html

The current version of Intel MKL installs by default here: ``"C:\Program Files (x86)\Intel\oneAPI\mkl\2022.0.2\include"``
which is where the dummy ``cblas.h`` should be created, and ``-I`` command line flag must reference.

Note that at times, the linked OpenMP library (even though `libiomp` and `libiomp5md` are actually the same files) will cause a compiler crash - as you can't load both 
`libomp.dll` and `libiomp5md.dll` into the same session.  There is a workaround for those that are compiling Pythran projects for Intel MKL that have installed the 
Intel OneAPI MKL referenced above.  Simply change these lines in your `pythran-win32.cfg`::

    library_dirs='C:\Program Files (x86)\Intel\oneAPI\compiler\latest\windows\compiler\lib\intel64_win'
    ldflags=\libiomp5md.lib

That should resolve any crashes related to having both OpenMP libraries loaded in one session.


Basic setup, ``OpenBLAS`` (pip installed NumPy/SciPy)::

    library_dirs='C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\Llvm\x64\lib'
    cflags=/std:c++14 /w -Xclang -fopenmp
    ldflags=\libiomp5md.lib
    blas=pythran-openblas
    CC=clang-cl.exe
    CXX=clang-cl.exe

Note with the ``OpenBLAS`` package, you need to: ``pip install pythran-openblas`` so the library can be linked properly.

For the same reason stated prior under the "both OpenMP libraries in one session crash," you can also link to the `libomp.lib` by changing a few settings::

    library_dirs='C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\lib\x64'
    ldflags=\libomp.lib

Why it needs the MSVC version I'm not sure.  The point here is to offer alternative configs that will build and run with Pythran when one OpenMP library doesn't work.

Using the LLVM linker (optional):
=================================
Another thing you can choose to do is to use a different linker on Windows - i.e. instead of `link.exe` you can use the LLVM `lld-link.exe` - again,
this is not an elegant solution.  The way Pythran finds the linker is through the [python]\Lib\site-packages\setuptools\_distutils\_msvccompiler.py
To change which linker Python uses for everything, you modify the _msvccompiler.py file so it becomes the default linker.
In this file, replace ``link.exe`` with ``lld-link.exe`` and be sure to comment out ``'/LTCG'`` under ``ldflags`` as the LLVM linker
cannot understand this option, and will throw an error.  It is sufficient to just modify the file like this::

    self.linker = _find_exe("lld-link.exe", paths)
    ...
    ldflags = ['/nologo', '/INCREMENTAL:NO'#, '/LTCG' # note this LTCG flag is just commented out

This will force Pythran (and Cython) to use the LLVM linker, instead of the MSVC one.  Note if you manually compile any packages, they will also use this linker setup!

Other Platform
==============

See MANUAL file.


Basic Usage
-----------

A simple pythran input could be ``dprod.py``

.. code-block:: python

    """
    Naive dotproduct! Pythran supports numpy.dot
    """
    #pythran export dprod(int list, int list)
    def dprod(l0,l1):
        """WoW, generator expression, zip and sum."""
        return sum(x * y for x, y in zip(l0, l1))


To turn it into a native module, run::

    $> pythran dprod.py

That will generate a native dprod.so that can be imported just like the former
module::

    $> python -c 'import dprod' # this imports the native module instead


Documentation
-------------

The user documentation is available in the MANUAL file from the doc directory.

The developer documentation is available in the DEVGUIDE file from the doc
directory. There is also a TUTORIAL file for those who don't like reading
documentation.

The CLI documentation is available from the pythran help command::

    $> pythran --help

Some extra developer documentation is also available using pydoc. Beware, this
is the computer science incarnation for the famous Where's Waldo? game::

    $> pydoc pythran
    $> pydoc pythran.typing
    $> pydoc -b  # in the browser


Examples
--------

See the ``pythran/tests/cases/`` directory from the sources.


Contact
-------

Praise, flame and cookies:

- pythran@freelists.org -- register at https://www.freelists.org/list/pythran first!

- #pythran on OFTC, https://oftc.net 

- serge.guelton@telecom-bretagne.eu

The mailing list archive is available at https://www.freelists.org/archive/pythran/.

Citing
------

If you need to cite a Pythran paper, feel free to use

.. code-block:: bibtex

    @article{guelton2015pythran,
      title={Pythran: Enabling static optimization of scientific python programs},
      author={Guelton, Serge and Brunet, Pierrick and Amini, Mehdi and Merlini,
                      Adrien and Corbillon, Xavier and Raynaud, Alan},
      journal={Computational Science \& Discovery},
      volume={8},
      number={1},
      pages={014001},
      year={2015},
      publisher={IOP Publishing}
    }


Authors
-------

See AUTHORS file.

License
-------

See LICENSE file.
