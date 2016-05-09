"""The analyses submodule contains all the analyses passes offered in Pythran.

This file is just for convenience and turns the import from

import analyses.foo.Foo

into

import analyses.Foo
"""

from .aliases import Aliases, StrictAliases
from .ancestors import Ancestors
from .argument_effects import ArgumentEffects
from .argument_read_once import ArgumentReadOnce
from .ast_matcher import ASTMatcher, AST_any, AST_or, Placeholder, Check
from .bound_expressions import BoundExpressions
from .cfg import CFG
from .constant_expressions import ConstantExpressions
from .extended_syntax_check import ExtendedSyntaxCheck
from .dependencies import Dependencies
from .global_declarations import GlobalDeclarations
from .global_effects import GlobalEffects
from .globals_analysis import Globals
from .has_break import HasBreak
from .has_continue import HasContinue
from .identifiers import Identifiers
from .imported_ids import ImportedIds
from .inlinable import Inlinable
from .is_assigned import IsAssigned
from .lazyness_analysis import LazynessAnalysis
from .literals import Literals
from .local_declarations import LocalNodeDeclarations, LocalNameDeclarations
from .locals_analysis import Locals
from .node_count import NodeCount
from .optimizable_comprehension import OptimizableComprehension
from .ordered_global_declarations import OrderedGlobalDeclarations
from .parallel_maps import ParallelMaps
from .range_values import RangeValues
from .potential_iterator import PotentialIterator
from .pure_expressions import PureExpressions
from .scope import Scope
from .use_def_chain import UseDefChain
from .use_omp import UseOMP
from .yield_points import YieldPoints
