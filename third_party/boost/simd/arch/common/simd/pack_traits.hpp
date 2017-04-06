//==================================================================================================
/*!
  @file

  Defines generic functions and traits for SIMD storage used by pack

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_PACK_TRAITS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_PACK_TRAITS_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/simd/detail/pack_traits.hpp>
#include <boost/simd/arch/common/tags.hpp>
#include <boost/simd/arch/spec.hpp>
#include <algorithm>
#include <array>

namespace boost { namespace simd { namespace detail
{
  // emulated_storage: *
  //-----------------------------------------------------------------------------------------------
  template <typename T, std::size_t N>
  class pack_traits<T, N, std::array<T, N> > {
    public:
    using storage_type              = std::array<T, N>;
    using substorage_type           = T;

    using value_type                = T;
    using size_type                 = std::size_t;

    using reference                 = value_type&;
    using const_reference           = value_type const&;

    using static_range              = nsm::range<std::size_t, 0, N>;
    using element_range             = nsm::range<std::size_t, 0, N>;

    using storage_kind              = ::boost::simd::scalar_storage;

    enum {
      static_size  = N,
      element_size = 1,
      alignment = sizeof(T),
      number_of_vectors = 0
    };

    template<typename Pack>
    BOOST_FORCEINLINE static reference at(Pack& d, std::size_t i)
    {
      return (d.storage())[i];
    }

    template<typename Pack>
    BOOST_FORCEINLINE static const_reference at(Pack const& d, std::size_t i)
    {
      return (d.storage())[i];
    }
  };

  // aggregated_storage: *
  //-----------------------------------------------------------------------------------------------
  template <typename T, typename SIMD, std::size_t N, std::size_t NumberOfVectors>
  class pack_traits<T, N, std::array<SIMD, NumberOfVectors> > {
    public:
    enum {
      static_size  = N,
      element_size = N / NumberOfVectors,
      element_mask = element_size-1,
      number_of_vectors = NumberOfVectors
    };

    enum { alignment = SIMD::alignment };

    using storage_type              = std::array<SIMD, NumberOfVectors>;
    using substorage_type           = SIMD;

    using value_type                = T;
    using size_type                 = std::size_t;

    using reference                 = typename SIMD::reference;
    using const_reference           = typename SIMD::const_reference;

    using static_range              = nsm::range<std::size_t, 0, NumberOfVectors>;
    using element_range             = nsm::range<std::size_t, 0, N>;

    using storage_kind              = ::boost::simd::aggregate_storage;

    public:
    template<typename Pack> BOOST_FORCEINLINE
    static reference at(Pack& d, std::size_t i)
    {
      return (d.storage())[(i&element_size) !=0][i&element_mask];
    }

    template<typename Pack> BOOST_FORCEINLINE
    static const_reference at(Pack const& d, std::size_t i)
    {
      return (d.storage())[(i&element_size) !=0][i&element_mask];
    }
  };
} } }

#endif
