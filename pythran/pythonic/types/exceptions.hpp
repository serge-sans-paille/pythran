#ifndef PYTHONIC_TYPES_EXCEPTIONS_HPP
#define PYTHONIC_TYPES_EXCEPTIONS_HPP

#include "pythonic/types/str.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/attr.hpp"
#include "pythonic/__builtin__/str.hpp"

#include <stdexcept>

namespace pythonic {

    namespace types {
        namespace BaseError{
            template<size_t I>
                struct Type
                {
                    typedef str type;
                };

            template<>
                struct Type<0>
                {
                    typedef list<str> type;
                };
        }
        class BaseException: public std::exception
        {
            public:
                BaseException(const BaseException &e) : args(e.args){}
                template<typename ... Types>
                    BaseException(str const& first,Types ... types) { args = empty_list() ; init(first, types ...);}
                BaseException() { args = empty_list();}
                virtual ~BaseException() noexcept {}
                list<str> args;
            protected:
                template<typename T, typename ... Types>
                    void init(T& first, Types ... others){ args.push_back(first); init(others ...);}
                template<typename T>
                    void init(T& first){args.push_back(first);}
        };



        // Use this to create a python exception class
#define CLASS_EXCEPTION(name,parent) \
        class name:public parent \
        { \
            public: \
                    name(const name& e):parent(e){} \
            template<class ... Types> \
            name(str const& first, Types ... types): parent(first, types ...){} \
            name():parent(){} \
            virtual ~name() noexcept {} \
        };

        CLASS_EXCEPTION(SystemExit,BaseException);
        CLASS_EXCEPTION(KeyboardInterrupt,BaseException);
        CLASS_EXCEPTION(GeneratorExit,BaseException);
        CLASS_EXCEPTION(Exception,BaseException);
        CLASS_EXCEPTION(StopIteration,Exception);
        CLASS_EXCEPTION(StandardError,Exception);
        CLASS_EXCEPTION(Warning,Exception);
        CLASS_EXCEPTION(BytesWarning,Warning);
        CLASS_EXCEPTION(UnicodeWarning,Warning);
        CLASS_EXCEPTION(ImportWarning,Warning);
        CLASS_EXCEPTION(FutureWarning,Warning);
        CLASS_EXCEPTION(UserWarning,Warning);
        CLASS_EXCEPTION(SyntaxWarning,Warning);
        CLASS_EXCEPTION(RuntimeWarning,Warning);
        CLASS_EXCEPTION(PendingDeprecationWarning,Warning);
        CLASS_EXCEPTION(DeprecationWarning,Warning);
        CLASS_EXCEPTION(BufferError,StandardError);
        CLASS_EXCEPTION(ArithmeticError,StandardError);
        CLASS_EXCEPTION(AssertionError,StandardError);
        CLASS_EXCEPTION(AttributeError,StandardError);
        CLASS_EXCEPTION(EnvironmentError,StandardError);
        CLASS_EXCEPTION(EOFError,StandardError);
        CLASS_EXCEPTION(ImportError,StandardError);
        CLASS_EXCEPTION(LookupError,StandardError);
        CLASS_EXCEPTION(MemoryError,StandardError);
        CLASS_EXCEPTION(NameError,StandardError);
        CLASS_EXCEPTION(ReferenceError,StandardError);
        CLASS_EXCEPTION(RuntimeError,StandardError);
        CLASS_EXCEPTION(SyntaxError,StandardError);
        CLASS_EXCEPTION(SystemError,StandardError);
        CLASS_EXCEPTION(TypeError,StandardError);
        CLASS_EXCEPTION(ValueError,StandardError);
        CLASS_EXCEPTION(FloatingPointError,ArithmeticError);
        CLASS_EXCEPTION(OverflowError,ArithmeticError);
        CLASS_EXCEPTION(ZeroDivisionError,ArithmeticError);
        CLASS_EXCEPTION(IOError,EnvironmentError);
        CLASS_EXCEPTION(OSError,EnvironmentError);
        CLASS_EXCEPTION(WindowsError,OSError);
        CLASS_EXCEPTION(VMSError,OSError);
        CLASS_EXCEPTION(IndexError,LookupError);
        CLASS_EXCEPTION(KeyError,LookupError);
        CLASS_EXCEPTION(UnboundLocalError,NameError);
        CLASS_EXCEPTION(NotImplementedError,RuntimeError);
        CLASS_EXCEPTION(IndentationError,SyntaxError);
        CLASS_EXCEPTION(TabError,IndentationError);
        CLASS_EXCEPTION(UnicodeError,ValueError);

    }

}

#include "pythonic/utils/proxy.hpp"
#define PYTHONIC_EXCEPTION(name)\
    template<typename ... Types>\
types::name name(Types ... args) {\
    return types::name(args ...);\
}\
\
PROXY(pythonic::__builtin__, name);\

/* pythran attribute system { */
#define DECLARE_EXCEPTION_GETATTR(name)\
    namespace pythonic {\
        namespace types {\
            namespace __##name {\
                \
                template <int I> struct getattr;\
                template <> struct getattr<attr::ARGS> {\
                    none<list<str>> operator()(name const& e) {\
                        return e.args;\
                    }\
                };\
            }\
        }\
        namespace __builtin__ {\
            template<int I>\
            auto getattr(types::name const& f) -> decltype(types::__##name::getattr<I>()(f)) {\
                return types::__##name::getattr<I>()(f);\
            }\
        }\
    }

#define DECLARE_EXCEPTION_GETATTR_FULL(name)\
    namespace pythonic {\
        namespace types {\
            namespace __##name {\
                \
                template <int I> struct getattr;\
                template <> struct getattr<attr::ARGS> {\
                    none<list<str>> operator()(name const& e) {\
                        if (e.args.size()>3 || e.args.size()<2)\
                        return e.args;\
                        else\
                        return list<str>(e.args.begin(), e.args.begin()+2);\
                    }\
                };\
                template <> struct getattr<attr::ERRNO> {\
                    none<str> operator()(name const& e) {\
                        if (e.args.size()>3 || e.args.size()<2)\
                        return __builtin__::None;\
                        else\
                        return e.args[0];\
                    }\
                };\
                template <> struct getattr<attr::STRERROR> {\
                    none<str> operator()(name const& e) {\
                        if (e.args.size()>3 || e.args.size()<2)\
                        return __builtin__::None;\
                        else\
                        return e.args[1];\
                    }\
                };\
                template <> struct getattr<attr::FILENAME> {\
                    none<str> operator()(name const& e) {\
                        if (e.args.size()!=3)\
                        return __builtin__::None;\
                        else\
                        return e.args[2];\
                    }\
                };\
            }\
        }\
        namespace __builtin__ {\
            template<int I>\
                auto getattr(types::name const& f) -> decltype(types::__##name::getattr<I>()(f)) {\
                    return types::__##name::getattr<I>()(f);\
                }\
        }\
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

#ifdef __VMS
REGISTER_EXCEPTION_TRANSLATOR(VMSError);
#endif

#ifdef MS_WINDOWS
REGISTER_EXCEPTION_TRANSLATOR(WindowsError);
#endif

namespace pythonic {

    namespace types {

        std::ostream& operator<<(std::ostream& o, BaseException const & e)
        {
            return o << e.args;
        }

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
        std::ostream& operator<<(std::ostream& o, EnvironmentError const & e)
        {
            if(e.args.size()==1)
                return o << e.args[0];
            if(e.args.size()==2)
                return o << "[Errno " << e.args[0] << "] " << e.args[1];
            else if(e.args.size()==3)
                return o << "[Errno " << e.args[0] << "] " << e.args[1] << ": '" << e.args[2] << "'";
            else {
                // Generate "('a', 'b', 'c', 'd') if a,b,c, and d are in e.args
                std::string listsep = "";
                o << "(";
                for(auto arg : e.args) {
                    o << listsep << "'" << arg << "'";
                    listsep=", ";
                }
                o << ")";
                return o;
            }
        }

    }
}

/* } */
#ifdef ENABLE_PYTHON_MODULE
#define REGISTER_EXCEPTION_TRANSLATOR(name) \
    void translate_##name(types::name const& e) { PyErr_SetString(PyExc_##name, __builtin__::str(e.args).c_str()); }
namespace pythonic {
    REGISTER_EXCEPTION_TRANSLATOR(BaseException);
    REGISTER_EXCEPTION_TRANSLATOR(SystemExit);
    REGISTER_EXCEPTION_TRANSLATOR(KeyboardInterrupt);
    REGISTER_EXCEPTION_TRANSLATOR(GeneratorExit);
    REGISTER_EXCEPTION_TRANSLATOR(Exception);
    REGISTER_EXCEPTION_TRANSLATOR(StopIteration);
    REGISTER_EXCEPTION_TRANSLATOR(StandardError);
    REGISTER_EXCEPTION_TRANSLATOR(Warning);
    REGISTER_EXCEPTION_TRANSLATOR(BytesWarning);
    REGISTER_EXCEPTION_TRANSLATOR(UnicodeWarning);
    REGISTER_EXCEPTION_TRANSLATOR(ImportWarning);
    REGISTER_EXCEPTION_TRANSLATOR(FutureWarning);
    REGISTER_EXCEPTION_TRANSLATOR(UserWarning);
    REGISTER_EXCEPTION_TRANSLATOR(SyntaxWarning);
    REGISTER_EXCEPTION_TRANSLATOR(RuntimeWarning);
    REGISTER_EXCEPTION_TRANSLATOR(PendingDeprecationWarning);
    REGISTER_EXCEPTION_TRANSLATOR(DeprecationWarning);
    REGISTER_EXCEPTION_TRANSLATOR(BufferError);
    REGISTER_EXCEPTION_TRANSLATOR(ArithmeticError);
    REGISTER_EXCEPTION_TRANSLATOR(AssertionError);
    REGISTER_EXCEPTION_TRANSLATOR(AttributeError);
    REGISTER_EXCEPTION_TRANSLATOR(EOFError);
    REGISTER_EXCEPTION_TRANSLATOR(ImportError);
    REGISTER_EXCEPTION_TRANSLATOR(LookupError);
    REGISTER_EXCEPTION_TRANSLATOR(MemoryError);
    REGISTER_EXCEPTION_TRANSLATOR(NameError);
    REGISTER_EXCEPTION_TRANSLATOR(ReferenceError);
    REGISTER_EXCEPTION_TRANSLATOR(RuntimeError);
    REGISTER_EXCEPTION_TRANSLATOR(SyntaxError);
    REGISTER_EXCEPTION_TRANSLATOR(SystemError);
    REGISTER_EXCEPTION_TRANSLATOR(TypeError);
    REGISTER_EXCEPTION_TRANSLATOR(ValueError);
    REGISTER_EXCEPTION_TRANSLATOR(FloatingPointError);
    REGISTER_EXCEPTION_TRANSLATOR(OverflowError);
    REGISTER_EXCEPTION_TRANSLATOR(ZeroDivisionError);
    REGISTER_EXCEPTION_TRANSLATOR(IndexError);
    REGISTER_EXCEPTION_TRANSLATOR(KeyError);
    REGISTER_EXCEPTION_TRANSLATOR(UnboundLocalError);
    REGISTER_EXCEPTION_TRANSLATOR(NotImplementedError);
    REGISTER_EXCEPTION_TRANSLATOR(IndentationError);
    REGISTER_EXCEPTION_TRANSLATOR(TabError);
    REGISTER_EXCEPTION_TRANSLATOR(UnicodeError);
    REGISTER_EXCEPTION_TRANSLATOR(IOError);
    REGISTER_EXCEPTION_TRANSLATOR(EnvironmentError);
    REGISTER_EXCEPTION_TRANSLATOR(OSError);

#ifdef __VMS
    REGISTER_EXCEPTION_TRANSLATOR(VMSError);
#endif

#ifdef MS_WINDOWS
    REGISTER_EXCEPTION_TRANSLATOR(WindowsError);
#endif
}


#endif

#endif
