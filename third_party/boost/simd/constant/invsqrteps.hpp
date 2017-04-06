//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INVSQRTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INVSQRTEPS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate  value \f$\1/sqrt(Eps<T>()\f$

    @return The Invsqrteps constant for the proper type
  **/
  template<typename T> T invsqrteps();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant Invsqrteps.

      @return The invsqrteps constant for the proper type
    **/
    const boost::dispatch::functor<tag::invsqrteps_> invsqrteps = {};
  }
} }
#endif

#include <boost/simd/constant/scalar/invsqrteps.hpp>
#include <boost/simd/constant/simd/invsqrteps.hpp>

#endif
