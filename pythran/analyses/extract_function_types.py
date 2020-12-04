# Copyright whatever. I don't care.

from pythran.passmanager import ModuleAnalysis
from pythran.tables import MODULES
from pythran.spec import Spec
from pythran.typing import List, Set, Tuple, NDArray
from pythran.log import logger as log
from pythran import types
from pythran import spec
from astpretty import pprint
from typing import ClassVar

import gast as ast

import numpy as np

dtypes = {
    'bool': np.bool,
    'byte': np.byte,
    'complex': np.complex,
    'int': np.int,
    'float': np.float,
    'uint8': np.uint8,
    'uint16': np.uint16,
    'uint32': np.uint32,
    'uint64': np.uint64,
    'uintc': np.uintc,
    'uintp': np.uintp,
    'int8': np.int8,
    'int16': np.int16,
    'int32': np.int32,
    'int64': np.int64,
    'intc': np.intc,
    'intp': np.intp,
    'float32': np.float32,
    'float64': np.float64,
    'float128': np.float128,
    'complex64': np.complex64,
    'complex128': np.complex128,
    'complex256': np.complex256,
    'str': str,
    'None': type(None),
    'bytes': bytes,
}


def type_annot_to_spec(node: ast.AST):
    if isinstance(node, ast.Name):
        return dtypes[node.id]
    elif isinstance(node, ast.Slice):
        start = node.lower.value if node.lower else 0
        stop = node.upper.value if node.upper else -1
        step = node.step.value if node.step else 1
        s = slice(start, stop, step)
        return s
    elif isinstance(node, ast.Constant):
        return node.value
    elif isinstance(node, ast.Tuple):
        return tuple(type_annot_to_spec(n) for n in node.elts)
    elif isinstance(node, ast.Subscript):
        if isinstance(node.value, ast.Name):
            tfm = dict(list=List, set=Set, tuple=Tuple, ndarray=NDArray)
            if node.value.id not in tfm:
                raise Exception(f"Instantiation of undefined template '{node.value.id}'.")
            container = tfm[node.value.id]
            args = type_annot_to_spec(node.slice)
            if container is NDArray:
                elt_ty = args[0]
                if not isinstance(elt_ty, type):
                    raise Exception(f"Invalid type argument to template type ndarray; first argument is expected to be a type, got: {elt_ty} of type {type(elt_ty)}.")
                new_args = [elt_ty]
                for arg in args[1:]:
                    if isinstance(arg, int):
                        new_args.append(slice(0, arg, 1))
                    elif isinstance(arg, slice):
                        new_args.append(arg)
                    else:
                        raise Exception(f"Invalid type argument to template type ndarray; expected slice or int literal, got: {arg.__name__} of type {type(arg)}.")
                args = tuple(new_args)
            return container(args)
        else:
            raise Exception(f"Expected template type name, got '{node.value}'.")
    return node


class ExtractFunctionTypeAnnotations(ModuleAnalysis):
    def __init__(self: 'ExtractFunctionTypeAnnotations'):
        self.result = dict()
        self.update = False
        self.functions = set()
        ModuleAnalysis.__init__(self)

    def run(self, node):
        super(ModuleAnalysis, self).run(node)
        return spec.Spec(functions=self.result)

    def visit_FunctionDef(self: 'ExtractFunctionTypeAnnotations', fn: ast.FunctionDef) -> None:
        self.result[fn.name] = (tuple(type_annot_to_spec(arg.annotation) for arg in fn.args.args),)
