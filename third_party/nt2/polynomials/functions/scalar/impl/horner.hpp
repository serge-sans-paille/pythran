//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOMIALS_FUNCTIONS_SCALAR_IMPL_HORNER_HPP_INCLUDED
#define NT2_POLYNOMIALS_FUNCTIONS_SCALAR_IMPL_HORNER_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/reverse.hpp>

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // static unrollign of horner scheme
  // Coefficients are given in decreasing powers and hexadecimal form
  // horner< NT2_HORNER_COEFF(float,5,(a0, a1, a2, a3, a4))>(x)
  // means a0*x^4 + a1*x^3 + a2*x^2 + a3*x + a4
  // computed as a4 + x*(a3 + x*(a2 + x*(a1 + x*a0))))
  // aka fma(x, fma(x, fma(x, fma(x, a0, a1), a2), a3), a4)
  //////////////////////////////////////////////////////////////////////////////

  namespace details
  {
    template<class V, V Coeff, class Next>
    struct horner_unroll
    {
      template<class T>
      static BOOST_FORCEINLINE T call(T const& x)
      {
        return fma(x, Next::call(x), Const<T, Coeff>());
      }
    };

    template<class V, V Coeff>
    struct horner_unroll<V, Coeff, void>
    {
      template<class T>
      static BOOST_FORCEINLINE T call(T const&)
      {
        return Const<T, Coeff>();
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
}

#define NT2_COEFF_GEN(z,n,text)                                               \
nt2::details::                                                                \
horner_unroll< BOOST_DISPATCH_PP_STRIP(BOOST_PP_TUPLE_ELEM(3,0,text))         \
             , BOOST_PP_TUPLE_ELEM( BOOST_PP_TUPLE_ELEM(3,1,text)             \
                                  , n                                         \
                                  , BOOST_PP_TUPLE_ELEM(3,2,text)             \
                                  )                                           \
             ,                                                                \
/**/

#define NT2_COEFF_GEN2(z,n,text) >

#define NT2_HORNER_COEFF(Type, Size, Seq)                                     \
BOOST_PP_REPEAT(Size, NT2_COEFF_GEN, ( (nt2::meta::as_integer<Type, unsigned>::type) \
                                     , Size                                   \
                                     , BOOST_PP_TUPLE_REVERSE(Size, Seq)      \
                                     )                                        \
               )                                                              \
void                                                                          \
BOOST_PP_REPEAT(Size, NT2_COEFF_GEN2, ~)                                      \
/**/

#define NT2_HORNER_COEFF_T(Type, Size, Seq)                                   \
BOOST_PP_REPEAT(Size, NT2_COEFF_GEN, ( (typename nt2::meta::as_integer<Type, unsigned>::type) \
                                     , Size                                   \
                                     , BOOST_PP_TUPLE_REVERSE(Size, Seq)      \
                                     )                                        \
               )                                                              \
void                                                                          \
BOOST_PP_REPEAT(Size, NT2_COEFF_GEN2, ~)                                      \
/**/

////////////////////////////////////////////////////////////////////////////////
// Computing a rationnal fraction P/Q at value x
// with Horner coefs of type "type"
// where P and Q lists of coefficients have respectively n and m elements
// Coefficients are given in decreasing powers and hexadecimal form as in Horner
////////////////////////////////////////////////////////////////////////////////

#define NT2_HORNER_RAT(type, n, m, x, P, Q)      \
  horner < NT2_HORNER_COEFF_T(type, n, P) > (x)/ \
  horner < NT2_HORNER_COEFF_T(type, m, Q) > (x)  \
/**/
#endif
