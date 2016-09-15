//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FOURPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FOURPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

   Constant \f$4\pi\f$.

    @par Semantic:

    For type T:

    @code
    T r = Fouropi<T>();
    @endcode

    is similar to:

    @code
    T r = Four<T>()*Pi<T>();
    @endcode

    @return The Fourpi constant for the proper type
  **/
  template<typename T> T Fourpi();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant fourpi.

      @return The Fourpi constant for the proper type
    **/
    Value Fourpi();
  }
} }
#endif

#include <boost/simd/constant/definition/fourpi.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
