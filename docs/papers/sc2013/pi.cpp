#define BOOST_PYTHON_MAX_ARITY 4
#define BOOST_SIMD_NO_STRICT_ALIASING 1
#include <pythran/pythran.h>
#include <pythran/pythran_gmp.h>
namespace __pythran_pi
{
  ;
  ;
  struct pi
  {
    typedef void callable;
    template <typename argument_type0 >
    struct type
    {
      typedef double __type0;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type2;
      typedef decltype((std::declval<__type0>() / std::declval<__type2>())) __type3;
      typedef decltype(core::make_tuple(std::declval<__type0>(), std::declval<__type3>())) __type4;
      typedef typename std::tuple_element<1,typename std::remove_reference<__type4>::type>::type __type5;
      typedef typename std::tuple_element<0,typename std::remove_reference<__type4>::type>::type __type6;
      typedef long __type9;
      typedef __type9 __type10;
      typedef decltype((std::declval<__type10>() - std::declval<__type0>())) __type12;
      typedef decltype((std::declval<__type12>() * std::declval<__type5>())) __type13;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::pow2())>::type>::type>()(std::declval<__type13>())) __type14;
      typedef decltype((std::declval<__type0>() + std::declval<__type14>())) __type15;
      typedef decltype((std::declval<__type0>() / std::declval<__type15>())) __type16;
      typedef decltype((std::declval<__type6>() + std::declval<__type16>())) __type17;
      typedef typename __combined<__type16,__type17,__type6>::type __type18;
      typedef typename assignable<decltype((std::declval<__type5>() * std::declval<__type18>()))>::type result_type;
    }
    ;
    template <typename argument_type0 >
    typename type<argument_type0>::result_type operator()(argument_type0 const & nsteps) const
    ;
  }  ;
  template <typename argument_type0 >
  typename pi::type<argument_type0>::result_type pi::operator()(argument_type0 const & nsteps) const
  {
    typedef long __type0;
    typedef double __type1;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type3;
    typedef decltype((std::declval<__type1>() / std::declval<__type3>())) __type4;
    typedef decltype(core::make_tuple(std::declval<__type1>(), std::declval<__type4>())) __type5;
    typedef typename std::tuple_element<0,typename std::remove_reference<__type5>::type>::type __type6;
    typedef __type0 __type10;
    typedef decltype((std::declval<__type10>() - std::declval<__type1>())) __type12;
    typedef typename std::tuple_element<1,typename std::remove_reference<__type5>::type>::type __type13;
    typedef decltype((std::declval<__type12>() * std::declval<__type13>())) __type14;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::pow2())>::type>::type>()(std::declval<__type14>())) __type15;
    typedef decltype((std::declval<__type1>() + std::declval<__type15>())) __type16;
    typedef decltype((std::declval<__type1>() / std::declval<__type16>())) __type17;
    typedef decltype((std::declval<__type6>() + std::declval<__type17>())) __type18;
    typename assignable<__type0>::type i;
    typename assignable<typename __combined<__type17,__type18,__type6>::type>::type sum;
    typename assignable<typename std::tuple_element<1,typename std::remove_reference<__type5>::type>::type>::type step;
    typename assignable<decltype((std::declval<__type12>() * std::declval<__type13>()))>::type x;
    {
      typename assignable<decltype(core::make_tuple(0.0, (1.0 / nsteps)))>::type __tuple10 = core::make_tuple(0.0, (1.0 / nsteps));
      step = std::get<1>(__tuple10);
      sum = std::get<0>(__tuple10);
    }
    {
      typename assignable<typename std::remove_cv<typename std::remove_reference<decltype(__builtin__::proxy::xrange{}(nsteps))>::type>::type>::type __iter1 = __builtin__::proxy::xrange{}(nsteps);
      #pragma omp parallel for reduction(+:sum) private(x) shared(__iter1) private(i)
      for (xrange_iterator __target1 = __iter1.begin(); __target1 < __iter1.end(); ++__target1)
      {
        i= *__target1;
        x = ((i - 0.5) * step);
        sum += (4.0 / (1.0 + __builtin__::proxy::pow2{}(x)));
      }
    }
    return (step * sum);
  }
}

typename std::remove_reference<typename __pythran_pi::pi::type<long>::result_type>::type pi0(long a0)
{
  return __pythran_pi::pi()(a0);
}

BOOST_PYTHON_MODULE(pi)
{
  import_array();
  boost::python::implicitly_convertible<std::string,pythonic::core::string>();
  pythran_to_python<typename std::remove_reference<typename __pythran_pi::pi::type<long>::result_type>::type>();
  boost::python::def("pi", &pi0);
}