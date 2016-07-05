Command Line Interface
######################

This file shows some use case of Pythran on the command line.

Firstly lets clear the working space::

  $> rm -f cli_*

..  Small hack to setup the $PATH in a compatible way
..  >>> import os, pythran, re
..  >>> if 'lib' in pythran.__file__: os.environ['PATH'] = re.sub(r'(.*)/lib/.*', r'\1/bin:', pythran.__file__) + os.environ['PATH']
..  >>> os.environ['PATH'] = './scripts:' + os.environ['PATH']

One of the most classic use case in Pythran is to generate a native .so module::

  $> printf '#pythran export foo()\n#pythran export msg\nmsg = \"hello world\"\ndef foo(): print msg' > cli_foo.py
  $> pythran cli_foo.py
  $> ls cli_foo.so
  cli_foo.so

The generated native ``.so`` module can then be used with the Python interpreter::

  $> python -c 'import cli_foo ; cli_foo.foo()'
  hello world
  $> python -c 'import cli_foo ; print(cli_foo.msg)'
  hello world

Pythran version can be dumped through ``--version``::

  $> pythran --version 2>&1
  0.7.6post1

The module-level ``__pythran__`` variable indicates that the module loaded has been pythranized::

  $> python -c 'import cli_foo ; print(hasattr(cli_foo, \"__pythran__\"))'
  True

You can choose your optimization level by using ``-O`` flag::

  $> rm cli_foo.so
  $> pythran cli_foo.py -O2
  $> ls cli_foo.so
  cli_foo.so

Out of curiosity, you can check the generated output::

  $> pythran -E cli_foo.py

That's some heavily templated code ;-) Pythran can then compile it for you to a Python module::

  $> pythran cli_foo.cpp

Pythran can also generate raw C++ code, using the ``-e`` switch::

  $> pythran -e cli_foo.py -o cli_foo.hpp
  $> printf '#include \"cli_foo.hpp\"\nusing namespace __pythran_cli_foo ; int main() { foo()(); return 0 ; }' > cli_foo.cpp
  $> `pythran-config --compiler --cflags` -std=c++11 cli_foo.cpp -o cli_foo -DNDEBUG `pythran-config --libs`
  $> ./cli_foo
  hello world

You can use ``-p`` option to apply a Pythran optimization. For example, the python
code can propagate constants using the Pythran ConstantFolding optimization::

  $> pythran -e cli_foo.py -p pythran.optimizations.ConstantFolding

If you want to specify the path of generated file::

  $> pythran cli_foo.py -o /tmp/cli_foo.so -DNDEBUG
  $> ls /tmp/cli_foo.so
  /tmp/cli_foo.so

To know more options about Pythran, you can check ``pythran --help`` :-)
