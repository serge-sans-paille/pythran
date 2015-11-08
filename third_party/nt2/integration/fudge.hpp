//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_FUDGE_HPP_INCLUDED
#define NT2_INTEGRATION_FUDGE_HPP_INCLUDED
#include <nt2/include/functions/is_invalid.hpp>

namespace nt2
{
  namespace details
  {
    template < class FUNC, int IND, class VT, class INPUT, bool test = true>
    struct fudge
    {
      static void fdg(const  FUNC & f, VT&y, size_t& fcnt, const bool & singular,
                      const INPUT& x, const INPUT& shift)
      {
        size_t i =  IND;
        if ((singular) && nt2::is_invalid(y(i)))// Fudge to avoid nans or infinities.
        {
          y(i) = f(x+shift); ++fcnt;
        }
      }
    };

    template < class FUNC, class VT, class INPUT>
    struct fudge < FUNC, 0, VT, INPUT, true >
    {
      static void fdg(const  FUNC & f, VT&y, size_t& fcnt, const bool & singular,
                      const INPUT& x, const INPUT& shift)
      {
        if ((singular) && nt2::is_invalid(y(end_)))// Fudge to avoid nans or infinities.
        {
          y(end_) = f(x+shift); ++fcnt;
        }
      }
    };

    template < class FUNC, int IND, class VT, class INPUT>
    struct fudge < FUNC, IND, VT, INPUT, false>
    {
      static void fdg(const  FUNC &, VT&, size_t& , const bool &,
                      const INPUT&, const INPUT&) {}
    };

  }

}


#endif
