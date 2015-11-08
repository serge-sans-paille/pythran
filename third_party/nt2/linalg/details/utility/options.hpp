//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_UTILITY_OPTIONS_HPP_INCLUDED
#define NT2_LINALG_DETAILS_UTILITY_OPTIONS_HPP_INCLUDED

#include <nt2/linalg/details/utility/f77_wrapper.hpp>

namespace nt2 { namespace details
{
  // INTERNAL ONLY
  // Map an immediate char like 'T' to a value suitable for LAPACK char* API
  inline const char* lapack_option(char c)
  {
    static char alpha[] = { 'A', 'B', 'C', 'D', 'E'
                          , 'F', 'G', 'H', 'I', 'J'
                          , 'K', 'L', 'M', 'N', 'O'
                          , 'P', 'Q', 'R', 'S', 'T'
                          , 'U', 'V', 'W', 'X', 'Y'
                          , 'Z'
                          };
    return &alpha[c-'A'];
  }

  // INTERNAL ONLY
  // Returns a pointer to a -1 value for query mode
  inline const nt2_la_int* query()
  {
    static nt2_la_int q(-1);
    return &q;
  }
} }

#endif
