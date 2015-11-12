//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TIMING_DETAILS_TIMER_HPP_INCLUDED
#define NT2_SDK_TIMING_DETAILS_TIMER_HPP_INCLUDED

#include <boost/assert.hpp>
#include <stack>

namespace nt2 { namespace details
{
  // INTERNAL ONLY
  // counter<R,T> is an implementation detail that gather and store cycles or
  // seconds measures between tic and toc calls.
  template<class R,class T> class counter
  {
    public :
    typedef T timer_type;
    typedef R type;

    void  tic() const { times().push(time()); }

    type toc( bool display ) const
    {
      BOOST_ASSERT_MSG(!empty(), "Unbalanced timing calls");
      type t = time()-times().top();
      times().pop();
      if(display) timer_type::Print(t);
      return t;
    }

    bool  empty() const { return times().empty();   }
    type  time()  const { return timer_type::Time();  }

    std::stack<type>& times() const
    {
      static std::stack<type> local;
      return local;
    }
  };
} }

#endif
