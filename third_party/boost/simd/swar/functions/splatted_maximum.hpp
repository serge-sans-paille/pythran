//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_MAXIMUM_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_MAXIMUM_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief splatted_maximum generic tag

     Represents the splatted_maximum function in generic contexts.

     @par Models:
        Hierarchy
   **/
    /*!
      @brief splatted_maximum generic tag

      Represents the splatted_maximum function in generic contexts.
    **/
    struct splatted_maximum_ : ext::unspecified_<splatted_maximum_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<splatted_maximum_> parent;
    };
  }
  /*!
    @brief Splatted maximum

    Computes the splatted maximum of the element of its argument.

    @par Semantic

    Depending on the type of its arguments, splatted_maximum exhibits different
    semantics. For any type @c Type and value @c v of type @c Type:

    @code
    Type r = splatted_maximum(v);
    @endcode

    is similar to:

    @code
    for(int i=0;i<Type::static_size;++i)
      x[i] = maximum(v);
    @endcode

    @param a0

    @return a value of the same type as the parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::splatted_maximum_, splatted_maximum, 1)
} }

#endif
