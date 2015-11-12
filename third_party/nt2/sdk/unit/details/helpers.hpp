//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_HELPERS_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_HELPERS_HPP_INCLUDED

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <boost/dispatch/meta/is_signed.hpp>
#include <boost/mpl/bool.hpp>
#include <cmath>

namespace nt2
{
  ////////////////////////////////////////////////////////////////////////////////
  // roll a random number (will be nt2::rand afterward)
  ////////////////////////////////////////////////////////////////////////////////
  template<class T, class X,  class Y, bool B>
  struct typed_inner_roll;

  template<class T, class X,  class Y>
  struct typed_inner_roll<T, X, Y, true>
  {
    static inline T call(X mn, Y mx)
    {
      // mn is supposed less than mx
      double r1 = ((double)::rand()/RAND_MAX);
      if(mx == 0)
      {
        return nt2::splat<T>(r1*mn);
      }
      else if (mn == 0)
      {
        return nt2::splat<T>(r1*mx);
      }
      else
      {
        double fac =  0.5*std::abs(double(mn)/double(mx));
        double r2 = ((double)::rand()/RAND_MAX);
        return nt2::splat<T>((r1 > fac) ? r2*mn : r2*mx);
      }
    }
  };

  template<class T, class X,  class Y>
  struct typed_inner_roll<T, X, Y, false>
  {
    static inline T call(X mn, Y mx)
    {
      double r = ((double)::rand()/RAND_MAX)*(mx-mn) + mn;
      return nt2::splat<T>(r);
    }
  };

  template<class T,class X, class Y> inline T roll(X mn, Y mx)
  {
    return typed_inner_roll<T, X, Y, boost::dispatch::meta::is_signed<T>::value>::call(mn, mx);
  }

  //=================================================================================
  template<class T, bool B>
  struct inner_roll;

  template<class T>
  struct inner_roll<T, true>
  {
    static inline T call()
    {
      double r1 = ((double)::rand()/RAND_MAX);
      double r2 = ((double)::rand()/RAND_MAX);
      return nt2::splat<T>((r1 > 0.5) ? r2*nt2::Valmin<T>() : r2*nt2::Valmax<T>());
    }
  };

  template<class T>
  struct inner_roll<T, false>
  {
    static inline T call()
    {
      double r1 = ((double)::rand()/RAND_MAX);
      return nt2::splat<T>(r1*nt2::Valmax<T>());
    }
  };

  template<class T> inline T roll()
  {
    return inner_roll<T, boost::dispatch::meta::is_signed<T>::value>::call();
  }




}
using nt2::roll;

#endif
