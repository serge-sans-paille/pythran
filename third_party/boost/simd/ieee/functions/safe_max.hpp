//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SAFE_MAX_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SAFE_MAX_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief safe_max generic tag

     Represents the safe_max function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct safe_max_ : ext::elementwise_<safe_max_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<safe_max_> parent;
    };
  }
  /*!
    Returns a safe_max relative to the input,  i.e. a
    value which will not overflow when multiplied by the input.

    @par Semantic:

    @code
    T r = safe_max(a0);
    @endcode

    is similar to:

    @code
    T r = x ? Sqrtvalmax<T>()/abs(x) : Inf<T>();
    @endcode

    @param a0

    @return a value of same type as the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::safe_max_, safe_max, 1)
} }

#endif
