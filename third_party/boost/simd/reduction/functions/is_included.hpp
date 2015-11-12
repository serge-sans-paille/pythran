//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_IS_INCLUDED_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_IS_INCLUDED_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief is_included generic tag

     Represents the is_included function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct is_included_ : ext::unspecified_<is_included_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<is_included_> parent;
    };
  }
  /*!
    Returns True is only if all bits set in a0 are also set in a1

    @par Semantic:

    For every parameters of type T0:

    @code
    logical<scalar_of<T0>> r = is_included(a0,a1);
    @endcode

    is similar to:

    @code
    logical<scalar_of<T0>> r = all((a0&a1) == a1);
    @endcode

    @param a0

    @param a1

    @return a value of the scalar logical type associated to the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_included_, is_included, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_included_, testz, 2)
} }

#endif

