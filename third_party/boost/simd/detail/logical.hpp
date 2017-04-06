//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_LOGICAL_HPP_INCLUDED

#include <boost/config.hpp>

namespace boost { namespace simd { namespace detail
{
  // traits of pack<logical<T>,N> is the one of its underlying type
  template<typename T, std::size_t N, typename Storage>
  class pack_traits<boost::simd::logical<T>, N, Storage>
      : public pack_traits<T, N, Storage>
  {
    public:
    using value_type  = boost::simd::logical<T>;
  };

  // Remove ambiguity with the other pack_traits
  template <typename T, std::size_t N>
  class pack_traits<boost::simd::logical<T>, N, std::array<boost::simd::logical<T>, N> >
  {
    public:
    using storage_type      = std::array<T, N>;
    using value_type        = boost::simd::logical<T>;
    using size_type         = std::size_t;
    using storage_kind      = ::boost::simd::scalar_storage;
    using substorage_type   = T;

    using static_range      = nsm::range<std::size_t, 0, N>;
    using element_range     = nsm::range<std::size_t, 0, N>;

    enum { static_size = N, element_size = 1, number_of_vectors = 0 };
    enum { alignment = sizeof(T) };

    template<typename Pack> BOOST_FORCEINLINE
    static typename Pack::reference at(Pack& d, std::size_t i) BOOST_NOEXCEPT
    {
      return {&d,i};
    }

    template<typename Pack> BOOST_FORCEINLINE
    static typename Pack::const_reference at(Pack const& d, std::size_t i) BOOST_NOEXCEPT
    {
      return {&d,i};
    }
  };

  template <typename T, typename SIMD, std::size_t N, std::size_t NumberOfVectors>
  class pack_traits<boost::simd::logical<T>, N, std::array<SIMD, NumberOfVectors> >
  {
    public:

    using storage_type    = std::array<SIMD, NumberOfVectors>;
    using value_type      = boost::simd::logical<T>;
    using size_type       = std::size_t;
    using reference       = typename SIMD::reference;
    using const_reference = typename SIMD::const_reference;
    using storage_kind    = ::boost::simd::aggregate_storage;
    using substorage_type = SIMD;

    using static_range    = nsm::range<std::size_t, 0, NumberOfVectors>;
    using element_range   = nsm::range<std::size_t, 0, N>;

    enum  { static_size = N
          , element_size = N / NumberOfVectors
          , element_mask = element_size-1
          , number_of_vectors = NumberOfVectors
          };

    enum  { alignment   = SIMD::alignment };

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
