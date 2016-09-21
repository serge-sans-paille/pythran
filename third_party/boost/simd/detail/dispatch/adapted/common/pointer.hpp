//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_COMMON_POINTER_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_COMMON_POINTER_HPP_INCLUDED

#include <boost/simd/detail/dispatch/adapted/hierarchy/pointer.hpp>
#include <boost/simd/detail/dispatch/meta/pointer_rank.hpp>
#include <boost/simd/detail/dispatch/meta/value_of.hpp>
#include <boost/simd/detail/dispatch/meta/model_of.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/simd/detail/dispatch/detail/is_pointer.hpp>
#include <boost/pointee.hpp>

namespace boost { namespace dispatch
{
  namespace ext
  {
    template<typename T>
    struct model_of<T, typename std::enable_if<detail::is_pointer<T>::value>::type>
    {
      template<typename X> struct apply : std::add_pointer<X> {};
    };

    template<typename T>
    struct  value_of<T, typename std::enable_if<detail::is_pointer<T>::value>::type>
          : boost::pointee<T>
    {};

    template<typename T, typename Origin>
    struct hierarchy_of < T, Origin
                        , typename std::enable_if<detail::is_pointer<T>::value>::type
                        >
    {
      using pointee_t = typename dispatch::remove_pointers<T>::type;
      using type      = pointer_< boost::dispatch::hierarchy_of_t<pointee_t,Origin>
                                , pointer_rank<T>::value
                                >;
    };
  }
} }

#endif
