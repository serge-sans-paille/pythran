//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_ASSERT_UTILS_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_ASSERT_UTILS_HPP_INCLUDED

#include <boost/simd/function/definition/extract.hpp>
#include <boost/simd/function/definition/bitwise_cast.hpp>
#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd
{
  namespace bs = boost::simd;
  namespace tt = nsm::type_traits;

  template<typename T> BOOST_FORCEINLINE bool assert_all( T const& t )
  {
    for(std::size_t i = 0; i != cardinal_of<T>::value; ++i)
      if(!extract(t, i)) return false; //extract(t, i);
    return true;
  }

  template<typename T> BOOST_FORCEINLINE bool assert_is_mask( T const& t )
  {
    for(std::size_t i = 0; i != cardinal_of<T>::value; ++i)
    {
      typedef dispatch::scalar_of_t<T> sT;
      typedef dispatch::as_integer_t<sT, unsigned> uT;

      sT v = extract(t, i);
      uT uv = bitwise_cast<uT>(v);

      if(uv != uT(0) && uv != Allbits<uT>()) return false;
    }
    return true;
  }

  template<typename A0, typename A1>
  BOOST_FORCEINLINE bool assert_good_shift( A1 const& t, tt::true_type const&)
  {
    for(std::size_t i = 0; i != cardinal_of<A0>::value; ++i)
    {
      typedef dispatch::scalar_of_t<A1> sA1;
      typedef dispatch::scalar_of_t<A0> sA0;
      const sA1 N = sizeof(sA0)*8;
      sA1 v = extract(t, i);

      if(v >= N)  return false;
    }

    return true;
  }

  template<typename A0, typename A1>
  BOOST_FORCEINLINE bool assert_good_shift( A1 const& t, tt::false_type const&)
  {
    for(std::size_t i = 0; i != cardinal_of<A0>::value; ++i)
    {
      typedef dispatch::scalar_of_t<A1> sA1;
      typedef dispatch::scalar_of_t<A0> sA0;
      const sA1 N = sizeof(sA0)*8;
      sA1 v = extract(t, i);

      if(v < sA1(0) || v >= N)  return false;
    }

    return true;
  }

  template<typename A0, typename A1>
  BOOST_FORCEINLINE bool assert_good_shift( A1 const& t )
  {
    return assert_good_shift<A0>(t, typename tt::is_unsigned<dispatch::scalar_of_t<A1>>::type{});
  }

} }

#endif
