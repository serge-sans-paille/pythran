=======
Pythran
=======

http://pythonhosted.org/pythran/

What is it?
-----------

Pythran is a python to c++ compiler for a subset of the python language. It
takes a python module annotated with a few interface description and turns it
into a native python module with the same interface, but (hopefully) faster.

It is meant to efficiently compile **scientific programs**, and takes advantage
of multi-cores and SIMD instruction units.

Pythran development is currently done using Python version **2.7**.

Installation
------------

Pythran sources are hosted on https://github.com/serge-sans-paille/pythran.

Pythran releases are hosted on http://pypi.python.org/pypi/pythran.

1. Gather dependencies:

   Pythran depends on a few Python modules and several C++ libraries. On a debian-like platform, run::

        $> sudo apt-get install libboost-python-dev libgoogle-perftools-dev libgmp-dev libboost-dev git cmake
        $> sudo apt-get install python-ply python-networkx python-numpy

2. Use the install target from setup script, in source directory::

		$> python setup.py install --prefix=<my_prefix>

3. Write your environment in stone::
		
		$> export PYTHONPATH=<my_prefix>/lib/python<my_version>/site-packages
		$> export PATH=<my_prefix>/bin:$PATH

**or**

1. Add serge_sans_paille's debian server to your `source.list`, following the
   instruction given in http://serge.liyun.free.fr/serge/debian.html

2. Run the classic::

		$> sudo apt-get update
		$> sudo apt-get install pythran


Basic Usage
-----------

A simple pythran input could be ``dprod.py``::

	#pythran export dprod(int list, int list)
	def dprod(l0,l1):
		return sum(x*y for x,y in zip(l0,l1))

To turn it into a native module, run::

	$> pythran dprod.py

That will generate a native dprod.so that can be imported just like the former
module.

Documentation
-------------

The user documentation is available in the MANUAL file from the doc directory.

The developer documentation is available in the DEVGUIDE file from the doc
directory. The also is a TUTORIAL file for those who don't like reading
documentation.

A todo list is maintained in the eponymous TODO file.

The CLI documentation is available from the pythran help command::

	$> pythran --help

Some extra developer documentation is also available using pydoc. Beware, this
is the computer science incarnation for the famous Where's Waldo? game::

	$> pydoc pythran
	$> pydoc pythran.typing


Examples
--------

See the ``pythran/tests/cases/`` directory from the sources.
	

Contact
-------

Praise, flame and cookies:

- pythran@freelists.org -- register at http://www.freelists.org/list/pythran first!

- #pythran on FreeNode

- serge.guelton@telecom-bretagne.eu

Authors
-------

See AUTHORS file.

License
-------

See LICENSE file.

