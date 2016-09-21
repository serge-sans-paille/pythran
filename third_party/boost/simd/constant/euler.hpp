//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_EULER_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_EULER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    GeneratesEuler constant.

    @par Semantic:
    The Euler constant can be defined as \f$\displaystyle \lim_{n \rightarrow \infty} \left(\sum_1^n \frac1n -\log n\right)\f$

    @code
    T r = Euler<T>();
    @endcode

    is similar to:

    @code
      r =  T(0.577215664901532860606512090082402431042159335939923598805767234884867726777664670936947063291746749);
    @endcode


**/
  template<typename T> T Euler();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      GeneratesEuler constant.

      Generate the  constant euler.

      @return The Euler constant for the proper type
    **/
    Value Euler();
  }
} }
#endif

#include <boost/simd/constant/definition/euler.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
