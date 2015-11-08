//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_REPEAT_LOWER_HALF_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_REPEAT_LOWER_HALF_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>



namespace boost { namespace simd {
  namespace tag
  {
   /*!
     @brief repeat_lower_half generic tag

     Represents the repeat_lower_half function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct repeat_lower_half_ : ext::unspecified_<repeat_lower_half_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<repeat_lower_half_> parent;
    };
  }

  /*!
    Repeat lower half of a vector

    @par Semantic:

    For every parameter of type T0

    @code
    T0 r = repeat_lower_half(a0);
    @endcode

    is similar to:

    @code
      T0 r;
      const std::size_t  middle = meta::cardinal_of<A0>::value/2;
      for(std::size_t i=0;i<middle;++i)
      {
        r[i] = r[i+middle] = a0[i];
      }
    @endcode

    @param a0

    @return a value of the same type as the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::repeat_lower_half_, repeat_lower_half, 1)

} }

#endif
