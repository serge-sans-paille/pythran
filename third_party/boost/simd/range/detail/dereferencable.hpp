//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAIL_DEREFERENCABLE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAIL_DEREFERENCABLE_HPP_INCLUDED

#include <boost/simd/pack.hpp>
#include <boost/simd/as.hpp>
#include <boost/config.hpp>
#include <type_traits>

namespace boost { namespace simd { namespace detail
{
  /*
    This proxy type is returned by dereferencing simd::iterator and encapsulates
    the needed load/store calls.
  */
  template<typename V, std::size_t C, typename Load, typename Store>
  struct dereferencable
  {
    // use decay to remove potential const from V
    using value_type = pack<typename std::decay<V>::type,C>;
    using raw_type = V;

    BOOST_FORCEINLINE value_type get() const BOOST_NOEXCEPT
    {
      return dispatch::functor<Load>()( ptr, dispatch::as_<value_type>() );
    }

    BOOST_FORCEINLINE void set(value_type const& other) BOOST_NOEXCEPT
    {
      dispatch::functor<Store>()(other, ptr);
    }

    V* ptr;
  };

  // Small helper to handle const/non-const pointer wrapping
  template<std::size_t C, typename Load, typename Store,typename V>
  BOOST_FORCEINLINE dereferencable<V,C,Load,Store> make_deref(V* p)
  {
    return dereferencable<V,C,Load,Store>{p};
  }

  template<std::size_t C, typename Load, typename Store,typename V>
  BOOST_FORCEINLINE dereferencable<V const,C,Load,Store> make_deref(V const* p)
  {
    return dereferencable<V const,C,Load,Store>{p};
  }
} } }

#endif
