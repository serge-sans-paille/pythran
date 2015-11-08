//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_CORRECT_FMA_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_CORRECT_FMA_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/correct_fma.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/split.hpp>
#include <boost/simd/include/functions/simd/group.hpp>
#include <boost/simd/include/functions/simd/two_prod.hpp>
#include <boost/simd/include/functions/simd/two_add.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

#ifndef BOOST_SIMD_DONT_CARE_FMA_OVERFLOW
#include <boost/simd/include/functions/simd/ldexp.hpp>
#include <boost/simd/include/functions/simd/exponent.hpp>
#include <boost/simd/include/functions/simd/maxmag.hpp>
#include <boost/simd/include/functions/simd/minmag.hpp>
#include <boost/simd/include/functions/simd/shift_right.hpp>
#include <boost/simd/include/functions/simd/unary_minus.hpp>
#endif

namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::correct_fma_, tag::cpu_
                                       , (A0)(X)
                                       , ( simd::meta::is_upgradable_on_ext<A0,X> )
                                       , ((simd_<single_<A0>,X>))
                                         ((simd_<single_<A0>,X>))
                                         ((simd_<single_<A0>,X>))
                                       )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      typedef typename dispatch::meta::upgrade<A0>::type ivtype;
      ivtype a0l, a0h, a1l, a1h, a2l, a2h;
      split(a0, a0l, a0h);
      split(a1, a1l, a1h);
      split(a2, a2l, a2h);
      return group(a0l*a1l+a2l, a0h*a1h+a2h);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::correct_fma_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                      ((simd_<floating_<A0>,X>))
                                      ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      result_type p, rp, s, rs;
#ifndef BOOST_SIMD_DONT_CARE_FMA_OVERFLOW
        typedef typename boost::dispatch::meta::as_integer<A0>::type iA0;
        result_type amax =  maxmag(a0, a1);
        result_type amin =  minmag(a0, a1);
        iA0 e0 = -shift_right(exponent(amax), 1);
        amax = ldexp(amax, e0);
        result_type a02 = ldexp(a2, e0);
        two_prod(amax, amin, p, rp);
        two_add(p, a02, s, rs);
        return ldexp(s+(rp+rs), -e0);
#else
        two_prod(a0, a1, p, rp);
        two_add(p, a2, s, rs);
        return s+(rp+rs);
#endif

    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::correct_fma_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_< integer_<A0>,X >))
                                      ((simd_< integer_<A0>,X >))
                                      ((simd_< integer_<A0>,X >))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      return a0*a1+a2;
    }
  };
} } }


#endif
