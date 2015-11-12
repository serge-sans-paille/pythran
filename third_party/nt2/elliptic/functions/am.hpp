//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_AM_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_AM_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief am generic tag

     Represents the am function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct am_ : ext::elementwise_<am_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<am_> parent;
    };
  }
  /*!
    Returns the  the jacobi's elliptic function am(u,x,{tol}{,choice})

    @par Semantic:

    Let F(phi,k) = F(phi \ alpha) = F(phi | m), be Legendre's elliptic
    function of the first kind with modulus k, modular angle alpha
    where k = sin(alpha) or parameter m where m = k^2, i.e.

     \f$\displaystyle   F(\phi,k) = \int_0^\phi  \frac{d\theta}{\sqrt{1 - k^2 \sin^2\theta}}\f$

     \f$\displaystyle  F(\phi \backslash \alpha) = \int_0^\phi \frac{d\theta}{\sqrt{1 - \sin^2\alpha \sin^2\theta}}\f$

     \f$\displaystyle  F(\phi | m) = \int_0^\phi \frac{d\theta}{\sqrt{1 - m \sin^2\theta}}\f$

    This Jacobi elliptic amplitude function, am, is defined as
              am(u,k) = am(u \ alpha) = am(u | m)  = phi
    where u = F(phi,k) = F(phi \ alpha) = F(phi | m).

    The second argument of the amplitude function am(u,x)
    corresponding to the second argument of the elliptic integral of
    the first kind F(phi,x).  x may be the modulus, modular angle,
    or parameter depending on the value of choice.  If a2 = 'm',
    then x must be between 0 and 1 inclusively and if a2 = 'k',
    then x must be between -1 and 1 inclusively.


    @param a0 The first argument of am(u,x) corresponding to the value
    of the elliptic integral of the first kind u = F(am(u,x),x).

    @param a1 The second argument of the amplitude function am(u,x)
    corresponding to the second argument of the elliptic integral of
    the first kind F(phi,x).  x may be the modulus, modular angle,
    or parameter depending on the value of a2.  If a2 = 'm',
    then x must be between 0 and 1 inclusively and if a2 = 'k',
    then x must be between -1 and 1 inclusively.

    @param a3 tol the tolerance on the result accuracy by defaut Eps<T>(),
    where T is the type of u

    @param a2 arg The mode of the second argument of am(): If a2 =
    'k', then x = k, the modulus of F(phi,k).  If A2 = 'a', then x =
    alpha, the modular angle of F(phi \ alpha), alpha in radians.  If
    arg = 'm', then x = m, the parameter of F(phi | m).  The value of
    arg defaults to 'k'.

    @return a value of the same type as the first parameter
  **/

    NT2_FUNCTION_IMPLEMENTATION(tag::am_, am, 2)
    NT2_FUNCTION_IMPLEMENTATION(tag::am_, am, 3)
    NT2_FUNCTION_IMPLEMENTATION(tag::am_, am, 4)
}

#endif

