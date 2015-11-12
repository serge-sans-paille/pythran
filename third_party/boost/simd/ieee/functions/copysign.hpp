//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_COPYSIGN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_COPYSIGN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief copysign generic tag

     Represents the copysign function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct copysign_ : ext::elementwise_<copysign_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<copysign_> parent;
    };
  }
  /*!
    Returns a0 with the sign of a1

    @par Semantic:

    @code
    T r = copysign(a0,a1);
    @endcode

    is similar to:

    @code
    T r = (a1 >= 0) ? abs(a0) : -(abs(a0));
    @endcode

    @param a0

    @param a1

    @return a value of same type as the inputs
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::copysign_, copysign, 2)
} }

#endif
