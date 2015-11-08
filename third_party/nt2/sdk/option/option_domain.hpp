//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPTION_OPTION_DOMAIN_HPP_INCLUDED
#define NT2_SDK_OPTION_OPTION_DOMAIN_HPP_INCLUDED

#include <nt2/sdk/option/option_expr_fwd.hpp>
#include <boost/proto/domain.hpp>

namespace nt2 { namespace details
{
  struct  option_domain
        : boost::proto::domain<boost::proto::pod_generator<option_expr> >
  {};
} }

#endif
