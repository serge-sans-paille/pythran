#pythran export entry()
#runas entry()
import simple_case_import

def forward(a):
    return simple_case_import.imported(a)

def entry():
    return forward(1)
