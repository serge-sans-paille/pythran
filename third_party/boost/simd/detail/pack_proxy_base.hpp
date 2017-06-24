//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_PACK_PROXY_BASE_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_PACK_PROXY_BASE_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/config.hpp>
#include <iostream>

namespace boost { namespace simd { namespace detail
{
  /*
    pack_proxy_base factorizes all the generic code shared by all pack_proxy specialization
    so operator and other repetitive tasks are not done twice.
  */
  template<typename Derived> struct pack_proxy_base
  {
    Derived&        self()        { return static_cast<Derived&      >(*this); }
    Derived const&  self() const  { return static_cast<Derived const&>(*this); }

    template<typename U> BOOST_FORCEINLINE void set(U const& other) BOOST_NOEXCEPT
    {
      self().set(other);
    }

    // We do need to take `operator...` as parameter because pasting `operator` and `+` leads to
    // an invalid preprocessing token
#define M0(OP_TOKEN, OP)                                                                            \
    template <typename U>                                                                           \
    BOOST_FORCEINLINE pack_proxy_base& OP_TOKEN(U const& other) BOOST_NOEXCEPT                      \
    {                                                                                               \
      using value_t = typename std::decay<decltype(self().get())>::type;                            \
      set(self().get() OP static_cast<value_t>(other));                                              \
      return *this;                                                                                 \
    }                                                                                               \
    BOOST_FORCEINLINE pack_proxy_base& OP_TOKEN(pack_proxy_base const& other) BOOST_NOEXCEPT        \
    {                                                                                               \
      set(self().get() OP other.self().get());                                                      \
      return *this;                                                                                 \
    }                                                                                               \
    /**/

    M0(operator+=, +)
    M0(operator-=, -)
    M0(operator*=, *)
    M0(operator/=, /)
    M0(operator%=, %)
#undef  M0
  };

  template<typename T> struct is_proxy : std::false_type {};
  template<typename T> struct is_proxy<pack_proxy_base<T>> : std::true_type {};

#define M0(OP_TOKEN, OP)                                                                            \
  template < typename Derived, typename U                                                           \
           , typename Enable = typename std::enable_if<!is_proxy<U>::value>::type                   \
           >                                                                                        \
  BOOST_FORCEINLINE typename Derived::base_type                                                     \
  OP_TOKEN(pack_proxy_base<Derived> const& lhs, U const& rhs) BOOST_NOEXCEPT                        \
  {                                                                                                 \
    return lhs.self().get() OP static_cast<typename Derived::base_type>(rhs);                       \
  }                                                                                                 \
  template < typename Derived, typename U                                                           \
           , typename Enable = typename std::enable_if<!is_proxy<U>::value>::type                   \
           >                                                                                        \
  BOOST_FORCEINLINE typename Derived::base_type                                                     \
  OP_TOKEN(U const& lhs, pack_proxy_base<Derived> const& rhs) BOOST_NOEXCEPT                        \
  {                                                                                                 \
    return static_cast<typename Derived::base_type>(lhs) OP rhs.self().get();                       \
  }                                                                                                 \
  template <typename Derived>                                                                       \
  BOOST_FORCEINLINE typename Derived::base_type                                                     \
  OP_TOKEN(pack_proxy_base<Derived> const& l, pack_proxy_base<Derived> const& r) BOOST_NOEXCEPT     \
  {                                                                                                 \
    return static_cast<typename Derived::base_type>(l.self().get() OP r.self().get());              \
  }                                                                                                 \
  /**/

  M0(operator+, +)
  M0(operator-, -)
  M0(operator/, /)
  M0(operator*, *)
  M0(operator%, %)
#undef  M0

#define M0(OP_TOKEN, OP)                                                                            \
  template < typename Derived, typename U                                                           \
           , typename Enable = typename std::enable_if<!is_proxy<U>::value>::type                   \
           >                                                                                        \
  BOOST_FORCEINLINE                                                                                 \
  bool OP_TOKEN(pack_proxy_base<Derived> const& lhs, U const& rhs) BOOST_NOEXCEPT                   \
  {                                                                                                 \
    return lhs.self().get() OP rhs;                                                                 \
  }                                                                                                 \
  template < typename Derived, typename U                                                           \
           , typename Enable = typename std::enable_if<!is_proxy<U>::value>::type                   \
           >                                                                                        \
  BOOST_FORCEINLINE                                                                                 \
  bool OP_TOKEN(U const& lhs, pack_proxy_base<Derived> const& rhs) BOOST_NOEXCEPT                   \
  {                                                                                                 \
    return lhs OP rhs.self().get();                                                                 \
  }                                                                                                 \
  template <typename Derived>                                                                       \
  BOOST_FORCEINLINE bool OP_TOKEN ( pack_proxy_base<Derived> const& lhs                             \
                                  , pack_proxy_base<Derived> const& rhs                             \
                                  ) BOOST_NOEXCEPT                                                  \
  {                                                                                                 \
    return lhs.self().get() OP rhs.self().get();                                                    \
  }                                                                                                 \
  /**/

  M0(operator==, ==)
  M0(operator!=, !=)
#undef  M0

  // operator: +
  template<typename Derived>
  BOOST_FORCEINLINE
  auto operator+(pack_proxy_base<Derived> const& p) BOOST_NOEXCEPT -> decltype(+p.self().get())
  {
    return +p.self().get();
  }

  // operator: !
  template<typename Derived>
  BOOST_FORCEINLINE bool operator!(pack_proxy_base<Derived> const& p) BOOST_NOEXCEPT
  {
    return !p.self().get();
  }

  // operator: <<
  template<typename Derived>
  inline std::ostream& operator<<(std::ostream& os, pack_proxy_base<Derived> const& p)
  {
    return os << p.self().get();
  }
} } }

#endif
