#ifndef PYTHONIC_EXCEPTIONS_H
#define PYTHONIC_EXCEPTIONS_H
#include <stdexcept>

namespace pythonic {
    namespace core {
        namespace BaseError{
            template<size_t I>
                struct Type
                {
                    typedef core::string type;
                };

            template<>
                struct Type<0>
                {
                    typedef core::list<core::string> type;
                };
        }
        class BaseException: public std::exception
        {
            public:
                BaseException(const BaseException &e) : args(e.args){}
                template<typename ... Types>
                    BaseException(core::string first,Types ... types) { args = core::empty_list() ; init(first, types ...);}
                BaseException() { args = core::empty_list();}
                virtual ~BaseException() noexcept {}
                core::list<core::string> args;
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
            name(core::string first, Types ... types):parent(first, types ...){} \
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

#endif
