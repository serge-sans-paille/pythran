//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_STRAIGHT_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_STRAIGHT_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for rem_pio2_straight function
    struct rem_pio2_straight_ : ext::elementwise_<rem_pio2_straight_>
    {
      typedef ext::elementwise_<rem_pio2_straight_> parent;
    };
  }
  /*!
    Computes the remainder modulo \f$\pi/2\f$.


    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r, rc;
    as_integer<T0> n;
    tie(n, r) = rem_pio2_straight<Range>(x);
    @endcode

    is similar to:

    @code
    as_integer<T0> n = idivround2even(x,, Pio_2<T0>());
    T0 r =  remainder(x, Pio_2<T0>());
    @endcode

    @par Note:
    @c rem_pio2_straight computes the remainder modulo \f$\pi/2\f$ with straight algorithm,
    and returns an angle quadrant which is always 1.
    This is a very quick version accurate if the input
    is in \f$[\pi/4,\pi/2]\f$. In fact it only substract \f$\pi/2\f$ to the input
    so it can be viewed as a specially accurate minuspio_2 function outside
    the interval in which it can be used as a substitute to rem_pio2.

    The reduction of the argument modulo \f$\pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms as this one
    can be used, but the precision is only insured on specific intervals.

    @see @funcref{rem_pio2}, @funcref{rem_pio2_medium},@funcref{rem_2pi},  @funcref{rem_pio2_cephes},
    @param a0 angle in radian

    @return A pair containing quadrant and  the remainder
  **/

   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_straight_, rem_pio2_straight,(A0 const&),1)

  /*!
    Computes the remainder modulo \f$\pi/2\f$.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r, rc;
    as_integer<T0> n;
    n = rem_pio2_straight<Range>(x, r);
    @endcode

    is similar to:

    @code
    as_integer<T0> n = idivround2even(x,, Pio_2<T0>());
    T0 r =  remainder(x, Pio_2<T0>());
    @endcode

    @par Note:
    @c rem_pio2_straight computes the remainder modulo \f$\pi/2\f$ with straight algorithm,
    and returns an angle quadrant which is always 1.
    This is a very quick version accurate if the input
    is in \f$[\pi/4,\pi/2]\f$. In fact it only substract \f$\pi/2\f$ to the input
    so it can be viewed as a specially accurate minuspio_2 function outside
    the interval in which it can be used as a substitute to rem_pio2.

    The reduction of the argument modulo \f$\pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms as this one
    can be used, but the precision is only insured on specific intervals.

    @see @funcref{rem_pio2}, @funcref{rem_pio2_medium},@funcref{rem_2pi},  @funcref{rem_pio2_cephes},
    @param a0 angle in radian
    @param a1 L-Value that will receive the remainder modulo \f$\pi/2\f$ of @c a0

    @return A pair containing the remainder and quadrant  of @c a0
  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_straight_, rem_pio2_straight,(A0 const&)(A0&),1)

  /*!
    Computes the remainder modulo \f$\pi/2\f$.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r, rc;
    as_integer<T0> n;
    rem_pio2_straight<Range>(x, n, r);
    @endcode

    is similar to:

    @code
    as_integer<T0> n = idivround2even(x,, Pio_2<T0>());
    T0 r =  remainder(x, Pio_2<T0>());
    @endcode

    @par Note:
    @c rem_pio2_straight computes the remainder modulo \f$\pi/2\f$ with straight algorithm,
    and returns an angle quadrant which is always 1.
    This is a very quick version accurate if the input
    is in \f$[\pi/4,\pi/2]\f$. In fact it only substract \f$\pi/2\f$ to the input
    so it can be viewed as a specially accurate minuspio_2 function outside
    the interval in which it can be used as a substitute to rem_pio2.

    The reduction of the argument modulo \f$\pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms as this one
    can be used, but the precision is only insured on specific intervals.

    @see @funcref{rem_pio2}, @funcref{rem_pio2_medium},@funcref{rem_2pi},  @funcref{rem_pio2_cephes},
    @param a0 angle in radian
    @param a1 L-Value that will receive the quadrant of @c a0
    @param a2 L-Value that will receive the remainder modulo \f$\pi/2\f$ of @c a0

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_straight_, rem_pio2_straight,(A0 const&)(A1&)(A0&),2)

    }

#endif


