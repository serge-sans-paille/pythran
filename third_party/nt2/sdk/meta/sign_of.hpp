//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_SIGN_OF_HPP_INCLUDED
#define NT2_SDK_META_SIGN_OF_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/is_signed.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <nt2/sdk/meta/is_fundamental.hpp>
#include <boost/dispatch/meta/sign_of.hpp>

namespace nt2 { namespace meta
{
  using boost::dispatch::meta::sign_of;
} }

#endif
