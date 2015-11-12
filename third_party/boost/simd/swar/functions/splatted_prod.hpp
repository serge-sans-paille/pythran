//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_PROD_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_PROD_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief splatted_prod generic tag

      Represents the splatted_prod function in generic contexts.
    **/
    struct splatted_prod_ : ext::unspecified_<splatted_prod_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<splatted_prod_> parent;
    };
  }

  /*!
    @brief Splatted product

    Computes the splatted product of the element of its argument.

    @par Semantic

    @code
    Type r = splatted_prod(v);
    @endcode

    If @c Type is a SIMD value, this code is equivalent to:

    @code
    for(int i=0;i<Type::static_size;++i)
      x[i] = prod(v);
    @endcode


    @param a0

    @return a value of the same type as the parameter
  */
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::splatted_prod_, splatted_prod, 1)
} }

#endif
