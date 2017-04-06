//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_LOGICAL_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>
#include <iostream>

namespace boost { namespace simd
{
  /*!
    @ingroup group-types
    Typed boolean value.

    logical<T> is a typed boolean value which can be vectorized in a portable
    manner (contrary to bool). Its semantic is equivalent to bool in all aspects,
    however, a compiler dependent, optimized bool-to-type conversion may be performed.

    @pre T models Vectorizable

    @tparam T Type the boolean value is generated from.
  **/
  template<typename T> struct logical
  {
    using value_type  = T;
    using bits        = dispatch::as_integer_t<T>;

    /// Default constructor
    BOOST_FORCEINLINE logical() = default;

    /// Copy constructor
    BOOST_FORCEINLINE logical(logical const&) = default;

    /// Constructor from boolean value
    BOOST_FORCEINLINE logical(bool v) : value_(v) {}

    /// Constructor from non-boolean value
    template<typename U> BOOST_FORCEINLINE explicit logical(U&& v) : value_(!!v) {}

    // Assignment operator
    BOOST_FORCEINLINE logical& operator=(logical const& v) = default;

    // Assignment operator from bool
    BOOST_FORCEINLINE logical& operator=(bool v)
    {
      value_ = v;
      return *this;
    }

    /// Bitwise complement operator
    BOOST_FORCEINLINE logical operator ~() const { return {!value_}; }

    /// Logical not operator
    BOOST_FORCEINLINE logical operator !() const { return {!value_}; }

    /// Unary + operator
    BOOST_FORCEINLINE logical operator +() const { return *this; }

    /// Convert a logical value to bool
    BOOST_FORCEINLINE operator bool() const { return value_; }

    /// Explicitly convert a logical value to bool
    BOOST_FORCEINLINE bool value() const {return value_; }

    private:
    bool  value_;
  };

  /// Stream insertion operator
  template<typename T>
  BOOST_FORCEINLINE std::ostream& operator<<(std::ostream& os, logical<T> const& v )
  {
    return os << (v.value() ? "true" : "false");
  }

  /// Equality comparison operator
  template<typename T> BOOST_FORCEINLINE
  logical<T> operator ==(logical<T> const& a, logical<T> const& b)
  {
    return a.value() == b.value();
  }

  /// Inequality comparison operator
  template<typename T> BOOST_FORCEINLINE
  logical<T> operator !=(logical<T> const& a, logical<T> const& b)
  {
    return a.value() != b.value();
  }

  /// Equality comparison operator
  template<typename T> BOOST_FORCEINLINE
  logical<T> operator &&(logical<T> const& a, logical<T> const& b)
  {
    return a.value() && b.value();
  }

  /// Inequality comparison operator
  template<typename T> BOOST_FORCEINLINE
  logical<T> operator ||(logical<T> const& a, logical<T> const& b)
  {
    return a.value() || b.value();
  }
} }

#include <boost/simd/meta/hierarchy/logical.hpp>
#include <boost/simd/detail/logical.hpp>

#endif
