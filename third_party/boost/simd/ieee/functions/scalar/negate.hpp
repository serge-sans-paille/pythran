//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_NEGATE_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_NEGATE_HPP_INCLUDED

#include <boost/simd/ieee/functions/negate.hpp>
#include <boost/simd/include/functions/scalar/is_nez.hpp>
#include <boost/simd/include/functions/scalar/sign.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::negate_, tag::cpu_
                                    , (A0)
                                    , (scalar_< signed_<A0> >)
                                      (scalar_< signed_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0*sign(a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::negate_, tag::cpu_
                                    , (A0)
                                    , (scalar_< unsigned_<A0> >)
                                      (scalar_< unsigned_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return bool(is_nez(a1))*a0;
    }
  };
} } }


#endif
