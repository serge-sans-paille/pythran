import unittest
import doctest

class TestDoctest(unittest.TestCase):

    modules = ('passes',)

    def test_package(self):
        import pythran
        failed, _ = doctest.testmod(pythran)
        self.assertEqual(failed, 0)

    def test_passes(self):
        from pythran import passes
        failed, _ = doctest.testmod(passes)
        self.assertEqual(failed, 0)

    def test_optimizations(self):
        from pythran import optimizations
        failed, _ = doctest.testmod(optimizations)
        self.assertEqual(failed, 0)

    def test_backend(self):
        from pythran import backend
        failed, _ = doctest.testmod(backend)
        self.assertEqual(failed, 0)

    def test_cxxtypes(self):
        from pythran import cxxtypes
        failed, _ = doctest.testmod(cxxtypes)
        self.assertEqual(failed, 0)

    #def test_typing(self):
    #    from pythran import typing
    #    failed, _ = doctest.testmod(typing)
    #    self.assertEqual(failed, 0)


if __name__ == '__main__':
    unittest.main()
