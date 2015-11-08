//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_PICK_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_PICK_HPP_INCLUDED

#include <boost/simd/swar/functions/details/topology.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // Either extract the Ith element for a shuffle or return 0 if I is -1
  // As we use static extract, we statically jump to the correct extract call
  // to avoid warning about overflow in extract index
  //============================================================================
  template<int I, typename T, int C> struct pick
  {
    typedef typename simd::meta::scalar_of<T>::type type;

    static BOOST_FORCEINLINE type apply(T const& a0)
    {
      return extract<I>(a0);
    }

    template<typename A0>
    static BOOST_FORCEINLINE type apply(A0 const& a0, A0 const& a1)
    {
      return apply(a0,a1,boost::mpl::bool_<!(I >= C)>() );
    }

    template<typename A0>
    static BOOST_FORCEINLINE type apply ( A0 const& a0, A0 const&
                                        , boost::mpl::true_ const&
                                        )
    {
      return extract<I>(a0);
    }

    template<typename A0>
    static BOOST_FORCEINLINE type apply ( A0 const&, A0 const& a1
                                        , boost::mpl::false_ const&
                                        )
    {
      return extract<I-C>(a1);
    }
  };

  //============================================================================
  // Static dispatch over -1 so extract never get called
  //============================================================================
  template<typename T, int C>
  struct pick<-1,T,C>
  {
    typedef typename simd::meta::scalar_of<T>::type type;

    static BOOST_FORCEINLINE type apply(T const&)
    {
      return type(0);
    }

    template<typename A0>
    static BOOST_FORCEINLINE type apply(A0 const&, A0 const&)
    {
      return type(0);
    }
  };
} } }

#endif
