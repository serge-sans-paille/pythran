#define BOOST_PYTHON_MAX_ARITY 4
#define BOOST_SIMD_NO_STRICT_ALIASING 1
#include <pythran/pythran.h>
namespace __pythran_map0
{
  ;
  ;
  struct map0
  {
    typedef void callable;
    template <typename argument_type0 >
    struct type
    {
      typedef typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::abs())>::type>::type __type0;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type1;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::range())>::type>::type>()(std::declval<__type1>())) __type2;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::vmap())>::type>::type>()(std::declval<__type0>(), std::declval<__type2>())) __type3;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::len())>::type>::type>()(std::declval<__type3>())) __type4;
      typedef long __type5;
      typedef decltype((std::declval<__type4>() / std::declval<__type5>())) __type6;
      typedef typename assignable<decltype(std::declval<__type3>()[std::declval<__type6>()])>::type result_type;
    }
    ;
    template <typename argument_type0 >
    typename type<argument_type0>::result_type operator()(argument_type0 const & n) const
    ;
  }  ;
  template <typename argument_type0 >
  typename map0::type<argument_type0>::result_type map0::operator()(argument_type0 const & n) const
  {
    typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type0;
    typedef typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::abs())>::type>::type __type1;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::range())>::type>::type>()(std::declval<__type0>())) __type2;
    typename lazy<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::range())>::type>::type>()(std::declval<__type0>()))>::type r = __builtin__::proxy::range{}(n);
    typename assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::vmap())>::type>::type>()(std::declval<__type1>(), std::declval<__type2>()))>::type l = __builtin__::proxy::vmap{}(__builtin__::proxy::abs{}, r);
    return l[(__builtin__::proxy::len{}(l) / 2L)];
  }
}

typename std::remove_reference<typename __pythran_map0::map0::type<long>::result_type>::type map00(long a0)
{
  return __pythran_map0::map0()(a0);
}

BOOST_PYTHON_MODULE(map0)
{
  import_array();
  boost::python::implicitly_convertible<std::string,pythonic::core::string>();
  boost::python::register_exception_translator<pythonic::core::BaseException>(&translate_BaseException);
  boost::python::register_exception_translator<pythonic::core::Exception>(&translate_Exception);
  boost::python::register_exception_translator<pythonic::core::StopIteration>(&translate_StopIteration);
  boost::python::register_exception_translator<pythonic::core::StandardError>(&translate_StandardError);
  boost::python::register_exception_translator<pythonic::core::EnvironmentError>(&translate_EnvironmentError);
  boost::python::register_exception_translator<pythonic::core::IOError>(&translate_IOError);
  boost::python::register_exception_translator<pythonic::core::ArithmeticError>(&translate_ArithmeticError);
  boost::python::register_exception_translator<pythonic::core::ZeroDivisionError>(&translate_ZeroDivisionError);
  boost::python::register_exception_translator<pythonic::core::OverflowError>(&translate_OverflowError);
  boost::python::register_exception_translator<pythonic::core::SystemError>(&translate_SystemError);
  boost::python::register_exception_translator<pythonic::core::SyntaxError>(&translate_SyntaxError);
  boost::python::register_exception_translator<pythonic::core::IndentationError>(&translate_IndentationError);
  boost::python::register_exception_translator<pythonic::core::EOFError>(&translate_EOFError);
  boost::python::register_exception_translator<pythonic::core::LookupError>(&translate_LookupError);
  boost::python::register_exception_translator<pythonic::core::IndexError>(&translate_IndexError);
  boost::python::register_exception_translator<pythonic::core::ImportError>(&translate_ImportError);
  boost::python::register_exception_translator<pythonic::core::ReferenceError>(&translate_ReferenceError);
  boost::python::register_exception_translator<pythonic::core::AttributeError>(&translate_AttributeError);
  boost::python::register_exception_translator<pythonic::core::Warning>(&translate_Warning);
  boost::python::register_exception_translator<pythonic::core::FutureWarning>(&translate_FutureWarning);
  boost::python::register_exception_translator<pythonic::core::UserWarning>(&translate_UserWarning);
  boost::python::register_exception_translator<pythonic::core::ImportWarning>(&translate_ImportWarning);
  boost::python::register_exception_translator<pythonic::core::DeprecationWarning>(&translate_DeprecationWarning);
  boost::python::register_exception_translator<pythonic::core::UnicodeWarning>(&translate_UnicodeWarning);
  boost::python::register_exception_translator<pythonic::core::PendingDeprecationWarning>(&translate_PendingDeprecationWarning);
  boost::python::register_exception_translator<pythonic::core::GeneratorExit>(&translate_GeneratorExit);
  boost::python::register_exception_translator<pythonic::core::OSError>(&translate_OSError);
  boost::python::register_exception_translator<pythonic::core::KeyError>(&translate_KeyError);
  boost::python::register_exception_translator<pythonic::core::SystemExit>(&translate_SystemExit);
  boost::python::register_exception_translator<pythonic::core::MemoryError>(&translate_MemoryError);
  boost::python::register_exception_translator<pythonic::core::RuntimeError>(&translate_RuntimeError);
  boost::python::register_exception_translator<pythonic::core::SyntaxWarning>(&translate_SyntaxWarning);
  boost::python::register_exception_translator<pythonic::core::BytesWarning>(&translate_BytesWarning);
  boost::python::register_exception_translator<pythonic::core::NameError>(&translate_NameError);
  boost::python::register_exception_translator<pythonic::core::UnboundLocalError>(&translate_UnboundLocalError);
  boost::python::register_exception_translator<pythonic::core::ValueError>(&translate_ValueError);
  boost::python::register_exception_translator<pythonic::core::UnicodeError>(&translate_UnicodeError);
  boost::python::register_exception_translator<pythonic::core::TypeError>(&translate_TypeError);
  boost::python::register_exception_translator<pythonic::core::NotImplementedError>(&translate_NotImplementedError);
  boost::python::register_exception_translator<pythonic::core::FloatingPointError>(&translate_FloatingPointError);
  boost::python::register_exception_translator<pythonic::core::AssertionError>(&translate_AssertionError);
  boost::python::register_exception_translator<pythonic::core::BufferError>(&translate_BufferError);
  boost::python::register_exception_translator<pythonic::core::KeyboardInterrupt>(&translate_KeyboardInterrupt);
  boost::python::register_exception_translator<pythonic::core::RuntimeWarning>(&translate_RuntimeWarning);
  boost::python::register_exception_translator<pythonic::core::TabError>(&translate_TabError);
  pythran_to_python<typename std::remove_reference<typename __pythran_map0::map0::type<long>::result_type>::type>();
  boost::python::def("map0", &map00);
}