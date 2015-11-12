//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIVS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_DIVS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/divs.hpp>
#include <boost/simd/include/functions/scalar/genmask.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4723) // potential divide by 0
#endif

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< floating_<A0> >)
                                      (scalar_< floating_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a0/a1;
    }
  };

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< int_<A0> >)
                                      (scalar_< int_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_unsigned<A0>::type utype;
      A0 const aa0 = a0 + !((a1 + One<A0>()) | ((utype)a0 + Valmin<A0>()));
      if (a1)
        return aa0/a1;
      else if (a0)
        return Valmax<A0>() + ((utype)a0 >> (sizeof(A0)*CHAR_BIT-1));
      else
        return Zero<A0>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::divs_, tag::cpu_
                                    , (A0)
                                    , (scalar_< uint_<A0> >)
                                      (scalar_< uint_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return a1 ? a0/a1 : genmask(a0);
    }
  };
} } }

#endif
