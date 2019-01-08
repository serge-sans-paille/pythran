import builtins_in_imported
from builtins_in_imported import dint


#pythran export entry()
#runas entry()
def entry():
    return dint(), builtins_in_imported.dint()
