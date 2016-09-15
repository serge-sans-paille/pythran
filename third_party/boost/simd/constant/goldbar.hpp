//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_GOLDBAR_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_GOLDBAR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the conjugate golden ratio that is \f$\bar\phi = \frac{1-\sqrt5}{2}\f$

    @par Semantic:

    @code
    T r = Goldbar<T>();
    @endcode

    is similar for floating types to:

    @code
    T r = (1-sqrt(T(5)))/2;
    @endcode

    @return The Goldbar constant for the proper type
  **/
  template<typename T> T Goldbar();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant goldbar.

      @return The Goldbar constant for the proper type
    **/
    Value Goldbar();
  }
} }
#endif

#include <boost/simd/constant/definition/goldbar.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
