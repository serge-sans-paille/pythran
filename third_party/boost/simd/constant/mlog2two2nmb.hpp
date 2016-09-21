//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MLOG2TWO2NMB_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MLOG2TWO2NMB_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Generates constant Mlog2two2nmb.

    @par Semantic:

    @code
    T r = Mlog2two2nmb<T>();
    @endcode

    is similar to:

    @code
      r =  T(Nbmantissabits<T>());
    @endcode


**/
  template<typename T> T Mlog2two2nmb();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Generates constant Mlog2two2nmb.

      Generate the  constant mlog2two2nmb.

      @return The Mlog2two2nmb constant for the proper type
    **/
    const boost::dispatch::functor<tag::mlog2two2nmb_> mlog2two2nmb = {};
  }
} }
#endif

#include <boost/simd/constant/definition/mlog2two2nmb.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
