 //==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_MAKE_INTEGER_HPP_INCLUDED
#define BOOST_DISPATCH_META_MAKE_INTEGER_HPP_INCLUDED

#include <boost/integer.hpp>
#include <boost/cstdint.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/dispatch/meta/na.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /**
   * Build a standard integer type from a sign and a size in bytes
   **/
  template< std::size_t Size
          , class Sign      = unsigned
          , class Transform = na_
          >
  struct  make_integer {};

  /// INTERNAL ONLY
  template< std::size_t Size, class Transform>
  struct  make_integer<Size,unsigned,Transform>
        : boost::mpl::apply<Transform,typename boost::uint_t<CHAR_BIT*Size>::fast> {};

  /// INTERNAL ONLY
  template< std::size_t Size, class Transform >
  struct  make_integer<Size,signed,Transform>
        : boost::mpl::apply<Transform,typename boost::int_t<CHAR_BIT*Size>::fast> {};

  /// INTERNAL ONLY
  /// Overload for long long to fix lack of boost::integer support
  template< class Transform >
  struct  make_integer<sizeof(boost::int64_t),unsigned,Transform>
        : boost::mpl::apply<Transform,boost::uint64_t> {};

  /// INTERNAL ONLY
  template< class Transform >
  struct  make_integer<sizeof(boost::int64_t),signed,Transform>
        : boost::mpl::apply<Transform,boost::int64_t> {};

  /// INTERNAL ONLY
  /// Overload to prevent useless apply<_,T> template instanciation
  template< std::size_t Size> struct make_integer<Size,unsigned,na_>
  {
    typedef typename boost::uint_t<CHAR_BIT*Size>::fast type;
  };

  /// INTERNAL ONLY
  template< std::size_t Size> struct make_integer<Size,signed,na_>
  {
    typedef typename boost::int_t<CHAR_BIT*Size>::fast type;
  };

  /// INTERNAL ONLY
  template<> struct make_integer<sizeof(boost::int64_t),unsigned,na_>
  {
    typedef boost::uint64_t type;
  };

  /// INTERNAL ONLY
  template<> struct make_integer<sizeof(boost::int64_t),signed,na_>
  {
    typedef boost::int64_t type;
  };
} } }

#endif
