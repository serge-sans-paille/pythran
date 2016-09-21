//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MLOG10TWO2NMB_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MLOG10TWO2NMB_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Generates constant Mlog10two2nmb.

    @par Semantic:

    @code
    T r = Mlog10two2nmb<T>();
    @endcode

    is similar to:

    @code
      r =  -log10(exp2(T(Nbmantissabits<T>())));
    @endcode


**/
  template<typename T> T Mlog10two2nmb();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Generates constant Mlog10two2nmb.

      Generate the  constant mlog10two2nmb.

      @return The Mlog10two2nmb constant for the proper type
    **/
    const boost::dispatch::functor<tag::mlog10two2nmb_> mlog10two2nmb = {};
  }
} }
#endif

#include <boost/simd/constant/definition/mlog10two2nmb.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
