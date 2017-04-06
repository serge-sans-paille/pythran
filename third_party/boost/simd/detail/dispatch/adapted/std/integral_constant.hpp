//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_STD_INTEGRAL_CONSTANT_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_STD_INTEGRAL_CONSTANT_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/value_of.hpp>
#include <boost/simd/detail/dispatch/meta/model_of.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/simd/detail/dispatch/adapted/hierarchy/integral_constant.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace tt = nsm::type_traits;
  // model/value_of adaptation
  namespace ext
  {
    template<typename T, T N> struct model_of<tt::integral_constant<T,N>>
    {
      template<typename X> struct apply { using type = tt::integral_constant<X,X(N)>; };
    };

    template<typename T, T N> struct value_of<tt::integral_constant<T,N>>
    {
      using type = T;
    };
  }

  namespace ext
  {
    // integral_constant<T,N> hierarchies as constant_< (u)int{8,16,32,64}<Origin> >
    template<typename T, T N, typename Origin>
    struct hierarchy_of<tt::integral_constant<T,N>,Origin>
    {
      using type = constant_< boost::dispatch::property_of_t<T,Origin> >;
    };
  }

} }

#endif
