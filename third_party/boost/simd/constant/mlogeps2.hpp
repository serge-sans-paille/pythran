//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MLOGEPS2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MLOGEPS2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate \f$-\log(eps^2)\f$ value


    @par Header <boost/simd/constant/mlogeps2.hpp>

    @par Semantic:

    @code
    T r = Mlogeps2<T>();
    @endcode

    is similar to:

    @code
    T r = -log(sqr(Eps<T>()));
    @endcode


    @return The Mlogeps2 constant for the proper type
  **/
  template<typename T> T Mlogeps2();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant mlogeps2.

      @return The Mlogeps2 constant for the proper type
    **/
    const boost::dispatch::functor<tag::mlogeps2_> mlogeps2 = {};
  }
} }
#endif

#include <boost/simd/constant/scalar/mlogeps2.hpp>
#include <boost/simd/constant/simd/mlogeps2.hpp>

#endif
