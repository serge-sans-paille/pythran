//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPTION_OPTION_TERM_HPP_INCLUDED
#define NT2_SDK_OPTION_OPTION_TERM_HPP_INCLUDED

#include <nt2/sdk/option/option.hpp>
#include <boost/proto/traits.hpp>

namespace nt2 { namespace details
{
  struct option_term
      : boost::proto::terminal< option< boost::proto::_ > >
  {};
} }

#endif
