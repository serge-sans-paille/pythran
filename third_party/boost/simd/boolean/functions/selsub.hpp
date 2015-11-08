///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SELSUB_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SELSUB_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief selsub generic tag

     Represents the selsub function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct selsub_ : ext::elementwise_<selsub_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<selsub_> parent;
    };
  }
  /*!

    The function returns the second entry or the difference of the
    second and third entries, according to the first entry being False
    or True

    @par Semantic:

    For every parameters of types respectively T0, T1, T1:

    @code
    T1 r = selsub(a0,a1,a2);
    @endcode

    is similar to:

    @code
    T1 r = a0 ? a1-a2 : a1;
    @endcode

    @par Alias:
    @c ifsub

    @param a0

    @param a1

    @param a2

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::selsub_, selsub, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::selsub_, ifsub,  3)
} }

#endif

