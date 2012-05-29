'''This package provides three entry points
    * spec_parser looks for specific code annotations in the form of pythran-formatted comments
    * cxx_generator turns a python ast into a c++ string
    * compile merges the c++ string with the code annotations to generate a native module
'''
from interface import cxx_generator, compile
from spec import spec_parser
