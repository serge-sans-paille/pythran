//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_MINNUM_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_MINNUM_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief minnum generic tag

     Represents the minnum function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct minnum_ : ext::elementwise_<minnum_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<minnum_> parent;
    };
  }
  /*!
     Returns the minimum value, ignoring nans.

    @par Semantic:

    @code
    T r = minnum(a0,a1);
    @endcode

    is similar to:

    @code
    T r =     T r = (is_nan(a0) ? a1 : (isnan(a1) ? a0 : min(a0, a1));;
    @endcode

    @par Alias:
    @c fmin

    @param a0

    @param a1

    @return a value of same type as the inputs
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minnum_, minnum, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minnum_, fmin, 2)
} }

#endif
