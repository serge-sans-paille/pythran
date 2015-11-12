//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_DETAILS_COMBINE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_DETAILS_COMBINE_HPP_INCLUDED

#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/utility/share.hpp>
#include <nt2/core/container/colon/colon.hpp>


namespace nt2 { namespace details
{


  template < class T, class A0 >
  BOOST_FORCEINLINE void
  combine_eigens(const T& wr,  const T& wi, A0& w)
  {
    typedef typename A0::value_type type_t;
    int n = numel(wr);
    w.resize(of_size(n, 1));
    nt2::container::table<type_t, nt2::shared_> sw(of_size(n, 1), share(w.raw(), w.raw()+n));
    sw = tocomplex(wr, wi);
  }
  template < class T1, class T2, class A0 >
  BOOST_FORCEINLINE void
  combine_vects(const T1& rv, const T2& wi, A0& v)
  {
    typedef typename A0::value_type type_t;
    int n = height(rv);
    v.resize(of_size(n, n));
    nt2::container::table<type_t, nt2::shared_> sv(of_size(n, n), share(v.raw(), v.raw()+numel(v)));
    for(int j=1; j <= n; ++j)
    {
      if(wi(j))
      {
        sv(nt2::_, j  ) = tocomplex(rv(nt2::_, j), rv(nt2::_, j+1));
        sv(nt2::_, j+1) = conj(sv(nt2::_, j));
        ++j;
      }
      else
        sv(nt2::_, j) = rv(nt2::_, j);
    }
  }
} }

#endif
