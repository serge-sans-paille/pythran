//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SUBS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SUBS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd {
  namespace tag
  {
    /*!
      @brief  subs generic tag

      Represents the subs function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct subs_ : ext::elementwise_<subs_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<subs_> parent;
    };
  }
  /*!
    Computes the saturated sum of its parameters.

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = subs(x, y);
    @endcode

    This function coincides with minus for floating point parameters.
    For integers is similar to:

    @code
    T r = (x-y > Valmax) ? Valmax : (x-y <  Valmin ? Valmin : x-y);
    @endcode

    @par Alias

    saturated_sub

    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::subs_, subs, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::subs_, saturated_sub, 2)
} }

#endif
