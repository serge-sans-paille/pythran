//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_MOD_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_GENERIC_MOD_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/mod.hpp>
#include <boost/simd/include/functions/simd/selsub.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/divfloor.hpp>
#include <boost/simd/include/functions/simd/idivfloor.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mod_, tag::cpu_
                                    , (A0)
                                    , (generic_<floating_<A0> >)
                                      (generic_<floating_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return selsub(boost::simd::is_nez(a1),a0,
                    divfloor(a0,a1)*a1
                   );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mod_, tag::cpu_
                                    , (A0)
                                    , (generic_<arithmetic_<A0> >)
                                      (generic_<arithmetic_<A0> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return selsub(is_nez(a1),a0,
                    boost::simd::multiplies(idivfloor(a0,a1), a1)
                   );

    }
  };


} } }

#endif
