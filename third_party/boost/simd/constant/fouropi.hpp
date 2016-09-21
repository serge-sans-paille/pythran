//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FOUROPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FOUROPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Constant \f$\frac4\pi\f$.

    @par Semantic:

    For type T:

    @code
    T r = Fouropi<T>();
    @endcode

    is similar to:

    @code
    T r = Four<T>()/Pi<T>();
    @endcode

    @return a value of type T

**/
  template<typename T> T Fouropi();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Constant \f$\frac4\pi\f$.

      Generate the  constant fouropi.

      @return The Fouropi constant for the proper type
    **/
    Value Fouropi();
  }
} }
#endif

#include <boost/simd/constant/definition/fouropi.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
