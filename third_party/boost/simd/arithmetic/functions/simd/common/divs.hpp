//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_DIVS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/divs.hpp>
#include <boost/simd/include/functions/simd/is_eqz.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/include/functions/simd/shift_right.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/if_zero_else_one.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/bitwise_xor.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

// perhaps divs for signed integral types must invoke correct Valmin entry and invoke  divfix
// also call simply divfix for unsigned
// also rdivide has to be defined as divs for float and as divfix for integers
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divs_, tag::cpu_, (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                      ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0/a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divs_, tag::cpu_, (A0)(X)
                                    , ((simd_<uint_<A0>,X>))
                                      ((simd_<uint_<A0>,X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0;


      const bA0 iseqza1 = is_eqz(a1);
      const A0 aa1 = if_else(iseqza1, One<A0>(), a1);
      const A0 aa0 = if_else(iseqza1, genmask(a0), a0);
      return aa0/aa1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divs_, tag::cpu_, (A0)(X)
                                    , ((simd_<int_<A0>,X>))
                                      ((simd_<int_<A0>,X>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::scalar_of<A0>::type sA0;

      const bA0 iseqza1 = is_eqz(a1);

      // replace valmin/-1 by (valmin+1)/-1
      A0 x = a0 + if_zero_else_one((a1 + One<A0>()) | (a0 + Valmin<A0>()));
      // negative -> valmin
      // positive -> valmax
      const A0 x2 = bitwise_xor(Valmax<A0>(), shrai(x, sizeof(sA0)*CHAR_BIT-1));

      x = if_else(logical_and(iseqza1, is_nez(x)), x2, x);
      const A0 y = if_else(iseqza1, One<A0>(), a1);
      return x/y;
    }
  };
} } }

#endif
