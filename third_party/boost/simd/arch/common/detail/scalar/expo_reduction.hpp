//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SCALAR_EXPO_REDUCTION_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SCALAR_EXPO_REDUCTION_HPP_INCLUDED


namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    template< class A0, class Tag, class Base_A0 = bd::scalar_of_t<A0> >
    struct exp_reduction;
  }
} }

#include <boost/simd/arch/common/detail/generic/d_expo_reduction.hpp>
#include <boost/simd/arch/common/detail/generic/f_expo_reduction.hpp>

#endif
