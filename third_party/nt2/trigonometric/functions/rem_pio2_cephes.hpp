//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_CEPHES_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_CEPHES_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct rem_pio2_cephes_ : ext::elementwise_<rem_pio2_cephes_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<rem_pio2_cephes_> parent;
    };
  }
  /*!

    Computes the remainder modulo \f$\pi/2\f$ with cephes algorithm,
    and return the angle quadrant between 0 and 3.
    This is a quick version accurate if the input is in \f$[-20\pi,20\pi]\f$.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 r;
    as_integer<T0> n;
    tie(r, n) = rem_pio2_cephes_(x);
    @endcode

    is similar to:

    @code
    as_integer<T0> n = idivround2even(x,, Pio_2<T0>());
    T0 r =  remainder(x, Pio_2<T0>());;
    @endcode

    @see @funcref{rem_pio2}, @funcref{rem_pio2_straight},@funcref{rem_2pi},  @funcref{rem_pio2_medium},
    @param a0 angle in radian

    @return A pair containing the remainder and quadrant of @c a0
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL ( tag::rem_pio2_cephes_
                                  , rem_pio2_cephes,(A0 const&)
                                  , 1
                                  )

  /*!

    Computes the remainder modulo \f$\pi/2\f$ with cephes algorithm,
    and the angle quadrant between 0 and 3.
    This is a quick version accurate if the input is in \f$[-20\pi,20\pi]\f$.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 r;
    as_integer<T0> n;
    n = rem_pio2_cephes_(x, r);
    @endcode

    is similar to:

    @code
    as_integer<T0> n = idivround2even(x,, Pio_2<T0>());
    T0 r =  remainder(x, Pio_2<T0>());;
    @endcode

    @see @funcref{rem_pio2}, @funcref{rem_pio2_straight},@funcref{rem_2pi},  @funcref{rem_pio2_medium},
    @param a0 angle in radian
    @param a1 L-Value that will receive the remainder modulo \f$\pi/2\f$ of @c a0

    @return the integer value of the quadrant
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL ( tag::rem_pio2_cephes_
                                  , rem_pio2_cephes
                                  , (A0 const&)(A0&)
                                  , 1
                                  )

  /*!
    Computes the remainder modulo \f$\pi/2\f$ with cephes algorithm,
    and the angle quadrant between 0 and 3.
    This is a quick version accurate if the input is in \f$[-20\pi,20\pi]\f$.

    @par Semantic:

    For every parameters of floating type T0:

    @code
    T0 r;
    as_integer<T0> n;
    rem_pio2_cephes_(x, n, r);
    @endcode

    is similar to:

    @code
    as_integer<T0> n = idivround2even(x,, Pio_2<T0>());
    T0 r =  remainder(x, Pio_2<T0>());;
    @endcode

    @see @funcref{rem_pio2}, @funcref{rem_pio2_straight},@funcref{rem_2pi},  @funcref{rem_pio2_medium},
    @param a0 angle in radian
    @param a1 L-Value that will receive the quadrant of @c a0
    @param a2 L-Value that will receive the remainder modulo \f$\pi/2\f$ of @c a0

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL ( tag::rem_pio2_cephes_
                                  , rem_pio2_cephes
                                  , (A0 const&)(A1&)(A0&)
                                  , 2
                                  )
}

#endif

