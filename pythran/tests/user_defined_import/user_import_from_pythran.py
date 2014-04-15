from user_import_from_pythran_main import bar
import user_import_from_pythran_main

def foo(a):
    return bar(a+42) + user_import_from_pythran_main.foo(a)
