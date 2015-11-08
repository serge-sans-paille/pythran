//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_HMSB_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_HMSB_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief hmsb generic tag

     Represents the hmsb function in generic contexts.

     @par Models:
        Hierarchy
   **/

    struct hmsb_ : ext::unspecified_<hmsb_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<hmsb_> parent;
    };
  }
  /*!
    Returns a size_t value composed by the highiest bits.
    of each vector element

    @par Semantic:

    For every parameter of type T0

    @code
    size_t r = hmsb(a0);
    @endcode

    is similar to:

    @code
      size_t r = 0;
      for(result_type i = 0; i != cardinal_of<T0>; ++i)
      {
        r |= (bits(a0[i]) >> (sizeof(stype)*8 - 1)) << i;
      }
    @endcode

    @param a0

    @return a size_t value
  **/
    BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::hmsb_, hmsb, 1)
} }
#endif

