//==================================================================================================
/*!
  @file

  Defines the pack_ hierarchy

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_HIERARCHY_SIMD_HPP_INCLUDED
#define BOOST_SIMD_META_HIERARCHY_SIMD_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/forward.hpp>
#include <boost/simd/detail/dispatch/hierarchy/generic.hpp>
#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/meta/value_of.hpp>
#include <boost/simd/detail/dispatch/meta/model_of.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/simd/detail/dispatch/property_of.hpp>

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  template<typename T, typename X>
  struct  pack_ // Doxygen does not like inheritance
  {
    using parent = pack_<typename T::parent, X>;
  };
#else
  template<typename T, typename X>
  struct  pack_ : pack_<typename T::parent, X>
  {
    using parent = pack_<typename T::parent, X>;
  };

  template<typename T,typename X>
  struct  pack_< boost::dispatch::unspecified_<T>, X >
        : boost::dispatch::generic_<boost::dispatch::property_of_t<T>>
  {
    using parent = boost::dispatch::generic_<boost::dispatch::property_of_t<T>>;
  };
#endif
} }

namespace boost { namespace dispatch
{
  namespace ext
  {
    template<typename T,std::size_t N> struct model_of<boost::simd::pack<T,N>>
    {
      template<typename X> struct apply { using type = boost::simd::pack<X,N>; };
    };

    template<typename T,std::size_t N> struct value_of<boost::simd::pack<T,N>>
    {
      using type = T;
    };

    template<typename T,std::size_t N> struct scalar_of<boost::simd::pack<T,N>>
    {
      using type = T;
    };

    template<typename T, std::size_t N, typename ABI,typename Origin>
    struct hierarchy_of<boost::simd::pack<T,N,ABI>,Origin>
    {
      using type = boost::simd::pack_<boost::dispatch::property_of_t<T,Origin>, ABI>;
    };
  }
} }

#endif
