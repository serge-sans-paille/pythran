//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_ULPDIST_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_ULPDIST_HPP_INCLUDED

#include <boost/simd/ieee/functions/ulpdist.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/include/functions/simd/is_equal.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/frexp.hpp>
#include <boost/simd/include/functions/simd/ldexp.hpp>
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/constants/eps.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ulpdist_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                      ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_integer<A0>::type itype;
      itype e1, e2;

      A0 m1 = boost::simd::frexp(a0, e1);
      A0 m2 = boost::simd::frexp(a1, e2);

      itype expo = -boost::simd::max(e1, e2);

      A0 e = select ( boost::simd::is_equal(e1, e2)
                    , boost::simd::abs(m1-m2)
                    , boost::simd::abs( boost::simd::ldexp(a0, expo)
                                      - boost::simd::ldexp(a1, expo)
                                      )
                    );

      return if_zero_else ( logical_or( logical_and(is_nan(a0), is_nan(a1))
                                      , boost::simd::is_equal(a0, a1)
                                      )
                          , e/Eps<A0>()
                          );
    }
  };
} } }


#endif
