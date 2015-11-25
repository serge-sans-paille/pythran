#ifndef PYTHONIC_INCLUDE_TYPES_EXCEPTIONS_HPP
#define PYTHONIC_INCLUDE_TYPES_EXCEPTIONS_HPP

#include "pythonic/include/types/str.hpp"
#include "pythonic/include/types/list.hpp"
#include "pythonic/include/types/attr.hpp"
#include "pythonic/include/__builtin__/str.hpp"

#include <stdexcept>

namespace pythonic
{

  namespace types
  {

    namespace BaseError
    {

      template <size_t I>
      struct Type {
        using type = str;
      };

      template <>
      struct Type<0> {
        using type = list<str>;
      };
    }

    class BaseException : public std::exception
    {
    public:
      BaseException(const BaseException &e);
      template <typename... Types>
      BaseException(str const &first, Types... types);
      BaseException();
      virtual ~BaseException() noexcept;
      list<str> args;

    protected:
      template <typename T, typename... Types>
      void init(T &first, Types... others);

      template <typename T>
      void init(T &first);
    };

// Use this to create a python exception class
#define CLASS_EXCEPTION_DECL(name, parent)                                     \
  class name : public parent                                                   \
  {                                                                            \
  public:                                                                      \
    name();                                                                    \
    name(const name &e);                                                       \
    template <class... Types>                                                  \
    name(str const &first, Types... types);                                    \
    virtual ~name() noexcept;                                                  \
  };

    CLASS_EXCEPTION_DECL(SystemExit, BaseException);
    CLASS_EXCEPTION_DECL(KeyboardInterrupt, BaseException);
    CLASS_EXCEPTION_DECL(GeneratorExit, BaseException);
    CLASS_EXCEPTION_DECL(Exception, BaseException);
    CLASS_EXCEPTION_DECL(StopIteration, Exception);
    CLASS_EXCEPTION_DECL(StandardError, Exception);
    CLASS_EXCEPTION_DECL(Warning, Exception);
    CLASS_EXCEPTION_DECL(BytesWarning, Warning);
    CLASS_EXCEPTION_DECL(UnicodeWarning, Warning);
    CLASS_EXCEPTION_DECL(ImportWarning, Warning);
    CLASS_EXCEPTION_DECL(FutureWarning, Warning);
    CLASS_EXCEPTION_DECL(UserWarning, Warning);
    CLASS_EXCEPTION_DECL(SyntaxWarning, Warning);
    CLASS_EXCEPTION_DECL(RuntimeWarning, Warning);
    CLASS_EXCEPTION_DECL(PendingDeprecationWarning, Warning);
    CLASS_EXCEPTION_DECL(DeprecationWarning, Warning);
    CLASS_EXCEPTION_DECL(BufferError, StandardError);
    CLASS_EXCEPTION_DECL(ArithmeticError, StandardError);
    CLASS_EXCEPTION_DECL(AssertionError, StandardError);
    CLASS_EXCEPTION_DECL(AttributeError, StandardError);
    CLASS_EXCEPTION_DECL(EnvironmentError, StandardError);
    CLASS_EXCEPTION_DECL(EOFError, StandardError);
    CLASS_EXCEPTION_DECL(ImportError, StandardError);
    CLASS_EXCEPTION_DECL(LookupError, StandardError);
    CLASS_EXCEPTION_DECL(MemoryError, StandardError);
    CLASS_EXCEPTION_DECL(NameError, StandardError);
    CLASS_EXCEPTION_DECL(ReferenceError, StandardError);
    CLASS_EXCEPTION_DECL(RuntimeError, StandardError);
    CLASS_EXCEPTION_DECL(SyntaxError, StandardError);
    CLASS_EXCEPTION_DECL(SystemError, StandardError);
    CLASS_EXCEPTION_DECL(TypeError, StandardError);
    CLASS_EXCEPTION_DECL(ValueError, StandardError);
    CLASS_EXCEPTION_DECL(FloatingPointError, ArithmeticError);
    CLASS_EXCEPTION_DECL(OverflowError, ArithmeticError);
    CLASS_EXCEPTION_DECL(ZeroDivisionError, ArithmeticError);
    CLASS_EXCEPTION_DECL(IOError, EnvironmentError);
    CLASS_EXCEPTION_DECL(OSError, EnvironmentError);
    CLASS_EXCEPTION_DECL(WindowsError, OSError);
    CLASS_EXCEPTION_DECL(VMSError, OSError);
    CLASS_EXCEPTION_DECL(IndexError, LookupError);
    CLASS_EXCEPTION_DECL(KeyError, LookupError);
    CLASS_EXCEPTION_DECL(UnboundLocalError, NameError);
    CLASS_EXCEPTION_DECL(NotImplementedError, RuntimeError);
    CLASS_EXCEPTION_DECL(IndentationError, SyntaxError);
    CLASS_EXCEPTION_DECL(TabError, IndentationError);
    CLASS_EXCEPTION_DECL(UnicodeError, ValueError);
  }
}

#include "pythonic/include/utils/functor.hpp"
#define PYTHONIC_EXCEPTION_DECL(name)                                          \
  template <typename... Types>                                                 \
  types::name name(Types... args);                                             \
                                                                               \
  DECLARE_FUNCTOR(pythonic::__builtin__, name);

/* pythran attribute system { */
#define DECLARE_EXCEPTION_GETATTR(name)                                        \
  namespace pythonic                                                           \
  {                                                                            \
    namespace types                                                            \
    {                                                                          \
      namespace __##name                                                       \
      {                                                                        \
                                                                               \
        template <int I>                                                       \
        struct getattr;                                                        \
        template <>                                                            \
        struct getattr<attr::ARGS> {                                           \
          none<list<str>> operator()(name const &e);                           \
        };                                                                     \
      }                                                                        \
    }                                                                          \
    namespace __builtin__                                                      \
    {                                                                          \
      template <int I>                                                         \
      auto getattr(types::name const &f)                                       \
          -> decltype(types::__##name::getattr<I>()(f));                       \
    }                                                                          \
  }

#define DECLARE_EXCEPTION_GETATTR_FULL(name)                                   \
  namespace pythonic                                                           \
  {                                                                            \
    namespace types                                                            \
    {                                                                          \
      namespace __##name                                                       \
      {                                                                        \
                                                                               \
        template <int I>                                                       \
        struct getattr;                                                        \
        template <>                                                            \
        struct getattr<attr::ARGS> {                                           \
          none<list<str>> operator()(name const &e);                           \
        };                                                                     \
        template <>                                                            \
        struct getattr<attr::ERRNO> {                                          \
          none<str> operator()(name const &e);                                 \
        };                                                                     \
        template <>                                                            \
        struct getattr<attr::STRERROR> {                                       \
          none<str> operator()(name const &e);                                 \
        };                                                                     \
        template <>                                                            \
        struct getattr<attr::FILENAME> {                                       \
          none<str> operator()(name const &e);                                 \
        };                                                                     \
      }                                                                        \
    }                                                                          \
    namespace __builtin__                                                      \
    {                                                                          \
      template <int I>                                                         \
      auto getattr(types::name const &f)                                       \
          -> decltype(types::__##name::getattr<I>()(f));                       \
    }                                                                          \
  }

DECLARE_EXCEPTION_GETATTR(BaseException);
DECLARE_EXCEPTION_GETATTR(SystemExit);
DECLARE_EXCEPTION_GETATTR(KeyboardInterrupt);
DECLARE_EXCEPTION_GETATTR(GeneratorExit);
DECLARE_EXCEPTION_GETATTR(Exception);
DECLARE_EXCEPTION_GETATTR(StopIteration);
DECLARE_EXCEPTION_GETATTR(StandardError);
DECLARE_EXCEPTION_GETATTR(Warning);
DECLARE_EXCEPTION_GETATTR(BytesWarning);
DECLARE_EXCEPTION_GETATTR(UnicodeWarning);
DECLARE_EXCEPTION_GETATTR(ImportWarning);
DECLARE_EXCEPTION_GETATTR(FutureWarning);
DECLARE_EXCEPTION_GETATTR(UserWarning);
DECLARE_EXCEPTION_GETATTR(SyntaxWarning);
DECLARE_EXCEPTION_GETATTR(RuntimeWarning);
DECLARE_EXCEPTION_GETATTR(PendingDeprecationWarning);
DECLARE_EXCEPTION_GETATTR(DeprecationWarning);
DECLARE_EXCEPTION_GETATTR(BufferError);
DECLARE_EXCEPTION_GETATTR(ArithmeticError);
DECLARE_EXCEPTION_GETATTR(AssertionError);
DECLARE_EXCEPTION_GETATTR(AttributeError);
DECLARE_EXCEPTION_GETATTR(EOFError);
DECLARE_EXCEPTION_GETATTR(ImportError);
DECLARE_EXCEPTION_GETATTR(LookupError);
DECLARE_EXCEPTION_GETATTR(MemoryError);
DECLARE_EXCEPTION_GETATTR(NameError);
DECLARE_EXCEPTION_GETATTR(ReferenceError);
DECLARE_EXCEPTION_GETATTR(RuntimeError);
DECLARE_EXCEPTION_GETATTR(SyntaxError);
DECLARE_EXCEPTION_GETATTR(SystemError);
DECLARE_EXCEPTION_GETATTR(TypeError);
DECLARE_EXCEPTION_GETATTR(ValueError);
DECLARE_EXCEPTION_GETATTR(FloatingPointError);
DECLARE_EXCEPTION_GETATTR(OverflowError);
DECLARE_EXCEPTION_GETATTR(ZeroDivisionError);
DECLARE_EXCEPTION_GETATTR(IndexError);
DECLARE_EXCEPTION_GETATTR(KeyError);
DECLARE_EXCEPTION_GETATTR(UnboundLocalError);
DECLARE_EXCEPTION_GETATTR(NotImplementedError);
DECLARE_EXCEPTION_GETATTR(IndentationError);
DECLARE_EXCEPTION_GETATTR(TabError);
DECLARE_EXCEPTION_GETATTR(UnicodeError);
DECLARE_EXCEPTION_GETATTR_FULL(IOError);
DECLARE_EXCEPTION_GETATTR_FULL(EnvironmentError);
DECLARE_EXCEPTION_GETATTR_FULL(OSError);

namespace pythonic
{

  namespace types
  {

    std::ostream &operator<<(std::ostream &o, BaseException const &e);

    /* @brief Convert EnvironmentError to a string.
     *
     * The number of arguments used when creating the EnvironmentError impact
     * the resulting "type" or formatting of the chain. We aim to mimic python
     * behavior of course:
     * - only one arg, then assume it can be converted to string,
     * - two args, then the first one is the errno, the next one a string,
     * - three args, like two args, adding "filename" as third one (after ':')
     * - four or more args, the "tuple" used to construct the exception
     *
     */
    std::ostream &operator<<(std::ostream &o, EnvironmentError const &e);
  }
}

/* } */

#endif
