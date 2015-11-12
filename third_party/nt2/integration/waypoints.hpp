//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_WAYPOINTS_HPP_INCLUDED
#define NT2_INTEGRATION_WAYPOINTS_HPP_INCLUDED

#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/core/container/extremum/extremum.hpp>

namespace nt2
{
  namespace details
  {
    template < class O, class X,  class W>
    inline void prepare_waypoints(O const &o, const X& x, W& wpts)
    {
      typedef typename X::value_type itype;
      BOOST_ASSERT_MSG( isempty(o.waypoints) || (numel(x) == 2)
                      , "Choose x or waypoints, not both"
                      );

      if (isempty(o.waypoints))
      {
        wpts = nt2::rowvect(x);
      }
      else if (numel(x) == 2)
      {
        itype a = x(begin_), b = x(end_);
        if(a != o.waypoints(begin_) && b!=o.waypoints(end_) )
          wpts =  nt2::cath(nt2::cath(a, nt2::rowvect(o.waypoints)), b);
        else if (a != o.waypoints(begin_))  wpts =  nt2::cath(a, nt2::rowvect(o.waypoints));
        else if (b != o.waypoints(end_))  wpts =  nt2::cath(nt2::rowvect(o.waypoints), b);
        else wpts = nt2::rowvect(o.waypoints);
      }
      else
      {
        wpts = nt2::rowvect(o.waypoints);
      }
    }
  }
}

#endif
