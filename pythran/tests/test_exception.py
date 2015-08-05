from test_env import TestEnv
import unittest

class TestException(TestEnv):

    def test_BaseException(self):
        self.run_test("def BaseException_():\n try: raise BaseException('a','b','c')\n except BaseException as e: return e.args", BaseException_=[])

    def test_SystemExit(self):
        self.run_test("def SystemExit_():\n try: raise SystemExit('a','b','c')\n except SystemExit as e: return e.args", SystemExit_=[])

    def test_KeyboardInterrupt(self):
        self.run_test("def KeyboardInterrupt_():\n try: raise KeyboardInterrupt('a','b','c')\n except KeyboardInterrupt as e: return e.args", KeyboardInterrupt_=[])

    def test_GeneratorExit(self):
        self.run_test("def GeneratorExit_():\n try: raise GeneratorExit('a','b','c')\n except GeneratorExit as e: return e.args", GeneratorExit_=[])

    def test_Exception(self):
        self.run_test("def Exception_():\n try: raise Exception('a','b','c')\n except Exception as e: return e.args", Exception_=[])

    def test_StopIteration(self):
        self.run_test("def StopIteration_():\n try: raise StopIteration('a','b','c')\n except StopIteration as e: return e.args", StopIteration_=[])

    def test_StandardError(self):
        self.run_test("def StandardError_():\n try: raise StandardError('a','b','c')\n except StandardError as e: return e.args", StandardError_=[])

    def test_Warning(self):
        self.run_test("def Warning_():\n try: raise Warning('a','b','c')\n except Warning as e: return e.args", Warning_=[])

    def test_BytesWarning(self):
        self.run_test("def BytesWarning_():\n try: raise BytesWarning('a','b','c')\n except BytesWarning as e: return e.args", BytesWarning_=[])

    def test_UnicodeWarning(self):
        self.run_test("def UnicodeWarning_():\n try: raise UnicodeWarning('a','b','c')\n except UnicodeWarning as e: return e.args", UnicodeWarning_=[])

    def test_ImportWarning(self):
        self.run_test("def ImportWarning_():\n try: raise ImportWarning('a','b','c')\n except ImportWarning as e: return e.args", ImportWarning_=[])

    def test_FutureWarning(self):
        self.run_test("def FutureWarning_():\n try: raise FutureWarning('a','b','c')\n except FutureWarning as e: return e.args", FutureWarning_=[])

    def test_UserWarning(self):
        self.run_test("def UserWarning_():\n try: raise UserWarning('a','b','c')\n except UserWarning as e: return e.args", UserWarning_=[])

    def test_SyntaxWarning(self):
        self.run_test("def SyntaxWarning_():\n try: raise SyntaxWarning('a','b','c')\n except SyntaxWarning as e: return e.args", SyntaxWarning_=[])

    def test_RuntimeWarning(self):
        self.run_test("def RuntimeWarning_():\n try: raise RuntimeWarning('a','b','c')\n except RuntimeWarning as e: return e.args", RuntimeWarning_=[])

    def test_PendingDeprecationWarning(self):
        self.run_test("def PendingDeprecationWarning_():\n try: raise PendingDeprecationWarning('a','b','c')\n except PendingDeprecationWarning as e: return e.args", PendingDeprecationWarning_=[])

    def test_DeprecationWarning(self):
        self.run_test("def DeprecationWarning_():\n try: raise DeprecationWarning('a','b','c')\n except DeprecationWarning as e: return e.args", DeprecationWarning_=[])

    def test_BufferError(self):
        self.run_test("def BufferError_():\n try: raise BufferError('a','b','c')\n except BufferError as e: return e.args", BufferError_=[])

    def test_ArithmeticError(self):
        self.run_test("def ArithmeticError_():\n try: raise ArithmeticError('a','b','c')\n except ArithmeticError as e: return e.args", ArithmeticError_=[])

    @unittest.skip("incompatible with py.test")
    def test_AssertionError(self):
        self.run_test("def AssertionError_():\n try: raise AssertionError('a','b','c')\n except AssertionError as e: return e.args", AssertionError_=[])

    def test_AttributeError(self):
        self.run_test("def AttributeError_():\n try: raise AttributeError('a','b','c')\n except AttributeError as e: return e.args", AttributeError_=[])

    def test_EnvironmentError4(self):
        self.run_test("def EnvironmentError4_():\n try: raise EnvironmentError('a','b','c','d')\n except EnvironmentError as e: return e.args", EnvironmentError4_=[])

    def test_EnvironmentError3(self):
        self.run_test("def EnvironmentError3_():\n try: raise EnvironmentError('a','b','c')\n except EnvironmentError as e: return e.args", EnvironmentError3_=[])

    def test_EnvironmentError2(self):
        self.run_test("def EnvironmentError2_():\n try: raise EnvironmentError('a','b')\n except EnvironmentError as e: return e.args", EnvironmentError2_=[])

    def test_EnvironmentError1(self):
        self.run_test("def EnvironmentError1_():\n try: raise EnvironmentError('a')\n except EnvironmentError as e: return e.args", EnvironmentError1_=[])

    def test_EOFError(self):
        self.run_test("def EOFError_():\n try: raise EOFError('a','b','c')\n except EOFError as e: return e.args", EOFError_=[])

    def test_ImportError(self):
        self.run_test("def ImportError_():\n try: raise ImportError('a','b','c')\n except ImportError as e: return e.args", ImportError_=[])

    def test_LookupError(self):
        self.run_test("def LookupError_():\n try: raise LookupError('a','b','c')\n except LookupError as e: return e.args", LookupError_=[])

    def test_MemoryError(self):
        self.run_test("def MemoryError_():\n try: raise MemoryError('a','b','c')\n except MemoryError as e: return e.args", MemoryError_=[])

    def test_NameError(self):
        self.run_test("def NameError_():\n try: raise NameError('a','b','c')\n except NameError as e: return e.args", NameError_=[])

    def test_ReferenceError(self):
        self.run_test("def ReferenceError_():\n try: raise ReferenceError('a','b','c')\n except ReferenceError as e: return e.args", ReferenceError_=[])

    def test_RuntimeError(self):
        self.run_test("def RuntimeError_():\n try: raise RuntimeError('a','b','c')\n except RuntimeError as e: return e.args", RuntimeError_=[])

    def test_SyntaxError(self):
        self.run_test("def SyntaxError_():\n try: raise SyntaxError('a','b','c')\n except SyntaxError as e: return e.args", SyntaxError_=[])

    def test_SystemError(self):
        self.run_test("def SystemError_():\n try: raise SystemError('a','b','c')\n except SystemError as e: return e.args", SystemError_=[])

    def test_TypeError(self):
        self.run_test("def TypeError_():\n try: raise TypeError('a','b','c')\n except TypeError as e: return e.args", TypeError_=[])

    def test_ValueError(self):
        self.run_test("def ValueError_():\n try: raise ValueError('a','b','c')\n except ValueError as e: return e.args", ValueError_=[])

    def test_FloatingPointError(self):
        self.run_test("def FloatingPointError_():\n try: raise FloatingPointError('a','b','c')\n except FloatingPointError as e: return e.args", FloatingPointError_=[])

    def test_OverflowError(self):
        self.run_test("def OverflowError_():\n try: raise OverflowError('a','b','c')\n except OverflowError as e: return e.args", OverflowError_=[])

    def test_ZeroDivisionError(self):
        self.run_test("def ZeroDivisionError_():\n try: raise ZeroDivisionError('a','b','c')\n except ZeroDivisionError as e:\n  return e.args", ZeroDivisionError_=[])

    def test_IOError(self):
        self.run_test("def IOError_():\n try: raise IOError('a','b','c')\n except IOError as e: return e.args", IOError_=[])

    def test_OSError(self):
        self.run_test("def OSError_():\n try: raise OSError('a','b','c')\n except OSError as e: return e.args", OSError_=[])

    def test_IndexError(self):
        self.run_test("def IndexError_():\n try: raise IndexError('a','b','c')\n except IndexError as e: return e.args", IndexError_=[])

    def test_KeyError(self):
        self.run_test("def KeyError_():\n try: raise KeyError('a','b','c')\n except KeyError as e: return e.args", KeyError_=[])

    def test_UnboundLocalError(self):
        self.run_test("def UnboundLocalError_():\n try: raise UnboundLocalError('a','b','c')\n except UnboundLocalError as e: return e.args", UnboundLocalError_=[])

    def test_NotImplementedError(self):
        self.run_test("def NotImplementedError_():\n try: raise NotImplementedError('a','b','c')\n except NotImplementedError as e: return e.args", NotImplementedError_=[])

    def test_IndentationError(self):
        self.run_test("def IndentationError_():\n try: raise IndentationError('a','b','c')\n except IndentationError as e: return e.args", IndentationError_=[])

    def test_TabError(self):
        self.run_test("def TabError_():\n try: raise TabError('a','b','c')\n except TabError as e: return e.args", TabError_=[])

    def test_UnicodeError(self):
        self.run_test("def UnicodeError_():\n try: raise UnicodeError('a','b','c')\n except UnicodeError as e: return e.args", UnicodeError_=[])

    def test_multiple_exception(self):
        self.run_test("def multiple_exception_():\n try:\n  raise OverflowError('a','b','c')\n except IOError as e:\n  a=2 ; print a ; return e.args\n except OverflowError as e:\n  return e.args", multiple_exception_=[])

    def test_multiple_tuple_exception(self):
        self.run_test("def multiple_tuple_exception_():\n try:\n  raise OverflowError('a','b','c')\n except (IOError, OSError):\n  a=3;print a\n except OverflowError as e:\n  return e.args", multiple_tuple_exception_=[])

    def test_reraise_exception(self):
        self.run_test("def reraise_exception_():\n try:\n  raise OverflowError('a','b','c')\n except IOError:\n  raise\n except:  return 'ok'", reraise_exception_=[])

    def test_raiseinst_exception(self):
        self.run_test("def raiseinst_exception_():\n try:\n  raise OverflowError, ('a','b','c')\n except OverflowError as e:\n  return e.args", raiseinst_exception_=[])

    def test_else2_exception(self):
        self.run_test("def else2_exception_():\n try:\n  raise 1\n  return 0,'bad'\n except:\n  a=2\n else:\n  return 0,'bad2'\n return a,'ok'", else2_exception_=[])

    def test_else_exception(self):
        self.run_test("def else_exception_():\n try:\n  a=2\n except:\n  return 0,'bad'\n else:\n  return a,'ok'\n return 0,'bad2'", else_exception_=[])

    def test_enverror_exception(self):
        self.run_test("def enverror_exception_():\n try:\n  raise EnvironmentError('a','b','c')\n except EnvironmentError as e:\n  return (e.errno,e.strerror,e.filename)", enverror_exception_=[])

    def test_finally_exception(self):
        self.run_test("def finally_exception_():\n try:\n  a=2\n except:\n  return 0,'bad'\n finally:\n  return a,'good'", finally_exception_=[])

    def test_finally2_exception(self):
        self.run_test("def finally2_exception_():\n try:\n  raise 1\n  return 0,'bad'\n except:\n  a=2\n finally:\n  return a,'good'", finally2_exception_=[])

    def test_str1_exception(self):
        self.run_test("def str1_exception_():\n try:\n  raise EnvironmentError('a')\n except EnvironmentError as e:\n  return str(e)", str1_exception_=[])

    def test_str2_exception(self):
        self.run_test("def str2_exception_():\n try:\n  raise EnvironmentError('a','b')\n except EnvironmentError as e:\n  return str(e)", str2_exception_=[])

    def test_str3_exception(self):
        self.run_test("def str3_exception_():\n try:\n  raise EnvironmentError('a','b','c')\n except EnvironmentError as e:\n  return str(e)", str3_exception_=[])

    def test_str4_exception(self):
        self.run_test("def str4_exception_():\n try:\n  raise EnvironmentError('a','b','c','d')\n except EnvironmentError as e:\n  return str(e)", str4_exception_=[])

    def test_str5_exception(self):
        self.run_test("def str5_exception_():\n try:\n  raise EnvironmentError('a','b','c','d','e')\n except EnvironmentError as e:\n  return str(e)", str5_exception_=[])

    def test_no_msg_exception(self):
        self.run_test("def no_msg_exception_():\n try: raise IndexError()\n except IndexError as e: return e.args", no_msg_exception_=[])

# test if exception translators are registered in pythran

    def test_BaseException_register(self):
        self.run_test("def BaseException_register(): raise BaseException('abc')", BaseException_register=[], check_exception=True)

    def test_SystemExit_register(self):
        self.run_test("def SystemExit_register():\n raise SystemExit('a','b','c')", SystemExit_register=[], check_exception=True)

    def test_KeyboardInterrupt_register(self):
        self.run_test("def KeyboardInterrupt_register():\n raise KeyboardInterrupt('a','b','c')", KeyboardInterrupt_register=[], check_exception=True)

    def test_GeneratorExit_register(self):
        self.run_test("def GeneratorExit_register():\n raise GeneratorExit('a','b','c')", GeneratorExit_register=[], check_exception=True)

    def test_Exception_register(self):
        self.run_test("def Exception_register():\n raise Exception('a','b','c')", Exception_register=[], check_exception=True)

    def test_StopIteration_register(self):
        self.run_test("def StopIteration_register():\n raise StopIteration('a','b','c')", StopIteration_register=[], check_exception=True)

    def test_StandardError_register(self):
        self.run_test("def StandardError_register():\n raise StandardError('a','b','c')", StandardError_register=[], check_exception=True)

    def test_Warning_register(self):
        self.run_test("def Warning_register():\n raise Warning('a','b','c')", Warning_register=[], check_exception=True)

    def test_BytesWarning_register(self):
        self.run_test("def BytesWarning_register():\n raise BytesWarning('a','b','c')", BytesWarning_register=[], check_exception=True)

    def test_UnicodeWarning_register(self):
        self.run_test("def UnicodeWarning_register():\n raise UnicodeWarning('a','b','c')", UnicodeWarning_register=[], check_exception=True)

    def test_ImportWarning_register(self):
        self.run_test("def ImportWarning_register():\n raise ImportWarning('a','b','c')", ImportWarning_register=[], check_exception=True)

    def test_FutureWarning_register(self):
        self.run_test("def FutureWarning_register():\n raise FutureWarning('a','b','c')", FutureWarning_register=[], check_exception=True)

    def test_UserWarning_register(self):
        self.run_test("def UserWarning_register():\n raise UserWarning('a','b','c')", UserWarning_register=[], check_exception=True)

    def test_SyntaxWarning_register(self):
        self.run_test("def SyntaxWarning_register():\n raise SyntaxWarning('a','b','c')", SyntaxWarning_register=[], check_exception=True)

    def test_RuntimeWarning_register(self):
        self.run_test("def RuntimeWarning_register():\n raise RuntimeWarning('a','b','c')", RuntimeWarning_register=[], check_exception=True)

    def test_PendingDeprecationWarning_register(self):
        self.run_test("def PendingDeprecationWarning_register():\n raise PendingDeprecationWarning('a','b','c')", PendingDeprecationWarning_register=[], check_exception=True)

    def test_DeprecationWarning_register(self):
        self.run_test("def DeprecationWarning_register():\n raise DeprecationWarning('a','b','c')", DeprecationWarning_register=[], check_exception=True)

    def test_BufferError_register(self):
        self.run_test("def BufferError_register():\n raise BufferError('a','b','c')", BufferError_register=[], check_exception=True)

    def test_ArithmeticError_register(self):
        self.run_test("def ArithmeticError_register():\n raise ArithmeticError('a','b','c')", ArithmeticError_register=[], check_exception=True)

    @unittest.skip("incompatible with py.test")
    def test_AssertionError_register(self):
        self.run_test("def AssertionError_register():\n raise AssertionError('a','b','c')", AssertionError_register=[], check_exception=True)

    def test_AttributeError_register(self):
        self.run_test("def AttributeError_register():\n raise AttributeError('a','b','c')", AttributeError_register=[], check_exception=True)

    def test_EnvironmentError4_register(self):
        self.run_test("def EnvironmentError4_register():\n raise EnvironmentError('a','b','c','d')", EnvironmentError4_register=[], check_exception=True)

    def test_EnvironmentError3_register(self):
        self.run_test("def EnvironmentError3_register():\n raise EnvironmentError('a','b','c')", EnvironmentError3_register=[], check_exception=True)

    def test_EnvironmentError2_register(self):
        self.run_test("def EnvironmentError2_register():\n raise EnvironmentError('a','b')", EnvironmentError2_register=[], check_exception=True)

    def test_EnvironmentError1_register(self):
        self.run_test("def EnvironmentError1_register():\n raise EnvironmentError('a')", EnvironmentError1_register=[], check_exception=True)

    def test_EOFError_register(self):
        self.run_test("def EOFError_register():\n raise EOFError('a','b','c')", EOFError_register=[], check_exception=True)

    def test_ImportError_register(self):
        self.run_test("def ImportError_register():\n raise ImportError('a','b','c')", ImportError_register=[], check_exception=True)

    def test_LookupError_register(self):
        self.run_test("def LookupError_register():\n raise LookupError('a','b','c')", LookupError_register=[], check_exception=True)

    def test_MemoryError_register(self):
        self.run_test("def MemoryError_register():\n raise MemoryError('a','b','c')", MemoryError_register=[], check_exception=True)

    def test_NameError_register(self):
        self.run_test("def NameError_register():\n raise NameError('a','b','c')", NameError_register=[], check_exception=True)

    def test_ReferenceError_register(self):
        self.run_test("def ReferenceError_register():\n raise ReferenceError('a','b','c')", ReferenceError_register=[], check_exception=True)

    def test_RuntimeError_register(self):
        self.run_test("def RuntimeError_register():\n raise RuntimeError('a','b','c')", RuntimeError_register=[], check_exception=True)

    def test_SyntaxError_register(self):
        self.run_test("def SyntaxError_register():\n raise SyntaxError('a','b','c')", SyntaxError_register=[], check_exception=True)

    def test_SystemError_register(self):
        self.run_test("def SystemError_register():\n raise SystemError('a','b','c')", SystemError_register=[], check_exception=True)

    def test_TypeError_register(self):
        self.run_test("def TypeError_register():\n raise TypeError('a','b','c')", TypeError_register=[], check_exception=True)

    def test_ValueError_register(self):
        self.run_test("def ValueError_register():\n raise ValueError('a','b','c')", ValueError_register=[], check_exception=True)

    def test_FloatingPointError_register(self):
        self.run_test("def FloatingPointError_register():\n raise FloatingPointError('a','b','c')", FloatingPointError_register=[], check_exception=True)

    def test_OverflowError_register(self):
        self.run_test("def OverflowError_register():\n raise OverflowError('a','b','c')", OverflowError_register=[], check_exception=True)

    def test_ZeroDivisionError_register(self):
        self.run_test("def ZeroDivisionError_register():\n raise ZeroDivisionError('a','b','c')", ZeroDivisionError_register=[], check_exception=True)

    def test_IOError_register(self):
        self.run_test("def IOError_register():\n raise IOError('a','b','c')", IOError_register=[], check_exception=True)

    def test_OSError_register(self):
        self.run_test("def OSError_register():\n raise OSError('a','b','c')", OSError_register=[], check_exception=True)

    def test_IndexError_register(self):
        self.run_test("def IndexError_register():\n raise IndexError('a','b','c')", IndexError_register=[], check_exception=True)

    def test_KeyError_register(self):
        self.run_test("def KeyError_register():\n raise KeyError('a','b','c')", KeyError_register=[], check_exception=True)

    def test_UnboundLocalError_register(self):
        self.run_test("def UnboundLocalError_register():\n raise UnboundLocalError('a','b','c')", UnboundLocalError_register=[], check_exception=True)

    def test_NotImplementedError_register(self):
        self.run_test("def NotImplementedError_register():\n raise NotImplementedError('a','b','c')", NotImplementedError_register=[], check_exception=True)

    def test_IndentationError_register(self):
        self.run_test("def IndentationError_register():\n raise IndentationError('a','b','c')", IndentationError_register=[], check_exception=True)

    def test_TabError_register(self):
        self.run_test("def TabError_register():\n raise TabError('a','b','c')", TabError_register=[], check_exception=True)

    def test_UnicodeError_register(self):
        self.run_test("def UnicodeError_register():\n raise UnicodeError('a','b','c')", UnicodeError_register=[], check_exception=True)

    def test_multiple_exception_register(self):
        self.run_test("def multiple_exception_register():\n raise OverflowError('a','b','c')", multiple_exception_register=[], check_exception=True)

    def test_multiple_tuple_exception_register(self):
        self.run_test("def multiple_tuple_exception_register():\n raise OverflowError('a','b','c')", multiple_tuple_exception_register=[], check_exception=True)

    def test_reraise_exception_register(self):
        self.run_test("def reraise_exception_register():\n raise OverflowError('a','b','c')", reraise_exception_register=[], check_exception=True)

    def test_raiseinst_exception_register(self):
        self.run_test("def raiseinst_exception_register():\n raise OverflowError, ('a','b','c')", raiseinst_exception_register=[], check_exception=True)

    def test_enverror_exception_register(self):
        self.run_test("def enverror_exception_register():\n raise EnvironmentError('a','b','c')", enverror_exception_register=[], check_exception=True)

    def test_str1_exception_register(self):
        self.run_test("def str1_exception_register():\n raise EnvironmentError('a')", str1_exception_register=[], check_exception=True)

    def test_str2_exception_register(self):
        self.run_test("def str2_exception_register():\n raise EnvironmentError('a','b')", str2_exception_register=[], check_exception=True)

    def test_str3_exception_register(self):
        self.run_test("def str3_exception_register():\n raise EnvironmentError('a','b','c')", str3_exception_register=[], check_exception=True)

    def test_str4_exception_register(self):
        self.run_test("def str4_exception_register():\n raise EnvironmentError('a','b','c','d')", str4_exception_register=[], check_exception=True)

    def test_str5_exception_register(self):
        self.run_test("def str5_exception_register():\n raise EnvironmentError('a','b','c','d','e')", str5_exception_register=[], check_exception=True)

    def test_no_msg_exception_register(self):
        self.run_test("def no_msg_exception_register():\n raise IndexError()", no_msg_exception_register=[], check_exception=True)
