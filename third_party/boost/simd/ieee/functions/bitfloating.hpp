//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_BITFLOATING_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_BITFLOATING_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief bitfloating generic tag

     Represents the bitfloating function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct bitfloating_ : ext::elementwise_<bitfloating_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<bitfloating_> parent;
    };
  }
  /*!
    Transform a pattern of bits stored in an integer value
    in a floating point with different formulas according to
    the integer sign (converse of bitinteger)

    @par Semantic:

    @code
    as_floating<T> r = bitfloating(a0);
    @endcode

    is similar to:

    @code
    as_floating<T> r =  bitwise_cast<as_floating<T> >
              (a0 >=0 ? a0 : Signmask<T>()-a0);
    @endcode

    @param a0

    @return a value of the floating type associated to the input
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitfloating_, bitfloating, 1)
} }

#endif
