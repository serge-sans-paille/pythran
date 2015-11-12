//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_SMALLEST_TYPE_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_SMALLEST_TYPE_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// Compute the smallest floating type between T and U
  template< class T, class U
          , class pT = typename boost::dispatch::meta::primitive_of<T>::type
          , class pU = typename boost::dispatch::meta::primitive_of<U>::type
          , bool  sT = boost::is_floating_point<T>::value
          , bool  sU = boost::is_floating_point<U>::value
          >
  struct  smallest_impl
        : boost::mpl::if_c <(sizeof(pT) <= sizeof(pU)), T , U >
  {};

  template< class T, class U, class pT, class pU>
  struct  smallest_impl<T,U,pT,pU,true,false>
  {
    typedef T type;
  };

  template< class T, class U, class pT, class pU>
  struct  smallest_impl<T,U,pT,pU,false,true>
  {
    typedef U type;
  };

  /// INTERNAL ONLY
  /// Cast a value toward the smallest type compatible with T and U for
  /// proper ULP comparisons
  template<class T, class U>
  typename smallest_impl<T, U>::type smallest_a(T const& a, U const&)
  {
    return typename smallest_impl<T, U>::type(a);
  }

  /// INTERNAL ONLY
  /// Cast a value toward the smallest type compatible with T and U for
  /// proper ULP comparisons
  template<class T, class U>
  typename smallest_impl<T, U>::type smallest_b(T const&, U const& b)
  {
    return typename smallest_impl<T, U>::type(b);
  }
} }

#endif
