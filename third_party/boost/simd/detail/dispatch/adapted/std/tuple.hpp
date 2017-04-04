//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_STD_TUPLE_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_STD_TUPLE_HPP_INCLUDED

#include <tuple>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/simd/detail/dispatch/detail/hierarchy_of.hpp>
#include <boost/simd/detail/dispatch/adapted/hierarchy/tuple.hpp>
#include <boost/simd/detail/dispatch/meta/is_homogeneous.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace tt = nsm::type_traits;
  namespace detail
  {
    template<typename T, typename Origin, bool IsHomo>
    struct hierarchy_of_tuple
    {
      using first = typename std::tuple_element<0,T>::type;
      using sz    = std::tuple_size<T>;
      using type = bag_ < boost::dispatch::property_of_t<first,Origin>
                        , tt::integral_constant<std::size_t, sz::value>
                        >;
    };

    template<typename T, typename Origin>
    struct hierarchy_of_tuple<T,Origin, false>
    {
      using sz   = std::tuple_size<T>;
      using type = tuple_<Origin, tt::integral_constant<std::size_t, sz::value>>;
    };

  }
  namespace ext
  {
    template<typename T, typename... Ts, typename Origin>
    struct  hierarchy_of < std::tuple<T,Ts...>, Origin >
          : detail::hierarchy_of_tuple< std::tuple<T,Ts...>,Origin
                                      , is_homogeneous<std::tuple<T,Ts...>>::value
                                      >
    {};

    template<typename Origin>
    struct hierarchy_of<std::tuple<>,Origin>
    {
      using type = tuple_<Origin, tt::integral_constant<std::size_t,0u>>;
    };
  }
} }

#endif
