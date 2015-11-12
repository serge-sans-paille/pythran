//==============================================================================
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_IS_DOWNGRADABLE_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_IS_DOWNGRADABLE_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/extension_of.hpp>
#include <boost/simd/sdk/simd/meta/has_extension.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace simd { namespace meta
{
  /*!
    @brief is A0 downgradable to A1 ?
  **/
  template<typename A0, typename A1>
  struct is_downgradable_to
       : boost::is_same< A1
                       , typename dispatch::meta::downgrade<A0>::type
                       >
  {};

  /*!
    @brief is A0 downgradable ? i.e. isn't (u)int8 or float
  **/
  template<typename A0>
  struct is_downgradable
       : mpl::not_< is_downgradable_to<A0, A0> >
  {
  };

  /*!
    @brief is A0 downgradable with the same SIMD extension ?
  **/
  template<typename A0, typename X = typename meta::extension_of<A0>::type>
  struct is_downgradable_on_ext
       : mpl::and_< is_downgradable<A0>
                  , has_extension<typename dispatch::meta::downgrade<A0>::type,X>
                  >
  {
  };

  /*!
    @brief  is A0 downgradable with the same SIMD extension
            and so does its real equivalent ?
  **/
  template<typename A0, typename X = typename meta::extension_of<A0>::type>
  struct is_downgradable_as_real_on_ext
       : mpl::and_< is_downgradable_on_ext<A0,X>
                  , mpl::not_
                    < is_same < dispatch::meta::na_
                              , typename meta::as_simd
                                < typename dispatch::meta::as_floating
                                          < typename dispatch::meta::downgrade
                                            <
                                              typename A0::value_type
                                            >::type
                                          >::type
                                , X
                                >::type
                              >
                    >
                  >
  {
  };
} } }

#endif
