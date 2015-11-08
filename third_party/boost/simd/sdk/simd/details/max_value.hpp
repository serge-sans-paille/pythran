//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_MAX_VALUE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_MAX_VALUE_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/apply.hpp>

namespace boost { namespace simd { namespace details
{
  template<class F>
  struct max_value_impl
  {
    template<class Sig>
    struct result;

    template<class This, class T, class U>
    struct result<This(T, U)>
    {
      typedef typename dispatch::meta::strip<T>::type sT;
      typedef typename mpl::apply1<F, sT>::type vT;
      typedef typename dispatch::meta::strip<U>::type sU;
      typedef typename mpl::apply1<F, sU>::type vU;
      typedef typename mpl::if_< mpl::greater<vU, vT>
                               , sU
                               , sT
                               >::type type;
    };

    template<class T, class U>
    typename result<max_value_impl(T const&, U const&)>::type operator()(T const&, U const&) const;
  };

  template<class T, class F>
  struct max_value
       : fusion::result_of::
         fold< T
             , typename fusion::result_of::
               value_of< typename fusion::result_of::begin<T>::type
                       >::type
             , max_value_impl<F>
             >
  {
  };

  template<class T, class F, bool IsSequence = boost::fusion::traits::is_sequence<T>::value >
  struct max_value_noseq
  {
    typedef T type;
  };

  template<class T, class F>
  struct max_value_noseq<T, F, true>
       : max_value<T, F>
  {
  };

} } }

#endif
