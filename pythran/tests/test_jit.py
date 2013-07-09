import unittest
import pythran


@pythran.jit
def foo(myarg1, myarg2):
    v = myarg1+myarg2
    return v


class TestJit(unittest.TestCase):

    def call_foo(self, func, n):
        for i in range(n):
            assert(func(10, 10) == 20)
            assert(func(1.3, 5) == 6.3)
            assert(func(5, 1.3) == 6.3)
            assert(func(1.5, 2.1) == 3.6)
            assert(func("Hello ", "World") == "Hello World")

    def test_simple_jit(self):
        n = 10

        foo.clear_cache()  # Ensure to start from scratch and force compilation
        self.call_foo(foo, n)
        assert(foo.stats.called == 5*n)
        assert(foo.stats.compiled == 5)
        assert(foo.stats.loaded_from_disk == 0)

        # Reload the JIT, but don't clear the cache.
        bar = pythran.jit(foo.func)
        self.call_foo(bar, n)
        assert(bar.stats.called == 5*n)
        assert(bar.stats.compiled == 0)
        assert(bar.stats.loaded_from_disk == 5)


if __name__ == '__main__':
    # Uncomment to debug :)
    #import logging
    #logging.basicConfig(format='%(levelname)s %(name)s: %(message)s',
    #                    level=logging.DEBUG)
    unittest.main()
