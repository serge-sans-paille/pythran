//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_MEANOF_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_MEANOF_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  meanof generic tag

      Represents the meanof function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct meanof_ : ext::elementwise_<meanof_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<meanof_> parent;
    };
  }
  /*!
    Computes the mean of its parameter avoiding overflow.

    @par semantic:
    For any given value @c x and @c y of type @c T:

    @code
    T r = meanof(x, y);
    @endcode

    is similar to:

    @code
    T r = (x+y)/2;
    @endcode

    @par Note:
    Take care that for integers the value returned can differ by one unit
    from \c ceil((a+b)/2.0) or \c floor((a+b)/2.0), but is always one of
    the two values.

    @param  a0
    @param  a1

    @return an value of the same type as the input.

  **/
   BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::meanof_, meanof, 2)
} }

#endif


