from test_env import TestEnv

class TestSubmodules(TestEnv):

    def test_module_import(self):
        self.run_test('def module_import(l): import os; return os.path.join("lili", l)',
                      "mypath", module_import=[str])

    def test_submodule_import(self):
        self.run_test('def submodule_import(l): import os.path; return os.path.join("lili", l)',
                      "mypath", submodule_import=[str])

    def test_import_alias(self):
        self.run_test('def import_alias(l): import os.path as p; return p.join("lili", l)',
                      "mypath", import_alias=[str])

    def test_function_import(self):
        self.run_test('def function_import(l): from os.path import join; return join("lili", l)',
                      "mypath", function_import=[str])

    def test_function_import_alias(self):
        self.run_test('def function_import_alias(l): from os.path import join as j; return j("lili", l)',
                      "mypath", function_import_alias=[str])
