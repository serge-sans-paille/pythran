//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_DETAILS_ASSERT_UTILS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_DETAILS_ASSERT_UTILS_HPP_INCLUDED

namespace boost { namespace simd
{
  template<class T>
  bool assert_all( T const& t );

  template<class T>
  bool assert_is_mask( T const& t );

  template<class A0, class A1>
  bool assert_good_shift( A1 const& t );
} }

#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd
{
  template<class T>
  bool assert_all( T const& t )
  {
    for(std::size_t i = 0; i != meta::cardinal_of<T>::value; ++i)
      if(!extract(t, i))
        return false;
    return true;
  }

  template<class T>
  bool assert_is_mask( T const& t )
  {
    for(std::size_t i = 0; i != meta::cardinal_of<T>::value; ++i)
    {
      typedef typename meta::scalar_of<T>::type sT;
      typedef typename dispatch::meta::as_integer<sT, unsigned>::type uT;

      sT v = extract(t, i);
      uT uv = bitwise_cast<uT>(v);

      if(uv != Zero<uT>() && uv != Allbits<uT>())
        return false;
    }
    return true;
  }

  template<class A0, class A1>
  bool assert_good_shift( A1 const& t )
  {
    for(std::size_t i = 0; i != meta::cardinal_of<A0>::value; ++i)
    {
      typedef typename meta::scalar_of<A1>::type sA1;
      typedef typename meta::scalar_of<A0>::type sA0;
      const sA1 N = sizeof(sA0)*8;
      sA1 v = extract(t, i);

      if(v < Zero<sA1>() || v >= N)
      {
        return false;
      }

    }
    return true;
  }
} }

#endif
