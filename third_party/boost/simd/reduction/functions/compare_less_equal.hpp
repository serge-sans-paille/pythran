//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_COMPARE_LESS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_COMPARE_LESS_EQUAL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief compare_less_equal generic tag

     Represents the compare_less_equal function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct compare_less_equal_ : ext::unspecified_<compare_less_equal_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<compare_less_equal_> parent;
    };
  }
  /*!
    Returns a logical scalar that is the result of the lexicographic
    test for <= on all elements of the entries

    It is probably not what you wish. Have a look to is_less_equal

    @par Semantic:

    For every parameters of type T0:

    @code
    as_logical<scalar_of<T0>> r = compare_less_equal(a0,a1);
    @endcode

    is similar to:

    @code
      as_logical<scalar_of<T0>> r = !compare_greater(a1, a0)
    @endcode

    @par Alias:
    @c compare_le

    @see @funcref{is_less_equal}
    @param a0

    @param a1

    @return a value of the scalar logical type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compare_less_equal_, compare_less_equal , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compare_less_equal_, compare_le         , 2 )
} }
#endif

