//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_EULERIAN_HPP_INCLUDED
#define BOOST_SIMD_EULERIAN_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-functions
    @defgroup group-euler Eulerian functions

    Algorithms for computing scalar and SIMD versions of
    some Eulerian functions. Mainly those that are present in
    stdlibc++ 11.

      <center>
        |                |                |               |                |
        |:--------------:|:--------------:|:-------------:|:--------------:|
        | @ref erf       |  @ref erfc     | @ref erfcx    |   @ref gamma   |
        | @ref gammaln   |  @ref signgam  | @ref stirling |                |
      </center>

  **/

} }

#include <boost/simd/function/erfc.hpp>
#include <boost/simd/function/erfcx.hpp>
#include <boost/simd/function/erf.hpp>
#include <boost/simd/function/gamma.hpp>
#include <boost/simd/function/gammaln.hpp>
#include <boost/simd/function/signgam.hpp>
#include <boost/simd/function/stirling.hpp>

#endif
