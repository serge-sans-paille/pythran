//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_ELLIPJ_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_ELLIPJ_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for ellipj function
    struct ellipj_ : ext::elementwise_<ellipj_>
    {
      typedef ext::elementwise_<ellipj_> parent;
    };
  }
  /*!

    computes simultaneously the values of the jacobi elliptic
    functions sn, cn and dn, evaluated for corresponding elements of
    argument u and parameter m.  u and m must be arrays of the same
    size or either can be scalar. m is limited to 0 <= m <= 1.

    @par Semantic:

    @code
    T0 k, e;
    tie(s, c, d)= ellipj(x, m{, tol});
    @endcode


    @see @funcref{am}
    @param a0 angle in radian
    @param a1 modulus
    @param a1 tolerance : lesser accuracy versus speed (default is Eps<T0>())

    @return A Fusion Sequence containing the sn, cn and dn values
  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipj_, ellipj,(A0 const&)(A1 const&)(A2 const&),3)
   //@overload
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipj_, ellipj,(A0 const&)(A1 const&),2)

  /*!
    Computes simultaneously the values of the jacobi elliptic
    functions sn, cn and dn, evaluated for corresponding elements of
    argument x and parameter m, and allows speed-up versus less accuracy.

    @par Semantic:

    @code
    T0 s, c, d;
    tie(s, c) = ellipj(x, m, tol, d);
    @endcode

    @see @funcref{am}
    @param a0 angle in radian
    @param a1 outside of \f$[0,1]\f$ the result is nan
    @param a2 accuracy  of computation. The default is Eps<A0>() (obtained for _()).
    @param a3 L-Value that will receive dn elliptic integral
    @return A Fusion Sequence containing the sn and cn values
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipj_, ellipj,(A0 const&)(A1 const&)(A2 const&)(A3&),4)
  /*!
    Computes simultaneously the values of the jacobi elliptic
    functions sn, cn and dn, evaluated for corresponding elements of
    argument u and parameter m, and allows speed-up versus less accuracy.

    @par Semantic:

    @code
    T0 c, d;
    T0 s = ellipj(x, m, tol, c, d);
    @endcode

    @see @funcref{am}, @funcref{sn}, @funcref{cn}, @funcref{dn}
    @param a0 angle in radian
    @param a1 outside of \f$[0,1]\f$ the result is nan
    @param a2 accuracy  of computation. The default is Eps<A0>()(obtained for _()).
    @param a3 L-Value that will receive cn elliptic integral
    @param a4 L-Value that will receive dn elliptic integral
    @return the sn elliptic integral

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipj_, ellipj,(A0 const&)(A1 const&)(A2 const&)(A3&)(A4&),5)

  /*!
    Computes simultaneously the values of the jacobi elliptic
    functions sn, cn and dn, evaluated for corresponding elements of
    argument u and parameter m, and allows speed-up versus less accuracy.

    @par Semantic:

    @code
    T0 s, c, d;
    ellipj(x, m, tol, s, c, d);
    @endcode

    @see @funcref{am}
    @param a0 angle in radian
    @param a1 outside of \f$[0,1]\f$ the result is nan
    @param a2 accuracy  of computation. The default is Eps<A0>()(obtained for _()).
    @param a3 L-Value that will receive sn elliptic integral
    @param a4 L-Value that will receive cn elliptic integral
    @param a5 L-Value that will receive dn elliptic integral

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipj_, ellipj,(A0 const&)(A1 const&)(A2 const&)(A3&)(A4&)(A5&),6)

    }

#endif
