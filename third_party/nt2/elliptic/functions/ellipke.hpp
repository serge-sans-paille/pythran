//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_ELLIPKE_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_ELLIPKE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for ellipke function
    struct ellipke_ : ext::elementwise_<ellipke_>
    {
      typedef ext::elementwise_<ellipke_> parent;
    };
  }
  /*!

    Computes simultaneously the complete elliptic integral
    of the first and second kinds.

    @par Semantic:

    @code
    T0 k, e;
    tie(k, e)= ellipke(x);
    @endcode

    is similar to:

    @code
    T0 k = ellpk(1-x);
    T0 e = ellpe(1-x);
    @endcode

    @see @funcref{ellint_1}, @funcref{ellint_2}
    @param a0 angle in radian

    @return A Fusion Sequence containing the sin and cos of @c a0
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::ellipke_, ellipke, 1)

  /*!
    Computes simultaneously the complete elliptic integral
    of the first and second kinds.

    @par Semantic:

    @code
    T0 k, e;
    k = ellipke(x, e);
    @endcode

    is similar to:

    @code
    T0 k = ellpk(1-x);
    T0 e = ellpe(1-x);
    @endcode

    @see @funcref{ellint_1}, @funcref{ellint_2}
    @param a0 outside of \f$[0,1]\f$ the result is nan
    @param a1 accuracy  of computation. The default is Eps<A0>().

    @return A Fusion Sequence containing the cos of @c a0
  **/


  NT2_FUNCTION_IMPLEMENTATION(tag::ellipke_, ellipke, 2)

  /*!
    Computes  simultaneously the complete elliptic integral
    of the first and second kinds, and allows speed-up versus less accuracy.

    @par Semantic:

    @code
    T0 k, e;
    k = ellipke(x, t, e);
    @endcode

    @see @funcref{ellint_1}, @funcref{ellint_2}
    @param a0 outside of \f$[0,1]\f$ the result is nan
    @param a1 accuracy  of computation. The default is Eps<A0>().
    @param a2 L-Value that will receive the second kind elliptic integral
    @return the first  kind elliptic integral

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipke_, ellipke,(A0 const&)(A1 const&)(A2&),3)

  /*!
    Computes simultaneously the complete elliptic integral
    of the first and second kinds, and allows speed-up versus less accuracy.

    @par Semantic:

    @code
    T0 k, e;
    ellipke(x, t, k, e);
    @endcode

    @see @funcref{ellint_1}, @funcref{ellint_2}
    @param a0 outside of \f$[0,1]\f$ the result is nan
    @param a1 accuracy  of computation. The default is Eps<A0>().
    @param a2 L-Value that will receive the first kind elliptic integral
    @param a3 L-Value that will receive the second kind elliptic integral

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipke_, ellipke,(A0 const&)(A1 const&)(A2&)(A3&),4)

    }

#endif
