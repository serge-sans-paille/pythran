//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_EXP10_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_EXP10_HPP_INCLUDED
#include <nt2/exponential/functions/exp10.hpp>
#include <nt2/exponential/functions/scalar/impl/exponential.hpp>

namespace nt2 {  namespace details
  {
    // ///////////////////////////////////////////////////////////////////////////
    // Meta-programmed exp10 values
    // ///////////////////////////////////////////////////////////////////////////
    template<class T, int N> struct static_exp10
    {
      static const T value = T(10)*static_exp10<T,N-1>::value;
    };

    template<class T> struct static_exp10<T,0>  { static const T value = 1; };
    template<class T> struct static_exp10<T,-1> { static const T value = 0; };

    #define NT2_CREATE_FAST_EXP10_LIMIT(T,L)                          \
    template<> struct static_exp10<T,L> { static const T value = 0; } \
    /**/

    NT2_CREATE_FAST_EXP10_LIMIT(int8_t      , 3);
    NT2_CREATE_FAST_EXP10_LIMIT(uint8_t     , 3);
    NT2_CREATE_FAST_EXP10_LIMIT(int16_t     , 5);
    NT2_CREATE_FAST_EXP10_LIMIT(uint16_t    , 5);
    NT2_CREATE_FAST_EXP10_LIMIT(int32_t     ,10);
    NT2_CREATE_FAST_EXP10_LIMIT(uint32_t    ,10);
    NT2_CREATE_FAST_EXP10_LIMIT(int64_t     ,19);
    NT2_CREATE_FAST_EXP10_LIMIT(uint64_t    ,20);
    #undef NT2_CREATE_FAST_EXP10_LIMIT

    // ///////////////////////////////////////////////////////////////////////////
    // Meta-programmed exp10 linearization
    // ///////////////////////////////////////////////////////////////////////////
    template<class T,int D, int F, bool STOP = (F==D+1)> struct s_exp10
    {
      static const T pivot = (F+D)/2;
      static inline T Eval(const T& x)
      {
        return (x<pivot) ? s_exp10<T,D,pivot>::Eval(x) : s_exp10<T,pivot,F>::Eval(x);
      }
    };

    template<class T,int D, int F> struct s_exp10<T,D,F,true>
    {
      static inline T Eval(const T& ) { return static_exp10<T,D>::value; }
    };

    // ///////////////////////////////////////////////////////////////////////////
    // Meta-programmed exp10 entry-point
    // ///////////////////////////////////////////////////////////////////////////
    #define NT2_FAST_EXP10(T,D,F) \
    inline T specExp10( const T& x ) { return s_exp10<T,D,F>::Eval(x); }

    NT2_FAST_EXP10(int8_t      , -1, 4)
    NT2_FAST_EXP10(uint8_t     ,  0, 4)
    NT2_FAST_EXP10(int16_t     , -1, 6)
    NT2_FAST_EXP10(uint16_t    ,  0, 6)
    NT2_FAST_EXP10(int32_t     , -1,11)
    NT2_FAST_EXP10(uint32_t    ,  0,11)
    NT2_FAST_EXP10(int64_t     , -1,20)
    NT2_FAST_EXP10(uint64_t    ,  0,21)
    #undef NT2_FAST_EXP10
  }
}

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::exp10_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
        return details::specExp10(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::exp10_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::details::
        exponential<A0,ten_tag, tag::not_simd_type, accu_tag>
        ::expa(a0);
      }
  };
} }

#endif
