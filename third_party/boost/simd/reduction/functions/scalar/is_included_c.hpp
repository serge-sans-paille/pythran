//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SCALAR_IS_INCLUDED_C_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SCALAR_IS_INCLUDED_C_HPP_INCLUDED

#include <boost/simd/reduction/functions/is_included_c.hpp>
#include <boost/simd/include/functions/scalar/bitwise_and.hpp>
#include <boost/simd/include/functions/scalar/is_eqz.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_included_c_
                                    , tag::cpu_
                                    , (A0)
                                    , (scalar_< fundamental_<A0> >)
                                      (scalar_< fundamental_<A0> >)
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return is_eqz(bitwise_and(a1, a0));
    }
  };
} } }

#endif
