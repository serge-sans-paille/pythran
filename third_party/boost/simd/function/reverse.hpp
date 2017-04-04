//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REVERSE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-swar
    Function object implementing reverse

    Returns a vector containing the value of its argument in reverse order.


    @par Header <boost/simd/function/reverse.hpp>

    @par Semantic:

    For every parameter of type T

    @code
    T r = reverse(x);
    @endcode

    is similar to:

    @code
    T r;
    for(size_t i=0;i<cardinal_of<T>;++i)
      r[i] = x[cardinal_of<T>-i-1];
    @endcode
  **/
  Value reverse(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/reverse.hpp>
#include <boost/simd/function/simd/reverse.hpp>

#endif
