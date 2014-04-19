"""The optimisations submodule contains all the optimisations passes offered
in Pythran.

This file is just for convenience and turns the import from

import optimisations.xxxxx.xxxxx

into

import optimisations.xxxxx
"""

from constant_folding import ConstantFolding
from dead_code_elimination import DeadCodeElimination
from forward_substitution import ForwardSubstitution
from gen_exp_to_imap import GenExpToImap
from iter_transformation import IterTransformation
from list_comp_to_genexp import ListCompToGenexp
from list_comp_to_map import ListCompToMap
from loop_full_unrolling import LoopFullUnrolling
from pow2 import Pow2
