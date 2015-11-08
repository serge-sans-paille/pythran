//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_IS_NEGATIVE_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_IS_NEGATIVE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_negative generic tag

     Represents the is_negative function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_negative_ : ext::elementwise_<is_negative_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<is_negative_> parent;
    };}
  /*!
    Returns True if a0 is negative else False.

    This function differs from is_ltz from floating point argument,
    because Mzero is negative but not less than zero.  and Mzero is
    not positive and not greater than zero, It's probably is_ltz that
    you want.

    @par Semantic:

    @code
    logical<T> r = is_negative(a0);
    @endcode

    is similar to:

    @code
    if T is signed
      logical<T> r = bitofsign(a0) == 1;
    else
      logical<T> r = False;
    @endcode

    @par Note:

    Mzero is the floating point 'minus zero',
    i.e. all bits are zero but the sign bit.
    Such a value is treated as zero by ieee standards.

    @param a0

    @return a logical value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_negative_, is_negative, 1)
} }

#endif

