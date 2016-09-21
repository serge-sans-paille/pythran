//==================================================================================================
/*!
  @file

  Defines the value-based proxy for pack elements

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_PACK_PROXY_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_PACK_PROXY_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/value_of.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/config.hpp>
#include <type_traits>
#include <iostream>

namespace boost { namespace simd { namespace detail
{
  template<typename Storage>
  class pack_proxy {

    public:
    using value_type = typename Storage::value_type;

    BOOST_FORCEINLINE pack_proxy(Storage* data, std::size_t index) : data_(data), index_(index) {}

    BOOST_FORCEINLINE value_type get() const BOOST_NOEXCEPT
    {
      return data_->get( index_ );
    }

    BOOST_FORCEINLINE void set(value_type const& other) BOOST_NOEXCEPT
    {
      data_->set(index_,other);
    }

    BOOST_FORCEINLINE pack_proxy& operator=(value_type const& other) BOOST_NOEXCEPT
    {
      set(other);
      return *this;
    }

    BOOST_FORCEINLINE pack_proxy& operator=(pack_proxy const& other) BOOST_NOEXCEPT
    {
      set(other.get());
      return *this;
    }

    // We do need to take `operator...` as parameter because pasting `operator` and `+` leads to
    // an invalid preprocessing token
#define M0(OP_TOKEN, OP)                                                                           \
    template <typename U>                                                                          \
    BOOST_FORCEINLINE                                                                              \
    pack_proxy& OP_TOKEN(U const& other) BOOST_NOEXCEPT                                            \
    {                                                                                              \
      set(get() OP static_cast<value_type>(other));                                                \
      return *this;                                                                                \
    }                                                                                              \
    BOOST_FORCEINLINE                                                                              \
    pack_proxy& OP_TOKEN(pack_proxy const& other) BOOST_NOEXCEPT                                   \
    {                                                                                              \
      set(get() OP other.get());                                                                   \
      return *this;                                                                                \
    }                                                                                              \
    /**/

    M0(operator+=, +)
    M0(operator-=, -)
    M0(operator*=, *)
    M0(operator/=, /)
    M0(operator%=, %)

#undef  M0

    // operator: (cast)
    BOOST_FORCEINLINE operator value_type() const BOOST_NOEXCEPT
    {
      return get();
    }

    private:
    Storage*    data_;
    std::size_t index_;
  };

#define M0(OP_TOKEN, OP)                                                                           \
  template <typename Storage, typename U>                                                          \
  BOOST_FORCEINLINE typename Storage::value_type                                                   \
  OP_TOKEN(pack_proxy<Storage> const& lhs, U const& rhs) BOOST_NOEXCEPT                            \
  {                                                                                                \
    return lhs.get() OP static_cast<typename Storage::value_type>(rhs);                            \
  }                                                                                                \
  template <typename T, std::size_t N, typename Storage, typename U>                               \
  BOOST_FORCEINLINE typename Storage::value_type                                                   \
  OP_TOKEN(U const& lhs, pack_proxy<Storage> const& rhs) BOOST_NOEXCEPT                            \
  {                                                                                                \
    return static_cast<typename Storage::value_type>(lhs) OP rhs.get();                            \
  }                                                                                                \
  template <typename Storage>                                                                      \
  BOOST_FORCEINLINE typename Storage::value_type                                                   \
  OP_TOKEN( pack_proxy<Storage> const& lhs, pack_proxy<Storage> const& rhs) BOOST_NOEXCEPT         \
  {                                                                                                \
    return static_cast<typename Storage::value_type>(lhs.get() OP rhs.get());                      \
  }                                                                                                \
  /**/

  M0(operator+, +)
  M0(operator-, -)
  M0(operator/, /)
  M0(operator*, *)
  M0(operator%, %)

#undef  M0

#define M0(OP_TOKEN, OP)                                                                           \
  template < typename Storage, typename U                                                          \
           , typename Enable = typename std::enable_if<std::is_arithmetic<U>::value>::type         \
           >                                                                                       \
  BOOST_FORCEINLINE                                                                                \
  bool OP_TOKEN(pack_proxy<Storage> const& lhs, U const& rhs) BOOST_NOEXCEPT                       \
  {                                                                                                \
    return lhs.get() OP rhs;                                                                       \
  }                                                                                                \
  template < typename Storage, typename U                                                          \
           , typename Enable = typename std::enable_if<std::is_arithmetic<U>::value>::type         \
           >                                                                                       \
  BOOST_FORCEINLINE                                                                                \
  bool OP_TOKEN(U const& lhs, pack_proxy<Storage> const& rhs) BOOST_NOEXCEPT                       \
  {                                                                                                \
    return lhs OP rhs.get();                                                                       \
  }                                                                                                \
  template <typename Storage>                                                                      \
  BOOST_FORCEINLINE bool OP_TOKEN ( pack_proxy<Storage> const& lhs                                 \
                                  , pack_proxy<Storage> const& rhs                                 \
                                  ) BOOST_NOEXCEPT                                                 \
  {                                                                                                \
    return lhs.get() OP rhs.get();                                                                 \
  }                                                                                                \
  /**/

  M0(operator==, ==)
  M0(operator!=, !=)

#undef  M0

  // operator: +
  template<typename Storage>
  BOOST_FORCEINLINE
  auto operator+(pack_proxy<Storage> const& p) BOOST_NOEXCEPT -> decltype(+p.get())
  {
    return +p.get();
  }

  // operator: !
  template<typename Storage>
  BOOST_FORCEINLINE bool operator!(pack_proxy<Storage> const& p) BOOST_NOEXCEPT
  {
    return !p.get();
  }

  // operator: <<
  template<typename Storage>
  inline std::ostream& operator<<(std::ostream& os, pack_proxy<Storage> const& p)
  {
    return os << p.get();
  }
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
