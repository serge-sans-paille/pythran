//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_GENERIC_REALLOG_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_GENERIC_REALLOG_HPP_INCLUDED

#include <nt2/exponential/functions/reallog.hpp>
#include <boost/assert.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <nt2/include/functions/simd/is_nltz.hpp>
#include <nt2/include/functions/simd/log.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reallog_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG(boost::simd::assert_all(nt2::is_nltz(a0)),
                       "reallog cannot produce complex result.");
      return nt2::log(a0);
    }
  };
} }

#endif
