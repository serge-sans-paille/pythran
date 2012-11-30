'''This package provides three entry points
    * spec_parser looks for code annotations in the form of formatted comments
    * cxx_generator turns a python ast into a c++ string
    * compile generates a native module from a c++ string and code annotations
'''
from interface import cxx_generator, compile
from spec import spec_parser
