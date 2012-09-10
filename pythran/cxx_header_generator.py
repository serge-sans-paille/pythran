'''Automates the creation of various pythonic++ headers
    * generate_all calls all custom generators defined locally
'''
import cxxgen
import inspect

class CodeGenerator(object):
    '''Base class for any Code Generator'''
    def __cmp__(self, other):
        return cmp(self.id, other.id)

class HeaderGenerator(CodeGenerator):
    '''Generates a dummy comment'''
    def __init__(self):self.id=0
    def __call__(self):
        return cxxgen.Line('/* Pythran is good for your health, eat it. */')

def generate_all():
    '''Scans this module for all code generators and runs them in id order.'''
    return sorted([ v()() for v in globals().itervalues() if inspect.isclass(v) and CodeGenerator in inspect.getmro(v) and v != CodeGenerator])
