//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_COMPLEX_DRY_HPP_INCLUDED
#define NT2_SDK_COMPLEX_DRY_HPP_INCLUDED

#include <nt2/sdk/complex/details/dry/meta.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/details/aliasing.hpp>

namespace nt2
{
  template<class T>
  struct BOOST_SIMD_MAY_ALIAS dry
  {
    typedef T type;
    T value;

    dry() {}
    explicit dry(T const& value_) : value(value_)
    {
    }
    operator T () const {return value; }
    operator T&()       {return value; }
    bool operator == (const dry<T>&a) const{return value == a.value; }
    bool operator != (const dry<T>&a) const{return value != a.value; }

    T&       operator()()       { return value; }
    T const& operator()() const { return value; }
  };
    ////////////////////////////////////////////////////////////////////////////
  // Stream insertion for dry<T>
  ////////////////////////////////////////////////////////////////////////////
  template<class T>
  BOOST_FORCEINLINE
  std::ostream& operator<<(std::ostream& os, dry<T> const& v )
  {
    return os << "(" << v() << ", _ )";
  }
}

#include <nt2/include/functions/extract.hpp>

namespace boost { namespace simd
{
  template<class T, class Ext>
  BOOST_FORCEINLINE
  std::ostream& operator<<(std::ostream& os, boost::simd::native<nt2::dry<T>,Ext> const& v )
  {
    const std::size_t size = meta::cardinal_of<boost::simd::native<T, Ext> >::value;
    os << "{";
    for(std::size_t i = 0;  i < size; ++i)
    {
      os << v[i] << ((i+1 == size) ? "}" :", ");
    }
    return os;
  }
} }

#endif
