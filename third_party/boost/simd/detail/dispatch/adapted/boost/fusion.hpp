//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_BOOST_FUSION_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_ADAPTED_BOOST_FUSION_HPP_INCLUDED

#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/simd/detail/dispatch/detail/hierarchy_of.hpp>
#include <boost/simd/detail/dispatch/adapted/hierarchy/tuple.hpp>
#include <boost/simd/detail/dispatch/meta/is_homogeneous.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace detail
  {
    namespace tt = nsm::type_traits;

    template<typename T, typename Origin, bool IsHomo>
    struct hierarchy_of_tuple
    {
      using first = typename boost::fusion::result_of::value_at<T, boost::mpl::int_<0>>::type;
      using sz    = boost::fusion::result_of::size<T>;
      using type  = bag_< boost::dispatch::property_of_t<first,Origin>
                        , tt::integral_constant<std::size_t, sz::value>
                        >;
    };

    template<typename T, typename Origin>
    struct hierarchy_of_tuple<T,Origin, false>
    {
      using sz   = boost::fusion::result_of::size<T>;
      using type = tuple_<Origin, tt::integral_constant<std::size_t, sz::value>>;
    };
  }

  namespace ext
  {
    template<typename Sequence, typename Origin>
    struct  hierarchy_of< Sequence
                        , Origin
                        , typename std::enable_if < boost::fusion::traits
                                                         ::is_sequence<Sequence>::value
                                                  >::type
                        >
          : detail::hierarchy_of_tuple<Sequence,Origin,is_homogeneous<Sequence>::value>
    {};
  }
} }

#endif
