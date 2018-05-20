from .. csts import return_cst
from ..level.dummer import twice
#pythran export yummy()
def yummy():
    return twice(return_cst())
