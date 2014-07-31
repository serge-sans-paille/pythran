from test_env import TestEnv


@TestEnv.module
class TestOs(TestEnv):

    def test_os_path(self):
        self.run_test('def os_path(l): import os; return os.path.join(l)',
                      "mypath", os_path=[str])

    def test_os_path2(self):
        self.run_test('def os_path2(l): import os; return os.path.join("lili", l)',
                      "mypath", os_path2=[str])

    def test_os_path3(self):
        self.run_test('def os_path3(l): import os; return os.path.join("lili", l)',
                      "/mypath", os_path3=[str])

    def test_os_path4(self):
        self.run_test('def os_path4(l): import os; return os.path.join("lili/", l)',
                      "mypath", os_path4=[str])

    def test_os_path5(self):
        self.run_test('def os_path5(l): import os; return os.path.join("", l)',
                      "mypath", os_path5=[str])
