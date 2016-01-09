"""
This submodule contains all the transformations passes offered in Pythran.

This file is just for convenience and turns the import from

import transformations.xxxxx.xxxxx

into

import transformations.xxxxx
"""


from .expand_builtins import ExpandBuiltins
from .expand_globals import ExpandGlobals
from .expand_import_all import ExpandImportAll
from .expand_imports import ExpandImports
from .extract_doc_strings import ExtractDocStrings
from .false_polymorphism import FalsePolymorphism
from .handle_import import HandleImport
from .normalize_compare import NormalizeCompare
from .normalize_exception import NormalizeException
from .normalize_identifiers import NormalizeIdentifiers
from .normalize_method_calls import NormalizeMethodCalls
from .normalize_return import NormalizeReturn
from .normalize_tuples import NormalizeTuples
from .remove_comprehension import RemoveComprehension
from .remove_lambdas import RemoveLambdas
from .remove_nested_functions import RemoveNestedFunctions
from .unshadow_parameters import UnshadowParameters
from .remove_named_arguments import RemoveNamedArguments
