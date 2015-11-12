//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_POSMIN_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_POSMIN_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief posmin generic tag

     Represents the posmin function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct posmin_ : ext::unspecified_<posmin_>
    {
      /// @brief Parent hierarchy
       typedef ext::unspecified_<posmin_> parent;
    };
  }
  /*!
    Returns the index of the first occurence of least element of the SIMD vector

    @par Semantic:

    For every parameter of type T0

    @code
    size_t r = posmin(a0);
    @endcode

    is similar to:

    @code
      T0 m =  minimum(a0);
      size_t r;
      for(size_t i=0; i < cardinal_of<T0>; i++)
        if (m == a0[i]) { r = i;  break; }
    @endcode

    @param a0

    @return a size_t value
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::posmin_, posmin, 1)
} }
#endif

