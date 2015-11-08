//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_SAFE_AT_HPP_INCLUDED
#define NT2_SDK_META_SAFE_AT_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/utility/enable_if.hpp>

namespace nt2 { namespace meta
{
  template<int N, class D, class T> BOOST_FORCEINLINE
  typename boost::lazy_enable_if_c
  < (0 <= N && N < boost::fusion::result_of::size<T>::type::value)
    , boost::fusion::result_of::at_c<const T, N>
  >::type safe_at_c(const T& t, const D& = D())
  {
    return boost::fusion::at_c<N>(t);
  }

  template<int N, class D, class T> BOOST_FORCEINLINE
  typename boost::disable_if_c
  < (0 <= N && N < boost::fusion::result_of::size<T>::type::value)
    , D
  >::type safe_at_c(const T&, const D& d = D())
  {
    return d;
  }

  template<class Seq, int N, class D, class Enable = void>
  struct mpl_safe_at_c
  {
    typedef D type;
  };

  template<class Seq, int N, class D>
  struct mpl_safe_at_c<Seq, N, D, typename boost::enable_if_c< N < boost::mpl::size<Seq>::type::value >::type>
       : boost::mpl::at_c<Seq, N>
  {
  };
} }

#endif
