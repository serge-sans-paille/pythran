//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_REGISTRATION_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_REGISTRATION_HPP_INCLUDED

namespace boost { namespace simd
{
  namespace details
  {
    struct support_registration
    {
      support_registration(const char* n, bool (*f)(), support_registration* nx)
                          : name(n), function(f), next(0)
      {
        if(nx) next = nx->link(this);
      }

      support_registration* link(support_registration* n)
      {
        if(next != 0 )  return next->link(n);
        else            next = n;
        return 0;
      }

      const char*            name;
      bool                   (*function)();
      support_registration*  next;

    private:
      support_registration(support_registration const&);
      support_registration& operator=(support_registration const&);
    };

    static support_registration registration_list(0,0,0);
  }
} }

#endif
