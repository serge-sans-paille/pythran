//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DEINTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DEINTERLEAVE_SECOND_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd {
  namespace tag
  {
   /*!
     @brief deinterleave_second generic tag

     Represents the deinterleave_second function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct deinterleave_second_ : ext::unspecified_<deinterleave_second_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<deinterleave_second_> parent;
    };
  }

  /*!
    Computes a vector from a combination of the two inputs.

    @par Semantic:

    For every parameters of type T0:

    @code
    T0 r = deinterleave_second(a,b);
    @endcode

    is equivalent to :

    @code
    r = [ a[1] a[3] ... a[n/2+1] b[1] b[3] ... b[n/2+1] ]
    @endcode

    with <tt> n = cardinal_of<T>::value </tt>

    @param a0 First vector to deinterleave
    @param a1 Second vector to deinterleave


    @return a value of the same type as the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::deinterleave_second_, deinterleave_second, 2)

} }

#endif
