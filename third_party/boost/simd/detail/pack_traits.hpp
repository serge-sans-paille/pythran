//==================================================================================================
/*!
  @file

  Defines traits for pack.

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_PACK_TRAITS_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_PACK_TRAITS_HPP_INCLUDED

#include <boost/simd/arch/common/tags.hpp>
#include <boost/simd/detail/pack_iterator.hpp>
#include <boost/simd/detail/pack_proxy.hpp>
#include <boost/simd/detail/aliasing.hpp>
#include <boost/utility/enable_if.hpp>
#include <iterator>
#include <cstddef>
#include <cstring>

namespace boost { namespace simd
{
  template<typename T> struct logical;
} }

namespace boost { namespace simd { namespace detail
{
  template < typename T
           , std::size_t N
           , typename Storage
           >
  class pack_traits;

  template<typename T, typename P, typename Enable = void> struct pack_references
  {
    using reference       = pack_proxy<P>;
    using const_reference = pack_proxy<P const>;
  };

  template <typename T,typename P>
  struct pack_references<T, P, typename boost::enable_if_has_type<typename T::reference>::type>
  {
    using reference       = typename T::reference;
    using const_reference = typename T::const_reference;
  };

  // Needed for const pack_proxy
  template <typename T, std::size_t N, typename Storage>
  class pack_traits<const T, N, const Storage> : public pack_traits<T, N, Storage> {};
} } }

#define BOOST_SIMD_DEFINE_PACK_TRAITS_TPL(TPL, TYPE, N, VTYPE)                                     \
  template <TPL>                                                                                   \
  class pack_traits<TYPE, N, VTYPE> {                                                              \
                                                                                                   \
    public:                                                                                        \
    using storage_type              = VTYPE;                                                       \
    using substorage_type           = VTYPE;                                                       \
                                                                                                   \
    using value_type                = TYPE;                                                        \
    using size_type                 = std::size_t;                                                 \
                                                                                                   \
    enum {                                                                                         \
      static_size = N,                                                                             \
      element_size = 1,                                                                            \
      number_of_vectors = 1,                                                                       \
      alignment = sizeof(VTYPE)                                                                    \
    };                                                                                             \
                                                                                                   \
    using static_range            = nsm::range<std::size_t, 0, N>;                             \
    using element_range           = nsm::range<std::size_t, 0, N>;                             \
                                                                                                   \
    using storage_kind            = ::boost::simd::native_storage;                                 \
                                                                                                   \
    template<typename Pack> BOOST_FORCEINLINE                                                      \
    static typename Pack::reference at(Pack& d, std::size_t i) BOOST_NOEXCEPT                      \
    {                                                                                              \
      return {&d,i};                                                                               \
    }                                                                                              \
                                                                                                   \
    template<typename Pack> BOOST_FORCEINLINE                                                      \
    static typename Pack::const_reference at(Pack const& d, std::size_t i) BOOST_NOEXCEPT          \
    {                                                                                              \
      return {&d,i};                                                                               \
    }                                                                                              \
  }                                                                                                \
/**/

#define BOOST_SIMD_DEFINE_PACK_TRAITS(TYPE, N, VTYPE)                                              \
BOOST_SIMD_DEFINE_PACK_TRAITS_TPL(BOOST_PP_EMPTY(), TYPE, N, VTYPE)                                \
/**/

#endif
