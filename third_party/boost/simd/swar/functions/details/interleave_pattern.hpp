//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_INTERLEAVE_PATTERN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_INTERLEAVE_PATTERN_HPP_INCLUDED

#include <boost/simd/swar/functions/details/default_matcher.hpp>
#include <boost/simd/include/functions/simd/deinterleave_second.hpp>
#include <boost/simd/include/functions/simd/deinterleave_first.hpp>
#include <boost/simd/include/functions/simd/interleave_second.hpp>
#include <boost/simd/include/functions/simd/interleave_first.hpp>
#include <boost/simd/include/functions/simd/interleave_even.hpp>
#include <boost/simd/include/functions/simd/interleave_odd.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/attributes.hpp>

#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/seq/elem.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // reversed cardinal 2 interleave_*
  //============================================================================
  template<typename Permutation>
  struct default_matcher::match2<2,0,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, P const&)
    {
      return interleave_first(a1,a0);
    }
  };

  template<typename Permutation>
  struct default_matcher::match2<3,1,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, P const&)
    {
      return interleave_second(a1,a0);
    }
  };

  //============================================================================
  // Auto-generated (de)interleave_* for 2-32 cardinal
  //============================================================================
#define M_IUFIRST(z,n,t)    n/2
#define M_IUFIRST00(z,n,t)  (n%2) ? M_IUFIRST(z,n,t) : -1
#define M_IUFIRST01(z,n,t)  (n%2) ? -1 : M_IUFIRST(z,n,t)
#define M_IBFIRST(z,n,t)    n/2+(n%2)*t

#define M_IUSECOND(z,n,t)   M_IUFIRST(z,n,t)+t/2
#define M_IUSECOND00(z,n,t) (n%2) ? M_IUSECOND(z,n,t) : -1
#define M_IUSECOND01(z,n,t) (n%2) ?-1 : M_IUSECOND(z,n,t)

#define M_IBSECOND(z,n,t) M_IBFIRST(z,n,t)+t/2

#define M_IEVEN(z,n,t) (n/2)*(t/2)+(n%2)*t
#define M_IODD(z,n,t)   M_IEVEN(z,n,t)+1

#define M_DFIRST(z,n,t)  2*n
#define M_DSECOND(z,n,t)  2*n+1

// unary interleaving
#define M_UINTERLEAVE(z,n,t)                                                   \
template<typename Permutation>                                                 \
struct BOOST_PP_CAT(default_matcher::match,n)                                  \
        < BOOST_PP_ENUM(n,BOOST_PP_SEQ_ELEM(1,t),n), Permutation>              \
{                                                                              \
  template<typename T, typename P>                                             \
  static BOOST_FORCEINLINE T process(T const& a0, P const&)                    \
  {                                                                            \
    return BOOST_PP_SEQ_ELEM(0,t)BOOST_PP_SEQ_ELEM(2,t);                       \
  }                                                                            \
};                                                                             \
/**/

// Binary interleaving
#define M_BINTERLEAVE(z,n,t)                                                   \
template<typename Permutation>                                                 \
struct BOOST_PP_CAT(default_matcher::match,n)                                  \
        < BOOST_PP_ENUM(n,BOOST_PP_SEQ_ELEM(1,t),n), Permutation>              \
{                                                                              \
  template<typename T, typename P>                                             \
  static BOOST_FORCEINLINE T process(T const& a0, T const& a1, P const&)       \
  {                                                                            \
    return BOOST_PP_SEQ_ELEM(0,t)BOOST_PP_SEQ_ELEM(2,t);                       \
  }                                                                            \
};                                                                             \
/**/

  // Unary interleave_first/second
  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 2, 32, M_UINTERLEAVE
                                          , (interleave_first)
                                            (M_IUFIRST)
                                            ((a0,a0))
                                          )

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 2, 32, M_UINTERLEAVE
                                          , (interleave_first)
                                            (M_IUFIRST00)
                                            ((Zero<T>(),a0))
                                          )

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 2, 32, M_UINTERLEAVE
                                          , (interleave_first)
                                            (M_IUFIRST01)
                                            ((a0,Zero<T>()))
                                          )

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 2, 32, M_UINTERLEAVE
                                          , (interleave_second)
                                            (M_IUSECOND)
                                            ((a0,a0))
                                          )

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 2, 32, M_UINTERLEAVE
                                          , (interleave_second)
                                            (M_IUSECOND00)
                                            ((Zero<T>(),a0))
                                          )

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 2, 32, M_UINTERLEAVE
                                          , (interleave_second)
                                            (M_IUSECOND01)
                                            ((a0,Zero<T>()))
                                          )

  // Binary interleave_first/second
  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 2, 32, M_BINTERLEAVE
                                          , (interleave_first)
                                            (M_IBFIRST)
                                            ((a0,a1))
                                          )

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 2, 32, M_BINTERLEAVE
                                          , (interleave_second)
                                            (M_IBSECOND)
                                            ((a0,a1))
                                          )

  // Binary interleave_even/odd
  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 4, 32, M_BINTERLEAVE
                                          , (interleave_even)
                                            (M_IEVEN)
                                            ((a0,a1))
                                          )

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 4, 32, M_BINTERLEAVE
                                          , (interleave_odd)
                                            (M_IODD)
                                            ((a0,a1))
                                          )
  // Binary deinterleave_first_second
  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 4, 32, M_BINTERLEAVE
                                          , (deinterleave_first)
                                            (M_DFIRST)
                                            ((a0,a1))
                                          )

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM_TO ( 4, 32, M_BINTERLEAVE
                                          , (deinterleave_second)
                                            (M_DSECOND)
                                            ((a0,a1))
                                          )

#undef M_UINTERLEAVE
#undef M_BINTERLEAVE
#undef M_IUFIRST
#undef M_IUSECOND
#undef M_IBFIRST
#undef M_IBSECOND
#undef M_IODD
#undef M_IEVEN
#undef M_DFIRST
#undef M_DSECOND

} } }

#endif
