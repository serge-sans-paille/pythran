//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOOKUP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOOKUP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-swar
    Function object implementing lookup capabilities

    shuffles the elements of x using indices in n


    @par Header <boost/simd/function/lookup.hpp>

    @par Semantic:

    For every parameters of types respectively T, N:

    @code
    T r = lookup(x,n);
    @endcode

    is similar to:

    @code
    T r;
    for(size_t i=0; i < boost::simd::meta::cardinal_of<T>::value; i++)
      r[i] = x[n[i]];
    @endcode

    @par Example:

      @snippet lookup.cpp lookup

    @par Possible output:

      @snippet lookup.txt lookup

  **/
  Value lookup(Value const& x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/lookup.hpp>
#include <boost/simd/function/simd/lookup.hpp>

#endif
