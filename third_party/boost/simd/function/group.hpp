//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_GROUP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_GROUP_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  /*!
    @ingroup group-swar
    Function object implementing group capabilities

    take two SIMD vectors of same type and elements of size n
    and return a vector collecting the two in a vector in which
    the elements have size n/2

    Of course the applicability is conditioned by the existence of compatible
    SIMD vector types

    @par Semantic:

    For every parameters of type T0

    @code
    downgrade<T0> r = group(x, y);
    @endcode

    is similar to:

    @code
    downgrade<T0> r;
    for(int i=0;i < T0::static_size; ++i)
      r[i] = x[i];
      r[i+T0::static_size] = y[i];
    @endcode
  **/
  downgrade<Value> group(Value const& x, Value const& y);
#endif
} }

#include <boost/simd/function/simd/group.hpp>

#endif
