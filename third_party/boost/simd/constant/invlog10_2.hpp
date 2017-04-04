//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INVLOG10_2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INVLOG10_2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Generates constant  1/log10(2).


    @par Header <boost/simd/constant/invlog10_2.hpp>

    @par Semantic:

    @code
    T r = invlog10_2<T>();
    @endcode


    is similar to:

    @code
    T r =  T(3.32192809488736234787031942949);
    @endcode

**/
  template<typename T> T Invlog10_2();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Generates constant  1/log10(2).

      Generate the  constant invlog10_2.

      @return The Invlog10_2 constant for the proper type
    **/
    const boost::dispatch::functor<tag::invlog10_2_> invlog10_2 = {};
  }
} }
#endif

#include <boost/simd/constant/scalar/invlog10_2.hpp>
#include <boost/simd/constant/simd/invlog10_2.hpp>

#endif
