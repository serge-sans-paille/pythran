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

  $> printf '#pythran export foo()\n#pythran export msg\nmsg = \"hello world\"\ndef foo(): print(msg)' > cli_foo.py
  $> pythran cli_foo.py -o cli_foo.so
  $> ls cli_foo.so
  cli_foo.so

The generated native ``.so`` module can then be used with the Python interpreter::

  $> python -c 'import cli_foo ; cli_foo.foo()'
  hello world
  $> python -c 'import cli_foo ; print(cli_foo.msg)'
  hello world

Pythran version can be dumped through ``--version``::

  $> pythran --version 2>&1
  0.18.0

The module-level ``__pythran__`` variable indicates that the module loaded has been pythranized::

  $> python -c 'import cli_foo ; print(hasattr(cli_foo, \"__pythran__\"))'
  True

You can choose your optimization level by using ``-O`` flag::

  $> rm cli_foo.so
  $> pythran cli_foo.py -O2 -o cli_foo.so
  $> ls cli_foo.so
  cli_foo.so

You can use ``-p`` option to apply a Pythran optimization. For example, the python
code can propagate constants using the Pythran ConstantFolding optimization::

  $> pythran -e cli_foo.py -p pythran.optimizations.ConstantFolding

If you want to specify the path of generated file::

  $> pythran cli_foo.py -o /tmp/cli_foo.so -DNDEBUG
  $> ls /tmp/cli_foo.so
  /tmp/cli_foo.so

Out of curiosity, you can check the generated output::

  $> pythran -E cli_foo.py

That's some heavily templated code ;-) Pythran can then compile it for you to a Python module::

  $> pythran cli_foo.cpp -o cli_foo.so

Pythran can also generate raw C++ code, using the ``-e`` switch::

  $> printf 'msg = \"hello world\"\ndef bar(): print(msg)' > cli_bar.py
  $> pythran -e cli_bar.py -w -o cli_bar.hpp
  $> printf '#include \"cli_bar.hpp\"\nusing namespace __pythran_cli_bar ; int main() { bar()(); return 0 ; }' > cli_bar.cpp
  $> `pythran-config --compiler --cflags` -std=c++11 cli_bar.cpp -o cli_bar
  $> ./cli_bar
  hello world

To know more options about Pythran, you can check::

  $> pythran --help
  usage: pythran [-h] [-o OUTPUT_FILE] [-P] [-E] [-e] [-v] [-w] [-V] [-p pass]
                 [-I include_dir] [-L ldflags] [-D macro_definition]
                 [-U macro_definition] [--config config] [-ftime-report]
                 [--trace-allocations]
                 input_file
  
  pythran: a python to C++ compiler
  
  positional arguments:
    input_file           the pythran module to compile, either a .py or a .cpp
                         file
  
  optional arguments:
    -h, --help           show this help message and exit
    -o OUTPUT_FILE       path to generated file. Honors %{ext}.
    -P                   only run the high-level optimizer, do not compile
    -E                   only run the translator, do not compile
    -e                   similar to -E, but does not generate python glue
    -v                   be more verbose
    -w                   be less verbose
    -V, --version        show program's version number and exit
    -p pass              any pythran optimization to apply before code
                         generation
    -I include_dir       any include dir relevant to the underlying C++ compiler
    -L ldflags           any search dir relevant to the linker
    -D macro_definition  any macro definition relevant to the underlying C++
                         compiler
    -U macro_definition  any macro undef relevant to the underlying C++ compiler
    --config config      config additional params
    -ftime-report        report time spent in each optimization/transformation
    --trace-allocations  instrument execution to trace memory allocations
  
  It's a megablast!
