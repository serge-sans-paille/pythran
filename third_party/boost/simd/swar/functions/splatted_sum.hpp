//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_SUM_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_SUM_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief splatted_sum generic tag

      Represents the splatted_sum function in generic contexts.
    **/
    struct splatted_sum_ : ext::unspecified_<splatted_sum_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<splatted_sum_> parent;
    };
  }

  /*!
    @brief Splatted sum

    Computes the splatted sum of the element of its argument.

    @par Semantic

    Depending on the type of its arguments, splatted_sum exhibits different
    semantics. For any type @c Type and value @c v of type @c Type:

    @code
    Type r = splatted_sum(v);
    @endcode

    If @c Type is a SIMD value, this code is equivalent to:

    @code
    for(int i=0;i<Type::static_size;++i)
      x[i] = sum(v);
    @endcode

    If @c Type is a scalar type, then it is equivalent to:

    @code
    r = v;
    @endcode

    @param a0 value to sum

    @return A value containign the splatted sum of @c a0
  */
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::splatted_sum_, splatted_sum, 1)
} }

#endif
