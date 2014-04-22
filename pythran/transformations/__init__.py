"""The transformation submodule contains all the transformations passes offered
in Pythran.

This file is just for convenience and turns the import from

import transformations.xxxxx.xxxxx

into

import transformations.xxxxx
"""


from expand_builtins import ExpandBuiltins
from expand_imports import ExpandImports
from expand_import_all import ExpandImportAll
from extract_top_level_stmts import ExtractTopLevelStmts
from false_polymorphism import FalsePolymorphism
from normalize_compare import NormalizeCompare
from normalize_exception import NormalizeException
from normalize_identifiers import NormalizeIdentifiers
from normalize_method_calls import NormalizeMethodCalls
from normalize_return import NormalizeReturn
from normalize_tuples import NormalizeTuples
from remove_comprehension import RemoveComprehension
from remove_lambdas import RemoveLambdas
from remove_nested_functions import RemoveNestedFunctions
from unshadow_parameters import UnshadowParameters
