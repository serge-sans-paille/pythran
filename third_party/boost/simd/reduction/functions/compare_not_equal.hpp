//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_COMPARE_NOT_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_COMPARE_NOT_EQUAL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief compare_not_equal generic tag

     Represents the compare_not_equal function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct compare_not_equal_ : ext::unspecified_<compare_not_equal_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<compare_not_equal_> parent;
    };
  }
  /*!
    Returns a logical scalar that is the result of the lexicographic
    test for != on elements of the entries,
    i.e. return true if and only if two corresponding entries
    elements are not equal.

    It is probably not what you wish. Have a look to <tt>is_not_equal</tt>

    @par Semantic:

    For every parameters of type T0:

    @code
    logical<scalar_of<T0>> r = compare_not_equal(a0,a1);
    @endcode

    is similar to:

    @code
    logical<scalar_of<T0>> r = any(a0 == a1);
    @endcode

    @par Alias:
    @c compare_neq

    @see @funcref{is_not_equal}
    @param a0

    @param a1

    @return a value of the scalar logical type associated to the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compare_not_equal_, compare_not_equal , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compare_not_equal_, compare_neq       , 2 )
} }
#endif

