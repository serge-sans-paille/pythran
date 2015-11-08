//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_INTERLEAVE_ODD_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_INTERLEAVE_ODD_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd {
  namespace tag
  {
   /*!
     @brief interleave_odd generic tag

     Represents the interleave_odd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct interleave_odd_ : ext::unspecified_<interleave_odd_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<interleave_odd_> parent;
    };
  }

  /*!
    Computes a vector from a combination of the two inputs.

    @par Semantic:

    For every parameters of types respectively T0:

    @code
    T0 r = interleave_odd(a,b);
    @endcode

    is equivalent to :

    @code
    r = [ a[1] b[1] a[3] b[3] ... a[n/2+1] b[n/2+1] ]
    @endcode

    with <tt> n = cardinal_of<T>::value </tt>

    @param a0 First vector to interleave
    @param a1 Second vector to interleave

    @return a value of the same type as the parameters
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::interleave_odd_, interleave_odd, 2)

} }

#endif
