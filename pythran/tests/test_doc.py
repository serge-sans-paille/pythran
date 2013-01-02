import unittest
import doctest

class TestDoctest(unittest.TestCase):

    def test_package(self):
        import pythran
        failed, _ = doctest.testmod(pythran)
        self.assertEqual(failed, 0)

    #def test_typing(self):
    #    from pythran import typing
    #    failed, _ = doctest.testmod(typing)
    #    self.assertEqual(failed, 0)




if __name__ == '__main__':
    unittest.main()
