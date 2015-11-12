//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_UTILITY_ENVBLOCKSIZE_HPP_INCLUDED
#define NT2_LINALG_DETAILS_UTILITY_ENVBLOCKSIZE_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

extern "C"
{

  nt2_la_int NT2_F77NAME(ilaenv)(const nt2_la_int *i, const char *n, const char *opts, const nt2_la_int *n1,
                                 const nt2_la_int *n2, const nt2_la_int *n3, const nt2_la_int *n4,
                                 nt2_la_int n_len, nt2_la_int opts_len);

}

namespace nt2 { namespace details
{
   inline nt2_la_int EnvBlockSize(nt2_la_int ispec,
                   const std::string & fname,
                   const std::string & opts,
                   nt2_la_int n1 = -1,
                   nt2_la_int n2 = -1,
                   nt2_la_int n3 = -1,
                   nt2_la_int n4 = -1)
  {
    nt2_la_int i = ispec;
    nt2_la_int N1 = n1;
    nt2_la_int N2 = n2;
    nt2_la_int N3 = n3;
    nt2_la_int N4 = n4;
    return NT2_F77NAME(ilaenv)(&i, fname.c_str(), opts.c_str(), &N1, &N2, &N3, &N4,
                           fname.size(), opts.size());
  }
} }


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of envblocksize.hpp
// /////////////////////////////////////////////////////////////////////////////
