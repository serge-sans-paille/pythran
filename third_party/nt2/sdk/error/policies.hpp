//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_POLICIES_HPP_INCLUDED
#define NT2_SDK_ERROR_POLICIES_HPP_INCLUDED

#include <boost/math/policies/policy.hpp>

namespace nt2
{
  typedef boost::math::policies::
          policy< boost::math::policies::domain_error<boost::math::policies::errno_on_error>
                , boost::math::policies::pole_error<boost::math::policies::errno_on_error>
                , boost::math::policies::overflow_error<boost::math::policies::errno_on_error>
                , boost::math::policies::evaluation_error<boost::math::policies::errno_on_error>
                , boost::math::policies::rounding_error<boost::math::policies::errno_on_error>
                > nt2_policy;
}

#endif
