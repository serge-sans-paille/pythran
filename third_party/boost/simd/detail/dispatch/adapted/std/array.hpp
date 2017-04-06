//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_STD_ARRAY_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_STD_ARRAY_HPP_INCLUDED

#include <array>
#include <boost/simd/detail/dispatch/meta/value_of.hpp>
#include <boost/simd/detail/dispatch/meta/model_of.hpp>
#include <boost/simd/detail/dispatch/adapted/hierarchy/array.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace ext
  {
    namespace tt = nsm::type_traits;
    template<typename T, std::size_t N> struct model_of<std::array<T,N>>
    {
      template<typename X> struct apply { using type = std::array<X,N>; };
    };

    template<typename T, std::size_t N> struct value_of<std::array<T,N>>
    {
      using type = T;
    };

    template<typename T, std::size_t N, typename Origin>
    struct hierarchy_of<std::array<T,N>,Origin>
    {
      using type = array_ < boost::dispatch::hierarchy_of_t<T,Origin>
                          , tt::integral_constant<std::size_t, N>
                          >;
    };
  }
} }

#endif
