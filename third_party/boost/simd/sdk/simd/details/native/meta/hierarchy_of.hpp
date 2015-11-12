//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_HIERARCHY_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_HIERARCHY_OF_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/property_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class X, class Origin>
  struct hierarchy_of< simd::native<T, X>, Origin>
  {
    typedef typename remove_const<Origin>::type stripped;
    typedef typename mpl::if_< is_same< simd::native<T, X>, stripped >, stripped, Origin>::type origin_;
    typedef simd::ext::simd_<typename property_of<T, origin_>::type, X> type;
  };
} } }

#endif

