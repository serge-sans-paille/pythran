//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_BITOFSIGN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_BITOFSIGN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief bitofsign generic tag

     Represents the bitofsign function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct bitofsign_ : ext::elementwise_<bitofsign_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<bitofsign_> parent;
    };
  }
  /*!
    Returns a value of the same type as the input
    with all bits set to zero
    except the bit of sign which is preserved.
    Returns always zero for unsigned types

    @par Semantic:

    @code
    T r = bitofsign(a0);
    @endcode

    for signed types is similar to:

    @code
    T r = a0&SignMask;
    @endcode

    @see @funcref{sign}, @funcref{signnz}
    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitofsign_, bitofsign, 1)
} }

#endif
