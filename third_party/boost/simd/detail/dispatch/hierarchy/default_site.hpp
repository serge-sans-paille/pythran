//==================================================================================================
/*!
  @file

  Generate a default architecture tag

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_DEFAULT_SITE_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_DEFAULT_SITE_HPP_INCLUDED

/*!
  @ingroup group-hierarchy
  @brief Customizable default architecture

  BOOST_DISPATCH_DEFAULT_SITE is to be defined with a proper architectural hierarchy to be used as
  the default architecture for a given translation unit.
**/
#if !defined(BOOST_DISPATCH_DEFAULT_SITE)
#include <boost/simd/detail/dispatch/hierarchy/cpu.hpp>
#define BOOST_DISPATCH_DEFAULT_SITE ::boost::dispatch::cpu_
#endif

namespace boost { namespace dispatch
{
  namespace ext
  {
    /*!
      @ingroup group-ext
      @brief SFINAE-enabled extension point for default_site

      This extension point allows customization of the default_site @metafunction
      by letting user defined SFINAE-enabled context in which they can specialize
      default_site for family of types.

      @tparam Tag     Function tag
      @tparam Enable  SFINAE condition to be specified
    **/
    template<typename Tag, typename Enable = void> struct default_site
    {
      using type = BOOST_DISPATCH_DEFAULT_SITE;
    };
  }

  /*!
    @ingroup group-hierarchy
    @brief Preferred architecture tag

    For any function Tag, returns the hierarchy of the preferred architecture this function should
    be dispatched to.

    @tparam Tag Function tag
  **/
  template<typename Tag>
  using default_site = typename ext::default_site<Tag>::type;
} }

#endif
