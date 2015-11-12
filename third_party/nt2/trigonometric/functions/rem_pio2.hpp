//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief rem_pio2 generic tag

     Represents the rem_pio2 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct rem_pio2_ : ext::elementwise_<rem_pio2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<rem_pio2_> parent;
    };
  }

  /*!
    Computes the remainder modulo \f$\pi/2\f$.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r, rc;
    as_integer<T0> n;
    tie(n, r, rc) = rem_pio2(x);
    @endcode

    is similar to:

    @code
    as_integer<T0> n = idivround2even(x,, Pio_2<T0>());
    T0 r =  remainder(x, Pio_2<T0>());
    T0 rc = more_bits_for_r;
    @endcode

    @par Note:

    This function which is accurate and the whole floating range
    is very expansive and its use must
    be limited to huge absolute values of the input.
    (see rem_pio2_cephes,  rem_pio2_medium, etc. for details)

    @param a0

    @return A pair containing quadrant and  the remainder
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_, rem_pio2,(A0 const&),1)
  /*!
    Computes the remainder modulo \f$\pi/2\f$,
    the angle quadrant between 0 and 3 and
    a correction to the remainder.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r;
    as_integer<T0> n;
    tie(n, r) = rem_pio2(x);
    @endcode

    is similar to:

    @code
    as_integer<T0> n = idivround2even(x,, Pio_2<T0>());
    T0 r =  remainder(x, Pio_2<T0>());;
    @endcode

    @par Note:

    This function which is accurate and the whole floating range
    is very expansive and its use must
    be limited to huge absolute values of the input.
    (see rem_pio2_cephes,  rem_pio2_medium, etc. for details)

    @param a0
    @param a1

    @return A triplet containing quadrant, remainder and extra precision
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_, rem_pio2,(A0 const&)(A0&),1)
  /*!
    Computes the remainder modulo \f$\pi/2\f$,
    the angle quadrant between 0 and 3.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r;
    as_integer<T0> n;
    tie(n, r) = rem_pio2(x);
    @endcode

    is similar to:

    @code
    as_integer<T0> n = idivround2even(x,, Pio_2<T0>());
    T0 r =  remainder(x, Pio_2<T0>());;
    @endcode

    @par Note:

    This function which is accurate and the whole floating range
    is very expansive and its use must
    be limited to huge absolute values of the input.
    (see rem_pio2_cephes,  rem_pio2_medium, etc. for details)

    @param a0
    @param a1
    @param a2

    @return A pair containing quadrant and  the remainder
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_, rem_pio2,(A0 const&)(A1&)(A0&),2)
  /*!
    Computes the remainder modulo \f$\pi/2\f$.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r, rc;
    as_integer<T0> n;
    n = rem_pio2<Range>(x, r);
    @endcode

    is similar to:

    @code
    as_integer<T0> n = idivround2even(x,, Pio_2<T0>());
    T0 r =  remainder(x, Pio_2<T0>());
    @endcode

    @par Note:

    The Range parameter is a type among big_,  medium_,  small_,  very_small_
    that allow to statically choose the computation process.

    @param a0
    @param a1
    @param a2
    @param a3

    @return  the remainder
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_, rem_pio2,(A0 const&)(A1&)(A0&)(A0&),2)
  ///INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_, rem_pio2,(A0 const&)(A0&)(const A1&),2)

 }

#endif

