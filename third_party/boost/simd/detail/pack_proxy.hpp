//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_PACK_PROXY_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_PACK_PROXY_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/value_of.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/simd/detail/pack_proxy_base.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace detail
{
  template<typename Storage>
  struct pack_proxy : public pack_proxy_base<pack_proxy<Storage>>
  {
    using base_type = typename Storage::value_type;

    BOOST_FORCEINLINE   pack_proxy(Storage* data, std::size_t index)
                      : data_(data), index_(index) {}

    BOOST_FORCEINLINE
    base_type get() const BOOST_NOEXCEPT             { return data_->get( index_ ); }

    BOOST_FORCEINLINE
    void set(base_type const& other) BOOST_NOEXCEPT  { data_->set(index_,other); }

    BOOST_FORCEINLINE pack_proxy& operator=(base_type const& other) BOOST_NOEXCEPT
    {
      set(other);
      return *this;
    }

    BOOST_FORCEINLINE pack_proxy& operator=(pack_proxy const& other) BOOST_NOEXCEPT
    {
      set(other.get());
      return *this;
    }

    BOOST_FORCEINLINE operator base_type() const BOOST_NOEXCEPT { return get(); }

    private:
    Storage*    data_;
    std::size_t index_;
  };

  template<typename T> struct is_proxy<pack_proxy<T>> : std::true_type {};
} } }

namespace boost { namespace dispatch
{
  namespace ext
  {
    template<typename S>
    struct  value_of<boost::simd::detail::pack_proxy<S>>
          : dispatch::value_of<typename S::value_type>
    {};

    template<typename S> struct scalar_of<boost::simd::detail::pack_proxy<S>>
          : dispatch::scalar_of<typename S::value_type>
    {};

    template<typename S,typename Origin>
    struct  hierarchy_of<boost::simd::detail::pack_proxy<S>,Origin>
          : dispatch::hierarchy_of<typename S::value_type>
    {};
  }
} }
#endif
