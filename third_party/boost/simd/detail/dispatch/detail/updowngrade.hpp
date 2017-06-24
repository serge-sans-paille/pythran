//==================================================================================================
/*!
  @file

  Defines the downgrade meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_DETAIL_UPDOWNGRADE_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_DETAIL_UPDOWNGRADE_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/primitive_of.hpp>
#include <boost/simd/detail/dispatch/meta/factory_of.hpp>
#include <boost/simd/detail/dispatch/meta/sign_of.hpp>
#include <boost/simd/detail/dispatch/meta/make_integer.hpp>
#include <boost/simd/detail/dispatch/meta/apply_sign.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch { namespace detail
{
  template<typename T, typename Map, typename Sign, bool Direction, bool IsReal> struct fetch
  {
    using type = nsm::at<Map,T>;
  };

  template<typename T, typename Map, typename Sign, bool Direction>
  struct fetch<T,Map,Sign,Direction,false>
  {
    // Normalize T
    using base = dispatch::make_integer_t<sizeof(T),unsigned>;
    using found = nsm::at<Map,base>;
    using type  = boost::dispatch::apply_sign_t<found,Sign>;
  };

  template<typename Map, typename Sign> struct fetch<bool,Map,Sign,false,false>
  {
    using type = nsm::at<Map,bool>;
  };

  template<typename T,typename Sign,typename Map, bool Direction> struct updowngrade
  {
    // Decompose in factory/primitive
    using f_t = boost::dispatch::factory_of<T>;
    using p_t = boost::dispatch::primitive_of_t<T>;

    // Fetch from a normalized pool of types if required by the Direction of the transformation
    using d_t = typename fetch<p_t,Map,Sign,Direction,std::is_floating_point<p_t>::value>::type;

    // Reconstruct
    using type = typename f_t::template apply<d_t>::type;
  };
} } }

#endif
