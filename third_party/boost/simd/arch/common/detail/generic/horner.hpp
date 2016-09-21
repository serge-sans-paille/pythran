//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_HORNER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_HORNER_HPP_INCLUDED

#include <boost/simd/constant/constant.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/preprocessor/punctuation/remove_parens.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/reverse.hpp>


namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  // static unrollign of horner scheme
  // Coefficients are given in decreasing powers and hexadecimal form
  // horner< BOOST_SIMD_HORNER_COEFF(float,5,(a0, a1, a2, a3, a4))>(x)
  // means a0*x^4 + a1*x^3 + a2*x^2 + a3*x + a4
  // computed as a4 + x*(a3 + x*(a2 + x*(a1 + x*a0))))
  // aka fma(x, fma(x, fma(x, fma(x, a0, a1), a2), a3), a4)
  //////////////////////////////////////////////////////////////////////////////
  namespace detail
  {
    namespace bs = boost::simd;

    template<class V, V Coeff, class Next>
    struct horner_unroll
    {
      template<class T>
      static BOOST_FORCEINLINE T call(T const& x)
      {
        return fma(x, Next::call(x), Constant<T, Coeff>());
      }
    };

    template<class V, V Coeff>
    struct horner_unroll<V, Coeff, void>
    {
      template<class T>
      static BOOST_FORCEINLINE T call(T const&)
      {
        return Constant<T, Coeff>();
      }
    };
  }


  //////////////////////////////////////////////////////////////////////////////
  /// @brief Static Horner scheme
  //////////////////////////////////////////////////////////////////////////////
  template<class Coeff, class Type>
  static BOOST_FORCEINLINE Type horner( Type const& x )
  {
    return Coeff::call(x);
  }
} }


#define BOOST_SIMD_COEFF_GEN(z,n,text)                                        \
bs::detail::                                                                \
horner_unroll< BOOST_PP_REMOVE_PARENS(BOOST_PP_TUPLE_ELEM(3,0,text))          \
             , BOOST_PP_TUPLE_ELEM( BOOST_PP_TUPLE_ELEM(3,1,text)             \
                                  , n                                         \
                                  , BOOST_PP_TUPLE_ELEM(3,2,text)             \
                                  )                                           \
             ,                                                                \
/**/

#define BOOST_SIMD_COEFF_GEN2(z,n,text) >

#define BOOST_SIMD_HORNER_COEFF(Type, Size, Seq)                              \
  BOOST_PP_REPEAT(Size, BOOST_SIMD_COEFF_GEN, ( (boost::dispatch::as_integer_t<Type, unsigned>) \
                                     , Size                                   \
                                     , BOOST_PP_TUPLE_REVERSE(Size, Seq)      \
                                     )                                        \
               )                                                              \
void                                                                          \
BOOST_PP_REPEAT(Size, BOOST_SIMD_COEFF_GEN2, ~)                               \
/**/

#define BOOST_SIMD_HORNER_COEFF_T(Type, Size, Seq)                      \
  BOOST_PP_REPEAT(Size, BOOST_SIMD_COEFF_GEN, (                         \
                    (boost::dispatch::as_integer_t<Type, unsigned>)     \
                    , Size                                              \
                    , BOOST_PP_TUPLE_REVERSE(Size, Seq)                 \
                  )                                                     \
                 )                                                      \
    void                                                                \
  BOOST_PP_REPEAT(Size, BOOST_SIMD_COEFF_GEN2, ~)                       \
/**/

////////////////////////////////////////////////////////////////////////////////
// Computing a rationnal fraction P/Q at value x
// with Horner coefs of type "type"
// where P and Q lists of coefficients have respectively n and m elements
// Coefficients are given in decreasing powers and hexadecimal form as in Horner
////////////////////////////////////////////////////////////////////////////////

#define BOOST_SIMD_HORNER_RAT(type, n, m, x, P, Q)      \
  horner < BOOST_SIMD_HORNER_COEFF_T(type, n, P) > (x)/ \
  horner < BOOST_SIMD_HORNER_COEFF_T(type, m, Q) > (x)  \
/**/
#endif
