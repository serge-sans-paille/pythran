//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_DETAILS_EVAL_LINSOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_DETAILS_EVAL_LINSOLVE_HPP_INCLUDED

#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <boost/assert.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace ext
{
    //==========================================================================
    /// INTERNAL ONLY - Parameters evaluation
    //==========================================================================
    template<typename A0,typename A1,typename eval_type> BOOST_FORCEINLINE
    void eval_param(A0& a0, A1& a1, eval_type& that)
    {
      nt2_la_int  m1  = nt2::height(a1);
      nt2_la_int  n   = nt2::width(a0);
      nt2_la_int  n1  = nt2::width(a1);

      BOOST_ASSERT_MSG( nt2_la_int(nt2::height(a0)) == m1 , "Nonconformant arguments" );

      if(m1 < n)
      {
        that = nt2::expand(a1,nt2::of_size(n,n1));
        nt2_la_int mn = std::abs(m1-n);
        nt2_la_int coord;

        for(nt2_la_int i = 1; i <= n1; ++i)
        {
          coord = m1+(i-1)*n;
          std::fill(that.raw()+coord,that.raw()+mn+coord,that(m1,i));
        }
      }
      else that = a1;
    }
} }

#endif
