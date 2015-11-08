//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPTION_OPTIONS_HPP_INCLUDED
#define NT2_SDK_OPTION_OPTIONS_HPP_INCLUDED

#include <nt2/sdk/option/option_pack.hpp>
#include <nt2/sdk/option/option_expr.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>
#include <boost/mpl/assert.hpp>

namespace nt2 { namespace details
{
  struct options_
  {
    template<class Opts>
    Opts const& operator[](Opts const& opts) const
    {
      BOOST_MPL_ASSERT_MSG( (boost::proto::matches<Opts, option_pack>::value)
                          , NT2_UNKNOWN_NAMED_OPTIONS
                          , (Opts)
                          );
      return opts;
    }
  };
} }

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // options entry-point
  //////////////////////////////////////////////////////////////////////////////
    details::options_ const options = {};
    BOOST_DISPATCH_IGNORE_GLOBAL(options)
}

#define NT2_REGISTER_PARAMETERS(NAME)                               \
struct NAME ## _ {};                                                \
nt2::details::option_expr<                                          \
    boost::proto::terminal<nt2::details::option<NAME ## _> >::type  \
> const NAME = {{{}}}                                               \
/**/

#endif

