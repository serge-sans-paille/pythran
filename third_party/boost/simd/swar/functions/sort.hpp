//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SORT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SORT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/dispatch/meta/tieable.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief sort generic tag

     Represents the sort function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct sort_ : ext::tieable_<sort_>
    {
      /// @brief Parent hierarchy
      typedef ext::tieable_<sort_> parent;
    };
  }
  /*!
    returns the sorted a0 vector in ascending order

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = sort(a0);
    @endcode

    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sort_, sort, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sort_, sort, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sort_, sort, 3)

} }

#endif
