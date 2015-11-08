//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_COVER_UTILS_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_COVER_UTILS_HPP_INCLUDED
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>

namespace nt2
{

template < class S > S downgrade_upper()
{
  typedef typename nt2::meta::downgrade<S>::type dtype;
  return nt2::Valmax<dtype>();
}

template < class S > S downgrade_lower()
{
  typedef typename nt2::meta::downgrade<S>::type dtype;
  return nt2::Valmin<dtype>();
}

}


#endif
