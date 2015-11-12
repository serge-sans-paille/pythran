//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_COMPARE_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_COMPARE_EQUAL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief compare_equal generic tag

     Represents the compare_equal function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct compare_equal_ : ext::unspecified_<compare_equal_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<compare_equal_> parent;
    };
  }
  /*!
    Returns a logical scalar value that is the result of the lexicographic
    test for equality of all elements of the entries,
    i.e. return true if and only if all corresponding entries
    elements are equal.

    It is probably not what you wish. Have a look to <tt>is_equal</tt>

    @par Semantic:

    For every parameters of type T0:

    @code
    logical<scalar_of<T0>> r = compare_equal(a0,a1);
    @endcode

    is similar to:

    @code
    logical<scalar_of<T0>> r = all(a0 == a1)
    @endcode

    @par Alias:
    @c compare_eq

    @see @funcref{is_equal}
    @param a0

    @param a1

    @return a value of the scalar logical type asssociated to the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compare_equal_, compare_equal , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::compare_equal_, compare_eq    , 2 )
} }
#endif

