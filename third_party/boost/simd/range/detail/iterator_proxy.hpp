//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAIL_ITERATOR_PROXY_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAIL_ITERATOR_PROXY_HPP_INCLUDED

#include <boost/simd/pack.hpp>
#include <boost/simd/detail/pack_proxy.hpp>
#include <boost/simd/range/detail/dereferencable.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace boost { namespace simd { namespace detail
{
  /*
    Make a pack-compatible proxy from the dereferenced data out of simd::(aligned_)iterator
    so both input and output iterator semantic are satisfied.
  */
  template<typename V, std::size_t C, typename L, typename S>
  struct pack_proxy<dereferencable<V,C,L,S>>
      : public pack_proxy_base<pack_proxy<dereferencable<V,C,L,S>>>
  {
    using deref_t     = dereferencable<V,C,L,S>;
    using value_type  = typename std::decay<V>::type;
    using base_type   = pack<value_type,C>;

    BOOST_FORCEINLINE pack_proxy(dereferencable<V,C,L,S> const& data) : data_(data) {}

    BOOST_FORCEINLINE
    base_type  get() const BOOST_NOEXCEPT                   { return data_.get(); }
    BOOST_FORCEINLINE
    void       set(base_type const& other) BOOST_NOEXCEPT   { data_.set(other);   }
    BOOST_FORCEINLINE
               operator base_type() const BOOST_NOEXCEPT    { return get();       }

    // ---------------------------------------------------------------------------------------------
    // Starts emulating pack interface

    enum { static_size = base_type::static_size };
    enum { alignment = base_type::alignment };

    using size_type       = typename base_type::size_type;
    using storage_type    = typename base_type::storage_type;
    using reference       = typename base_type::reference;
    using const_reference = typename base_type::const_reference;

    using iterator               = typename deref_t::raw_type*;
    using const_iterator         = typename deref_t::raw_type const*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    template<typename U>                using rebind = pack<U,C>;
    template<std::size_t M>             using resize = pack<value_type,M>;
    template<typename U,std::size_t M>  using retype = pack<U,M>;

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

    static BOOST_FORCEINLINE size_type size()     BOOST_NOEXCEPT { return static_size; }
    static BOOST_FORCEINLINE size_type max_size() BOOST_NOEXCEPT { return static_size; }
    static BOOST_FORCEINLINE bool empty()         BOOST_NOEXCEPT { return false; }

    BOOST_FORCEINLINE storage_type const& storage() const BOOST_NOEXCEPT { return get().storage(); }

    BOOST_FORCEINLINE reference operator[](std::size_t i)             { return data_.ptr[i]; }
    BOOST_FORCEINLINE const_reference operator[](std::size_t i) const { return data_.ptr[i]; }

    /// @brief Returns an iterator to the beginning of the pack
    BOOST_FORCEINLINE iterator       begin()        BOOST_NOEXCEPT { return data_.ptr; }
    BOOST_FORCEINLINE const_iterator begin() const  BOOST_NOEXCEPT { return data_.ptr; }

    BOOST_FORCEINLINE iterator        end()       BOOST_NOEXCEPT { return begin()+C; }
    BOOST_FORCEINLINE const_iterator  end() const BOOST_NOEXCEPT { return begin()+C; }

    BOOST_FORCEINLINE const_iterator cbegin() const BOOST_NOEXCEPT { return data_.ptr; }
    BOOST_FORCEINLINE const_iterator cend()   const BOOST_NOEXCEPT { return data_.ptr+C; }

    BOOST_FORCEINLINE reverse_iterator rbegin() BOOST_NOEXCEPT
    {
      return reverse_iterator(end());
    }

    BOOST_FORCEINLINE const_reverse_iterator rbegin() const BOOST_NOEXCEPT
    {
      return reverse_iterator(end());
    }

    BOOST_FORCEINLINE reverse_iterator rend() BOOST_NOEXCEPT
    {
      return reverse_iterator(begin());
    }

    BOOST_FORCEINLINE const_reverse_iterator rend() const BOOST_NOEXCEPT
    {
      return reverse_iterator(begin());
    }

    BOOST_FORCEINLINE const_reverse_iterator crbegin() const BOOST_NOEXCEPT
    {
      return const_reverse_iterator(cend());
    }

    BOOST_FORCEINLINE const_reverse_iterator crend() const BOOST_NOEXCEPT
    {
      return const_reverse_iterator(cbegin());
    }

    reference       back()         { return *(begin() + static_size-1); }
    const_reference back()  const  { return *(begin() + static_size-1); }
    reference       front()        { return *begin(); }
    const_reference front() const  { return *begin(); }

    private:
    dereferencable<V,C,L,S> data_;
  };
} } }

#endif
